
#define _GNU_SOURCE
#include <dlfcn.h>
#include <assert.h>
#include "common.h"
#include "core.h"

char            game_start(char *path, int team_nb)
{
    t_lemipc    *s_lemipc;

    catch_signals();
    srand(time(NULL));
    if (!get_shr_mem_handle(&s_lemipc, path))
        return 0;
    return game_loop(s_lemipc, team_nb);
}

char check_player_dead(t_lemipc *s_lemipc, t_player *me)
{
    if (me->pid != -1)
        return 0;
    init_s_player(me);
    sem_post(&s_lemipc->move_lock);
    if (s_lemipc->nbr_players <= 0)
        clean_ipcs(s_lemipc);
    return 1;
}

char game_loop(t_lemipc *s_lemipc, int team_nb)
{
    t_player *me;
    if (EINTR == sem_wait(&s_lemipc->move_lock))
        return 0;
    if (!new_player_slot(&me, s_lemipc, team_nb))
        return 0;
    sem_post(&s_lemipc->move_lock);
    while (1) {
        if (EINTR == sem_wait(&s_lemipc->move_lock))
            return 0;
        if (check_player_dead(s_lemipc, me))
            return 1;
        if (!can_playing(s_lemipc, me) ||
            !focus_ennemy(me, &s_lemipc->players) ||
              !move_forward(s_lemipc, me)) {

            LOG_MSG("[IDLE] Me: pid=%d x=%d y=%d team_id=%d\n",
                    me->pid,
                    me->x,
                    me->y,
                    me->team_id);

        } else {
            LOG_MSG("[PLAYING] Me: pid=%d x=%d y=%d team_id=%d | ennemy: pid=%d x=%d y=%d team_id=%d\n",
                    me->pid,
                    me->x,
                    me->y,
                    me->team_id,
                    me->player_focus->pid,
                    me->player_focus->x,
                    me->player_focus->y,
                    me->player_focus->team_id);
        }
        sem_post(&s_lemipc->move_lock);
        sleep(GAME_SLEEP);
    }
}

char        get_shr_mem_handle(t_lemipc **s_lemipc, char *path)
{
    void    *shared_handle;
    char    (*get_shared_lemipc)(t_lemipc **, char *);

    shared_handle = dlopen("./liblemipc_shared.so", RTLD_LAZY);
    if (!shared_handle)
        return 0;
    get_shared_lemipc = dlsym(shared_handle, "get_shared_lemipc");
    if (!get_shared_lemipc)
        return 0;
    if (!get_shared_lemipc(s_lemipc, path))
        return 0;
    dlclose(shared_handle);
    g_lemipc = *s_lemipc;
    return 1;
}

void clean_ipcs(t_lemipc *lemipc)
{
    if (lemipc->nbr_players <= 0) {
        shmctl(lemipc->shm_key, IPC_RMID, NULL);
        sem_close(&lemipc->move_lock);
        LOG_MSG("IPCS cleaned\n");
    }
}

char        can_playing(t_lemipc *s_lemipc, t_player *me)
{
    int     i;
    char    different_team;
    char    has_friend;

    i = -1;
    different_team = 0;
    has_friend = 0;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].is_free == 0 &&
            s_lemipc->players[i].team_id != me->team_id)
            different_team = 1;
        if (s_lemipc->players[i].team_id == me->team_id &&
            s_lemipc->players[i].pid != me->pid)
            has_friend = 1;
    }
    return (different_team && has_friend);
}

char    focus_ennemy(t_player *me, t_player *players)
{
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (players[i].is_free == 0 &&
            players[i].team_id != me->team_id) {
            me->player_focus = &players[i];
            return 1;
        }
    }
    me->player_focus = NULL;
    return 0;
}

char            check_ennemy_on_this_pos(t_player (*players)[MAX_PLAYERS],
                              t_player *player, int x, int y)
{
    t_player    *ennemy;

    return ((ennemy = has_player_on_this_pos(players, x, y)) &&
            ennemy->team_id != player->team_id);
}

char        count_ennemies_around(t_player (*players)[MAX_PLAYERS],
                                  t_player *player)
{
    int     x;
    int     y;
    char    c;

    c = 0;
    x = player->x;
    y = player->y;
    c += check_ennemy_on_this_pos(players, player, x, y - 1);
    c += check_ennemy_on_this_pos(players, player, x + 1, y - 1);
    c += check_ennemy_on_this_pos(players, player, x + 1, y);
    c += check_ennemy_on_this_pos(players, player, x + 1, y + 1);
    c += check_ennemy_on_this_pos(players, player, x, y + 1);
    c += check_ennemy_on_this_pos(players, player, x - 1, y + 1);
    c += check_ennemy_on_this_pos(players, player, x - 1, y);
    c += check_ennemy_on_this_pos(players, player, x - 1, y - 1);
    return c;
}

char kill_player(t_lemipc *s_lemipc, t_player *player)
{
    init_s_player(player);
    s_lemipc->nbr_players--;
}

char    eat_ennemies_around(t_lemipc *s_lemipc)
{
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].pid != -1 &&
                s_lemipc->players[i].is_free == 0) {
            if (count_ennemies_around(&s_lemipc->players,
                                      &s_lemipc->players[i]) > 1)
                kill_player(s_lemipc, &s_lemipc->players[i]);
        }
    }
}

void move_forward_check_dest(t_player *me, t_dist_cmp *dist_cmp, t_lemipc *s_lemipc)
{
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x, me->y - 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y - 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y - 1), &s_lemipc->players);
}

char            move_forward(t_lemipc *s_lemipc, t_player *me)
{
    int         max;
    t_dist_cmp  dist_cmp;

    if (!me->player_focus)
        return 0;
    max = round(sqrt(MAX_PLAYERS)) - 1;
    init_dist_cmp(&dist_cmp);
    if (1 != check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y),
                            &s_lemipc->players))
        move_forward_check_dest(me, &dist_cmp, s_lemipc);
    if (dist_cmp.dest.x != -1 && dist_cmp.dest.y != -1) {
        me->x = dist_cmp.dest.x;
        me->y = dist_cmp.dest.y;
    }
    eat_ennemies_around(s_lemipc);
    return 1;
}
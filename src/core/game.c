
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

void game_play(t_lemipc *s_lemipc, t_player *me)
{
    if (!can_playing(s_lemipc, me) ||
        !focus_ennemy(me, &s_lemipc->players) ||
        !move_forward(s_lemipc, me)) {
        LOG_MSG("[IDLE] Me: pid=%d x=%d y=%d team_id=%d\n",
                me->pid,
                me->x,
                me->y,
                me->team_id);
    } else {
        LOG_MSG("[PLAYING] Me: pid=%d x=%d y=%d team_id=%d | "
                "ennemy: pid=%d x=%d y=%d team_id=%d\n",
                me->pid,
                me->x,
                me->y,
                me->team_id,
                me->player_focus->pid,
                me->player_focus->x,
                me->player_focus->y,
                me->player_focus->team_id);
    }
}

char one_team_playing(t_lemipc *s_lemipc)
{
    int i;
    int team_id;

    team_id = -1;
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!s_lemipc->players[i].is_free &&
            s_lemipc->players[i].team_id != -1) {
            if (team_id == -1) {
                team_id = s_lemipc->players[i].team_id;
                continue;
            }
            if (team_id != s_lemipc->players[i].team_id)
                return 0;
        }
    }
    if (team_id == -1)
        return 0;
    return 1;
}

char            game_loop(t_lemipc *s_lemipc, int team_nb)
{
    t_player    *me;

    if (EINTR == sem_wait(&s_lemipc->move_lock))
        return 0;
    if (!new_player_slot(&me, s_lemipc, team_nb))
        return 0;
    sem_post(&s_lemipc->move_lock);
    while (1) {
        if (EINTR == sem_wait(&s_lemipc->move_lock))
            return 0;
        if (s_lemipc->game_started && one_team_playing(s_lemipc)) {
            LOG_MSG("Team id %d WIN !\n", me->team_id);
            s_lemipc->team_id_won = me->team_id;
            kill_player(s_lemipc, me);
        }
        if (check_player_dead(s_lemipc, me))
            return 1;
        game_play(s_lemipc, me);
        sem_post(&s_lemipc->move_lock);
        sleep(GAME_SLEEP);
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
    if (different_team && has_friend)
        s_lemipc->game_started = 1;
    return (different_team && has_friend);
}
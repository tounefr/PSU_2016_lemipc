
#include "lemipc.h"

char master_game_mode(t_lemipc *s_lemipc, t_player *me) {
}
char slave_game_mode(t_lemipc *s_lemipc, t_player *me) {
}

char game_loop(t_lemipc *s_lemipc, t_player *me) {
    while (1) {
        sem_wait(&s_lemipc->move_lock);

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

        display_map(s_lemipc);

        sem_post(&s_lemipc->move_lock);
        sleep(GAME_SLEEP);
    }
    return 1;
}

char game_start(char *path, int team_nb) {
    t_player *me;
    t_lemipc *s_lemipc;

    catch_signals();
    srand(time(NULL));
    if (!get_shared_lemipc(&s_lemipc, path))
        return 0;
    if (!new_player_slot(&me, s_lemipc, team_nb))
        return 0;
    debug_players(&s_lemipc->players);
    return game_loop(s_lemipc, me);
}

void clean_ipcs(t_lemipc *lemipc) {
    if (lemipc->nbr_players <= 0) {
        shmctl(lemipc->shm_key, IPC_RMID, NULL);
        sem_close(&lemipc->move_lock);
        LOG_MSG("IPCS cleaned\n");
    }
}

char get_shared_lemipc(t_lemipc **s_lemipc, char *path) {
    key_t key;
    int shm_key;
    int created;

    key = ftok(path, 0);
    created = 0;
    shm_key = shmget(key, sizeof(t_lemipc), SHM_R | SHM_W);
    if (-1 == shm_key) {
        shm_key = shmget(key, sizeof(t_lemipc), IPC_CREAT | SHM_R | SHM_W);
        if (-1 == shm_key)
            return exit_error(NULL, 0);
        created = 1;
    }
    LOG_MSG("Shm key=%d\n", shm_key);
    *s_lemipc = shmat(shm_key, NULL, SHM_R | SHM_W);
    if (s_lemipc == ((void*) - 1))
        return exit_error(NULL, 0);
    g_lemipc = *s_lemipc;
    if (created && !init_s_lemipc(*s_lemipc, shm_key))
        return 0;
    return 1;
}

char can_playing(t_lemipc *s_lemipc, t_player *me) {
    int i;
    char different_team;
    char has_friend;

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

char focus_ennemy(t_player *me, t_player *players) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
            players[i].team_id != me->team_id) {
            me->player_focus = &players[i];
            return 1;
        }
    }
    me->player_focus = NULL;
    return 0;
}

char check_ennemy_on_this_pos(t_player *players, t_player *player, int x, int y) {
    t_player *ennemy;

    return ((ennemy = has_player_on_this_pos(players, x, y)) &&
            ennemy->team_id != player->team_id);
}

char count_ennemies_around(t_player *players, t_player *player) {
    int x;
    int y;
    char c;

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

void kill_process(int pid) {
    if (-1 == kill(pid, SIGUSR1)) {
        LOG_MSG("Failed to kill process id=%d cause=%s\n",
                pid, strerror(errno));
    }
}

char eat_ennemies_around(t_lemipc *s_lemipc) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].is_free == 0) {
            if (count_ennemies_around(&s_lemipc->players,
                                      &s_lemipc->players[i]) > 1)
                kill_process(s_lemipc->players[i].pid);
        }
    }
}

char move_forward(t_lemipc *s_lemipc, t_player *me) {
    int max;
    t_dist_cmp dist_cmp;

    if (!me->player_focus)
        return 0;
    max = round(sqrt(MAX_PLAYERS)) - 1;

    //top
    check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y - 1), &s_lemipc->players);
    //right-top
    check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y - 1), &s_lemipc->players);
    //right
    check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y), &s_lemipc->players);
    //right-bottom
    check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y + 1), &s_lemipc->players);
    //bottom
    check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y + 1), &s_lemipc->players);
    //left-bottom
    check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y + 1), &s_lemipc->players);
    //left
    check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y), &s_lemipc->players);
    //left-top
    check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y - 1), &s_lemipc->players);

    me->x = dist_cmp.dest.x;
    me->y = dist_cmp.dest.y;

    eat_ennemies_around(s_lemipc);

    return 1;
}
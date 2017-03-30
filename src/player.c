
#include "lemipc.h"

void debug_players(t_player *players) {
    int i;
    int c;

    c = 0;
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free) {
            c++;
            printf("x=%d y=%d is_free=%d pid=%d team_id=%d is_master=%d\n",
                   players[i].x,
                   players[i].y,
                   players[i].is_free,
                   players[i].pid,
                   players[i].team_id,
                   players[i].is_master
            );
        }
    }
    printf("count = %d\n", c);
}


char init_new_player(t_player **me, int team_id, t_lemipc *lemipc) {
    t_pos xy_pos;
    t_player *player;

    xy_pos = rand_player_pos(lemipc);
    if (xy_pos.x == -1 && xy_pos.y == -1)
        return 0;
    player = &lemipc->players[xy_pos.i];
    player->is_free = 0;
    player->pid = getpid();
    player->team_id = team_id;
    player->is_master = is_player_master(&lemipc->players, team_id);
    player->x = xy_pos.x;
    player->y = xy_pos.y;
    *me = player;
    LOG_MSG("my pos x=%d y=%d\n", player->x, player->y);
    return 1;
}

char new_player_slot(t_player **me, t_lemipc *lemipc, int team_id) {
    if (lemipc->nbr_players >= MAX_PLAYERS)
        return exit_error("Failed to allocate new player slot\n", 0);
    lemipc->nbr_players++;
    LOG_MSG("Cur nbr players=%d\n", lemipc->nbr_players);
    return init_new_player(me, team_id, lemipc);
}

t_player *get_player_in_same_team(t_player *me, t_player *players) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (players[i].team_id == me->team_id &&
            players[i].is_free == 0 &&
            players[i].pid != me->pid)
            return &players[i];
    }
    return NULL;
}

char on_player_leave(t_player *me, t_lemipc *lemipc) {
    t_player *smne_in_team;

    if (me == NULL)
        return 0;
    LOG_MSG("\non_player_leave\n");
    LOG_MSG("Cur nbr players=%d\n", lemipc->nbr_players);
    if (me->is_master) {
        smne_in_team = get_player_in_same_team(me, &lemipc->players);
        if (smne_in_team) {
            LOG_MSG("PID=%d is now the master\n", smne_in_team->pid);
            smne_in_team->is_master = 1;
        }
    }
    init_s_player(me);
    lemipc->nbr_players--;
    if (lemipc->nbr_players <= 0) {
        LOG_MSG("Ending game\n");
        clean_ipcs(lemipc);
    }
    return 1;
}

t_player *get_player_slot(t_lemipc *lemipc) {
    int i;
    int my_pid;

    my_pid = getpid();
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!lemipc->players[i].is_free && lemipc->players[i].pid == my_pid)
            return &lemipc->players[i];
    }
    return NULL;
}

char is_player_master(t_player *players, int team_id) {
    int i;
    int my_pid;

    my_pid = getpid();
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
            players[i].team_id == team_id &&
            players[i].pid != my_pid)
            return 0;
    }
    return 1;
}


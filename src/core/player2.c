
#include "core.h"

char    is_player_master(t_player *players, int team_id)
{
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

char kill_player(t_lemipc *s_lemipc, t_player *player)
{
    init_s_player(player);
    s_lemipc->nbr_players--;
}
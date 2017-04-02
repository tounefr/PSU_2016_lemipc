
#include "core.h"

void            sighandler(int signum)
{
    t_player    *player;

    signum = signum;
    if (g_lemipc != NULL) {
        sem_wait(&g_lemipc->move_lock);
        if ((player = get_player_slot(g_lemipc))) {
            init_s_player(player);
            g_lemipc->nbr_players--;
            if (g_lemipc->nbr_players <= 0)
                clean_ipcs(g_lemipc);
        }
        sem_post(&g_lemipc->move_lock);
    }
    exit(0);
}

void catch_signals()
{
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);
}
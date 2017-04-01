
#include "core.h"

void sighandler(int signum) {
    if (g_lemipc != NULL)
        on_player_leave(get_player_slot(g_lemipc), g_lemipc);
    exit(0);
}

void catch_signals() {
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    signal(SIGUSR2, sighandler);
}
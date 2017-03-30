
#include "lemipc.h"

void sighandler(int signum) {
    //if (signum == SIGINT) {
        if (g_lemipc != NULL)
            on_player_leave(get_player_slot(g_lemipc), g_lemipc);
        exit(0);
    //}
}

void catch_signals() {
    int i;

    i = -1;
    while (++i < MAX_SIG)
        signal(i, sighandler);
}
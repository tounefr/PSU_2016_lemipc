
#define _GNU_SOURCE
#include <dlfcn.h>
#include <assert.h>
#include "common.h"
#include "gui_cli.h"

t_lemipc *g_lemipc = NULL;

char    check_player(t_lemipc *s_lemipc, char *c, int *x, int *y)
{
    int i2;

    i2 = -1;
    while (++i2 < MAX_PLAYERS) {
        if (!s_lemipc->players[i2].is_free &&
            s_lemipc->players[i2].x == *x &&
            s_lemipc->players[i2].y == *y &&
            s_lemipc->players[i2].team_id != -1)
            *c = s_lemipc->players[i2].team_id + '0';
    }
}

char    display_map(t_lemipc *s_lemipc) {
    int max;
    int x;
    int y;
    int i;
    int c;

    max = round(sqrt(MAX_PLAYERS));
    y = -1;
    printf("Nbr players : %d\n", s_lemipc->nbr_players);
    while (++y < max) {
        x = -1;
        while (++x < max) {
            i = (y * max) + x;
            c = '_';
            check_player(s_lemipc, &c, &x, &y);
            printf("%c", c);
        }
        printf("\n");
    }
    printf("\n");
}


void    sig_handler(int signum) {
    if (g_lemipc) {
        if (g_lemipc->nbr_players <= 0) {
            LOG_MSG("Ending game\n");
            clean_ipcs(g_lemipc);
        }
    }
    exit(0);
}

char    usage() {
    fprintf(stderr, "Usage: ./gui path\n");
    return 1;
}

int             main(int ac, char **av) {
    t_lemipc    *lemipc;

    if (ac != 2)
        return usage();
    signal(SIGINT, sig_handler);
    signal(SIGUSR1, sig_handler);
    if (!get_shared_lemipc(&lemipc, av[1]))
        return 0;
    g_lemipc = lemipc;
    while (1) {
        display_map(lemipc);
        usleep((GAME_SLEEP * 1000000) / 4);
    }
}
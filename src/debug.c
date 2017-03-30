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

char display_map(t_lemipc *s_lemipc) {
    int max;
    int x;
    int y;
    int i;
    int i2;
    int c;

    max = round(sqrt(MAX_PLAYERS));
    y = -1;
    while (++y < max) {
        x = -1;
        while (++x < max) {
            i = (y * max) + x;
            i2 = -1;
            c = '_';
            while (++i2 < MAX_PLAYERS) {
                if (!s_lemipc->players[i2].is_free &&
                    s_lemipc->players[i2].x == x &&
                    s_lemipc->players[i2].y == y &&
                    s_lemipc->players[i2].team_id != -1)
                    c = s_lemipc->players[i2].team_id + '0';
            }
            printf("%c", c);
        }
        printf("\n");
    }
    printf("\n");
}
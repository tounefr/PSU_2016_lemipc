#include "core.h"

char    focus_ennemy(t_player *me, t_player players[MAX_PLAYERS])
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

char        count_ennemies_around(t_player players[MAX_PLAYERS],
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

void    eat_ennemies_around(t_lemipc *s_lemipc)
{
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].pid != -1 &&
            s_lemipc->players[i].is_free == 0) {
            if (count_ennemies_around(s_lemipc->players,
                                      &s_lemipc->players[i]) > 1)
                kill_player(s_lemipc, &s_lemipc->players[i]);
        }
    }
}


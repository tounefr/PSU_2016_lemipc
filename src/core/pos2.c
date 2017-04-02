#include "core.h"

t_pos       get_xy_pos(int i)
{
    t_pos   pos;

    pos.x = (i % (int)round(sqrt(MAX_PLAYERS)));
    pos.y = (i / (int)round(sqrt(MAX_PLAYERS)));
    pos.i = i;
    return pos;
}

char            check_ennemy_on_this_pos(t_player players[MAX_PLAYERS],
                                         t_player *player, int x, int y)
{
    t_player    *ennemy;

    return ((ennemy = has_player_on_this_pos(players, x, y)) &&
            ennemy->team_id != player->team_id);
}

#include "core.h"

void move_forward_check_dest(t_player *me, t_dist_cmp *dist_cmp, t_lemipc *s_lemipc)
{
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x, me->y - 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y - 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x + 1, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y + 1), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y), &s_lemipc->players);
    check_dest_pos(me, dist_cmp,
                   init_pos(me->x - 1, me->y - 1), &s_lemipc->players);
}

char            move_forward(t_lemipc *s_lemipc, t_player *me)
{
    int         max;
    t_dist_cmp  dist_cmp;

    if (!me->player_focus)
        return 0;
    max = round(sqrt(MAX_PLAYERS)) - 1;
    init_dist_cmp(&dist_cmp);
    if (1 != check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y),
                            &s_lemipc->players))
        move_forward_check_dest(me, &dist_cmp, s_lemipc);
    if (dist_cmp.dest.x != -1 && dist_cmp.dest.y != -1) {
        me->x = dist_cmp.dest.x;
        me->y = dist_cmp.dest.y;
    }
    eat_ennemies_around(s_lemipc);
    return 1;
}
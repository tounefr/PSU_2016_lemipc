
#include "core.h"

char is_good_pos(int x, int y) {
    int max;

    max = round(sqrt(MAX_PLAYERS)) - 1;
    return (x >= 0 && x <= max && y >= 0 && y <= max);
}

int calc_dist(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

char check_dest_pos(t_player *me,
                    t_dist_cmp *dist_cmp,
                    t_pos test_pos,
                    t_player (*players)[MAX_PLAYERS]) {
    int v;

    if (!is_good_pos(test_pos.x, test_pos.y))
        return -1;
    v = calc_dist(test_pos.x, test_pos.y, me->player_focus->x, me->player_focus->y);
    LOG_MSG("dist=%d\n", v);
    if (NULL != has_player_on_this_pos(players, test_pos.x, test_pos.y))
        return -1;
    if (dist_cmp->min == -1 || v < dist_cmp->min)
        dist_cmp->min = v;
    if (v == dist_cmp->min) {
        dist_cmp->dest.x = test_pos.x;
        dist_cmp->dest.y = test_pos.y;
    }
    return v;
}


t_pos rand_player_pos(t_lemipc *lemipc) {
    int i;
    int available_pos;
    int rand_nbr;
    t_pos rand_pos;

    i = -1;
    available_pos = 0;
    rand_pos.x = -1;
    rand_pos.y = -1;
    while (++i < MAX_PLAYERS) {
        if (lemipc->players[i].is_free)
            available_pos++;
    }
    if (available_pos == 0)
        rand_pos;
    rand_nbr = rand() % available_pos;
    i = -1;
    available_pos = 0;
    while (++i < MAX_PLAYERS) {
        if (lemipc->players[i].is_free)
            available_pos++;
        if (available_pos == rand_nbr)
            rand_pos = get_xy_pos(i);
    }
    return rand_pos;
}

t_player *has_player_on_this_pos(t_player *players, int x, int y) {
    int i;

    i = -1;
    if (!is_good_pos(x, y))
        return NULL;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
            players[i].x == x &&
            players[i].y == y) {
            return &players[i];
        }
    }
    return NULL;
}

t_pos get_xy_pos(int i) {
    t_pos pos;

    pos.x = (i % (int)round(sqrt(MAX_PLAYERS)));
    pos.y = (i / (int)round(sqrt(MAX_PLAYERS)));
    pos.i = i;
    return pos;
}
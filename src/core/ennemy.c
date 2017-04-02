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

void            player_push(t_player **players_list, t_player *player)
{
    t_player    *last;

    if (player == NULL)
        return;
    player->next = NULL;
    if (*players_list == NULL)
        *players_list = player;
    else {
        last = *players_list;
        while (last->next)
            last = last->next;
        last->next = player;
    }
}

char    two_players_same_team(t_player *list)
{
    int team_id;

    if (!list)
        return 0;
    team_id = list->team_id;
    list = list->next;
    while (list) {
        if (list->team_id == team_id)
            return 1;
        list = list->next;
    }
    return 0;
}

char            has_more_than_2_ennemies_around(
                    t_player players[MAX_PLAYERS],
                    t_player *player)
{
    t_player    *players_list;
    int         x;
    int         y;

    x = player->x;
    y = player->y;
    players_list = NULL;
    player_push(&players_list, has_player_on_this_pos(players, x, y - 1));
    player_push(&players_list, has_player_on_this_pos(players, x + 1, y - 1));
    player_push(&players_list, has_player_on_this_pos(players, x + 1, y));
    player_push(&players_list, has_player_on_this_pos(players, x + 1, y + 1));
    player_push(&players_list, has_player_on_this_pos(players, x, y + 1));
    player_push(&players_list, has_player_on_this_pos(players, x - 1, y + 1));
    player_push(&players_list, has_player_on_this_pos(players, x - 1, y));
    player_push(&players_list, has_player_on_this_pos(players, x - 1, y - 1));
    return two_players_same_team(players_list);

}

void    eat_ennemies_around(t_lemipc *s_lemipc)
{
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].pid != -1 &&
            s_lemipc->players[i].is_free == 0) {
            if (has_more_than_2_ennemies_around(s_lemipc->players,
                                                &s_lemipc->players[i]))
                kill_player(s_lemipc, &s_lemipc->players[i]);
        }
    }
}


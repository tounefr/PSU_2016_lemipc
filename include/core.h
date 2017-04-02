//
// Created by thomas on 01/04/17.
//

#ifndef PSU_2016_LEMIPC_CORE_H
#define PSU_2016_LEMIPC_CORE_H

#include "common.h"

#define MAX_SIG 31

typedef struct s_pos
{
    int x;
    int y;
    int i;
} t_pos;

typedef struct s_dist_cmp
{
    t_pos dest;
    int min;
    t_pos my_pos;
    t_pos ennemy_pos;
} t_dist_cmp;

extern t_lemipc *g_lemipc;

t_player *get_player_in_same_team(t_player *me, t_player *players);
char on_player_leave(t_player *me, t_lemipc *lemipc);
t_player *get_player_slot(t_lemipc *lemipc);
char is_player_master(t_player *players, int team_id);
t_pos get_xy_pos(int i);
t_pos rand_player_pos(t_lemipc *lemipc);
void debug_players(t_player *players);
char init_new_player(t_player **me, int team_id, t_lemipc *lemipc);
char new_player_slot(t_player **me, t_lemipc *lemipc, int team_id);
void init_s_player(t_player *player);
char init_s_lemipc(t_lemipc *lemipc, int shm_key);
char can_playing(t_lemipc *s_lemipc, t_player *me);
char focus_ennemy(t_player *me, t_player players[MAX_PLAYERS]);
char display_map(t_lemipc *s_lemipc);
char is_good_pos(int x, int y);
t_pos init_pos(int x, int y);
char check_dest_pos(t_player *me,
                    t_dist_cmp *dist_cmp,
                    t_pos test_pos,
                    t_player players[MAX_PLAYERS]);
void eat_ennemies_around(t_lemipc *s_lemipc);
char move_forward(t_lemipc *s_lemipc, t_player *me);
char game_loop(t_lemipc *s_lemipc, int team_nb);
char game_start(char *path, int team_nb);
void game_play(t_lemipc *s_lemipc, t_player *me);
void clean_ipcs(t_lemipc *lemipc);
void sighandler(int signum);
char count_ennemies_around(t_player players[MAX_PLAYERS], t_player *player);
t_player *has_player_on_this_pos(t_player *players, int x, int y);
//char check_ennemy_on_this_pos(t_player (*players)[MAX_PLAYERS], t_player *player, int x, int y);
char check_ennemy_on_this_pos(t_player players[MAX_PLAYERS], t_player *player, int x, int y);
char get_shr_mem_handle(t_lemipc **s_lemipc, char *path);
char	exit_error(char *msg, char exit_number);
int  abs(int x);
char is_nbr(char *str);
void catch_signals();
void kill_player(t_lemipc *s_lemipc, t_player *player);
char check_player_dead(t_lemipc *s_lemipc, t_player *me);
void init_dist_cmp(t_dist_cmp *dist_cmp);
char one_team_playing(t_lemipc *s_lemipc);

#endif //PSU_2016_LEMIPC_CORE_H

/*
** lemipc.h for  in /home/linder/cours/system unix/PSU_2016_lemipc/include
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 10:58:32 2017 linder
** Last update Tue Mar 28 11:46:53 2017 linder
*/

#ifndef _LEMIPC_H_
# define _LEMIPC_H_

#include <stdio.h>
#include <semaphore.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <math.h>
#include <signal.h>

#define LOG 1
#if LOG
    #define LOG_MSG(...) fprintf(stderr, __VA_ARGS__)
#else
    #define LOG_MSG(...)
#endif

#define MAX_SIG 31
#define MAX_PLAYERS 500
#define GAME_SLEEP 1

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

typedef struct s_player
{
    int x;
    int y;
    int pid;
    int is_free;
    int team_id;
    char is_master;
    struct s_player *player_focus;
} t_player;

typedef struct  s_lemipc
{
    sem_t       move_lock;
    int         shm_key;
    int         nbr_players;
    t_player    players[MAX_PLAYERS];
}               t_lemipc;

extern t_lemipc *g_lemipc;

// error.c
char	exit_error(char *msg, char exit_number);

// util.c
char is_nbr(char *str);

t_player *get_player_in_same_team(t_player *me, t_player (*players)[MAX_PLAYERS]);
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
char get_shared_lemipc(t_lemipc **s_lemipc, char *path);
char can_playing(t_lemipc *s_lemipc, t_player *me);
char focus_ennemy(t_player *me, t_player *players);
char display_map(t_lemipc *s_lemipc);
char is_good_pos(int x, int y);
int  abs(int x);
int calc_dist(int x1, int y1, int x2, int y2);
t_pos init_pos(int x, int y);
char check_dest_pos(t_player *me,
                    t_dist_cmp *dist_cmp,
                    t_pos test_pos,
                    t_player (*players)[MAX_PLAYERS]);
char eat_ennemies_around(t_lemipc *s_lemipc);
char move_forward(t_lemipc *s_lemipc, t_player *me);
char game_loop(t_lemipc *s_lemipc, t_player *me);
char game_start(char *path, int team_nb);
void clean_ipcs(t_lemipc *lemipc);
void sighandler(int signum);
char count_ennemies_around(t_player (*players)[MAX_PLAYERS], t_player *player);
t_player *has_player_on_this_pos(t_player *players, int x, int y);
//char check_ennemy_on_this_pos(t_player (*players)[MAX_PLAYERS], t_player *player, int x, int y);
char check_ennemy_on_this_pos(t_player (*players)[MAX_PLAYERS], t_player *player, int x, int y);

#endif /* !_LEMIPC_H_ */

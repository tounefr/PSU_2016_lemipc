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

#define MAX_PLAYERS 1000
#define GAME_SLEEP 1
#define SHARED_MEM_LIBRARY "./liblemipc_shared.so"

typedef struct      s_rgb
{
    unsigned char   r;
    unsigned char	g;
    unsigned char	b;
}		            t_rgb;

typedef struct s_player
{
    int x;
    int y;
    int pid;
    int is_free;
    int team_id;
    char is_master;
    t_rgb       color;
    struct s_player *player_focus;
    struct s_player *next;
} t_player;

typedef struct  s_lemipc
{
    sem_t       move_lock;
    int         shm_key;
    int         nbr_players;
    t_player    players[MAX_PLAYERS];
    char        game_started;
    int         team_id_won;
}               t_lemipc;

char is_nbr(char *str);
int  abs(int x);
char	exit_error(char *msg, char exit_number);
char get_shared_lemipc(t_lemipc **s_lemipc, char *path);
void init_s_player(t_player *player);
char init_s_lemipc(t_lemipc *lemipc, int shm_key);
void clean_ipcs(t_lemipc *lemipc);

#endif /* !_LEMIPC_H_ */

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

#define MAX_PLAYERS 500
#define GAME_SLEEP 1
#define SHARED_MEM_LIBRARY "./liblemipc_shared.so"

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

char is_nbr(char *str);
int  abs(int x);
char	exit_error(char *msg, char exit_number);
char get_shared_lemipc(t_lemipc **s_lemipc, char *path);

#endif /* !_LEMIPC_H_ */

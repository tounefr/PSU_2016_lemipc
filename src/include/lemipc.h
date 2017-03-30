/*
** lemipc.h for  in /home/linder/cours/system unix/PSU_2016_lemipc/include
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 10:58:32 2017 linder
** Last update Tue Mar 28 18:35:34 2017 linder
*/

#ifndef _LEMIPC_H_
# define _LEMIPC_H_

#include <stdio.h>
#include <semaphore.h>

<<<<<<< HEAD
#define LOG 1
#if LOG
    #define LOG_MSG(...) fprintf(stderr, __VA_ARGS__)
#else
    #define LOG_MSG(...)
#endif

#define MAX_PLAYERS 100
=======
/*typedef struct s_ipcs
{

};*/
>>>>>>> 0e9a1a923d7774ad901de08feb5fffd1784d29cc

typedef struct s_pos
{
    int x;
    int y;
    int i;
} t_pos;

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
    sem_t       lock;
    int         shm_key;
    int         nbr_players;
    t_player    players[MAX_PLAYERS];
}               t_lemipc;

extern t_lemipc *g_lemipc;

// error.c
char	exit_error(char *msg, char exit_number);

// util.c
char is_nbr(char *str);

#endif /* !_LEMIPC_H_ */

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

# define MAP_WIDTH 100
# define MAP_HEIGHT 100

/*typedef struct s_ipcs
{

};*/

typedef struct s_player
{
    int x;
    int y;

} t_player;

typedef struct  s_ipc_shared
{
    sem_t       *lock_map;
    t_player    **players;
}               t_ipc_shared;

// error.c
char	exit_error(char *msg, char exit_number);

// util.c
char is_nbr(char *str);

#endif /* !_LEMIPC_H_ */

/*
** signal.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:55:10 2017 linder
** Last update Sun Apr  2 18:55:38 2017 linder
*/

#include "core.h"

void		sighandler(int signum)
{
  t_player	*player;

  signum = signum;
  if (g_lemipc != NULL)
    {
      sem_wait(&g_lemipc->move_lock);
      if ((player = get_player_slot(g_lemipc)))
	{
	  init_s_player(player);
	  g_lemipc->nbr_players--;
	  if (g_lemipc->nbr_players <= 0)
	    clean_ipcs(g_lemipc);
        }
      sem_post(&g_lemipc->move_lock);
    }
  exit(0);
}

void	catch_signals()
{
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  signal(SIGUSR2, sighandler);
}

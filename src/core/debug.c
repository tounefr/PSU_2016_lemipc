/*
** debug.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:45:27 2017 linder
** Last update Sun Apr  2 18:45:50 2017 linder
*/

#include "core.h"

void	debug_players(t_player *players)
{
  int	i;
  int	c;

  c = 0;
  i = -1;
  while (++i < MAX_PLAYERS)
    {
      if (!players[i].is_free)
	{
	  c++;
	  printf("x=%d y=%d is_free=%d pid=%d team_id=%d is_master=%d\n",
		 players[i].x,
		 players[i].y,
		 players[i].is_free,
		 players[i].pid,
		 players[i].team_id,
		 players[i].is_master);
        }
    }
  printf("count = %d\n", c);
}

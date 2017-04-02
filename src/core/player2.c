/*
** player2.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:59:01 2017 linder
** Last update Sun Apr  2 19:00:03 2017 linder
*/

#include "core.h"

char	is_player_master(t_player *players, int team_id)
{
  int	i;
  int	my_pid;

  my_pid = getpid();
  i = -1;
  while (++i < MAX_PLAYERS)
    {
      if (!players[i].is_free &&
	  players[i].team_id == team_id &&
	  players[i].pid != my_pid)
	return (0);
    }
  return (1);
}

char	check_player_dead(t_lemipc *s_lemipc, t_player *me)
{
  if (me->pid != -1)
    return (0);
  init_s_player(me);
  sem_post(&s_lemipc->move_lock);
  if (s_lemipc->nbr_players <= 0)
    clean_ipcs(s_lemipc);
  return (1);
}

void	kill_player(t_lemipc *s_lemipc, t_player *player)
{
  init_s_player(player);
  s_lemipc->nbr_players--;
}

t_rgb	get_player_color(t_player players[MAX_PLAYERS], int team_id)
{
  int	i;

  i = -1;
  while (++i < MAX_PLAYERS)
    {
      if (!players[i].is_free && team_id == players[i].team_id)
	return (players[i].color);
    }
  return (init_rgb(rand() % 200, rand() % 200, rand() % 200));
}

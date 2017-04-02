/*
** pos2.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 19:00:09 2017 linder
** Last update Sun Apr  2 19:01:00 2017 linder
*/

#include "core.h"

t_pos	get_xy_pos(int i)
{
  t_pos	pos;

  pos.x = (i % (int)round(sqrt(MAX_PLAYERS)));
  pos.y = (i / (int)round(sqrt(MAX_PLAYERS)));
  pos.i = i;
  return (pos);
}

char	check_ennemy_on_this_pos(t_player players[MAX_PLAYERS],
                                         t_player *player, int x, int y)
{
  t_player	*ennemy;

  return ((ennemy = has_player_on_this_pos(players, x, y)) &&
	  ennemy->team_id != player->team_id);
}

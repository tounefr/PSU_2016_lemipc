/*
** init.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:57:56 2017 linder
** Last update Sun Apr  2 18:58:41 2017 linder
*/

#include "core.h"

void	init_s_player(t_player *player)
{
  player->x = -1;
  player->y = -1;
  player->pid = -1;
  player->is_free = 1;
  player->team_id = -1;
  player->is_master = -1;
}

t_pos	init_pos(int x, int y)
{
  t_pos	pos;

  pos.x = x;
  pos.y = y;
  return (pos);
}

t_rgb       init_rgb(int r, int g, int b)
{
  t_rgb	rgb;

  rgb.r = r;
  rgb.g = g;
  rgb.b = b;
  return (rgb);
}

void	init_dist_cmp(t_dist_cmp *dist_cmp)
{
  dist_cmp->min = -1;
  dist_cmp->dest.x = -1;
  dist_cmp->dest.y = -1;
}

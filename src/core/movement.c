/*
** movement.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:49:26 2017 linder
** Last update Sun Apr  2 19:07:30 2017 linder
*/

#include "core.h"

void	move_forward_check_dest(t_player *me, t_dist_cmp *dist_cmp,
				t_lemipc *s_lemipc)
{
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x, me->y - 1), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x + 1, me->y - 1), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x + 1, me->y), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x + 1, me->y + 1), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x, me->y + 1), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x - 1, me->y + 1), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x - 1, me->y), s_lemipc->players);
  check_dest_pos(me, dist_cmp,
		 init_pos(me->x - 1, me->y - 1), s_lemipc->players);
}

char		move_forward(t_lemipc *s_lemipc, t_player *me)
{
  t_dist_cmp	dist_cmp;

  if (!me->player_focus)
    return (0);
  init_dist_cmp(&dist_cmp);
  if (1 != check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y),
			  s_lemipc->players))
    move_forward_check_dest(me, &dist_cmp, s_lemipc);
  if (dist_cmp.dest.x != -1 && dist_cmp.dest.y != -1)
    {
      me->x = dist_cmp.dest.x;
      me->y = dist_cmp.dest.y;
    }
  eat_ennemies_around(s_lemipc);
  return (1);
}

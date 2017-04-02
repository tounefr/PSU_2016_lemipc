/*
** player.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 18:50:07 2017 linder
** Last update Sun Apr  2 18:52:04 2017 linder
*/

#include "core.h"

char		init_new_player(t_player **me, int team_id, t_lemipc *lemipc)
{
  t_pos		xy_pos;
  t_player	*player;

    xy_pos = rand_player_pos(lemipc);
    if (xy_pos.x == -1 && xy_pos.y == -1)
        return 0;
    player = &lemipc->players[xy_pos.i];
    player->color = get_player_color(lemipc->players, team_id);
    player->is_free = 0;
    player->pid = getpid();
    player->team_id = team_id;
    player->is_master = is_player_master(lemipc->players, team_id);
    player->x = xy_pos.x;
    player->y = xy_pos.y;
    *me = player;
    return 1;
}

char		new_player_slot(t_player **me, t_lemipc *lemipc, int team_id)
{
  if (lemipc->nbr_players >= MAX_PLAYERS)
    return (exit_error("Failed to allocate new player slot\n", 0));
  lemipc->nbr_players++;
  return (init_new_player(me, team_id, lemipc));
}

t_player	*get_player_in_same_team(t_player *me, t_player *players)
{
  int		i;

  i = -1;
  while (++i < MAX_PLAYERS)
    {
      if (players[i].team_id == me->team_id &&
	  players[i].is_free == 0 &&
	  players[i].pid != me->pid)
	return (&players[i]);
    }
  return (NULL);
}

char		on_player_leave(t_player *me, t_lemipc *lemipc)
{
  if (me == NULL)
    return 0;
  printf("You've been killed\n");
  init_s_player(me);
  lemipc->nbr_players--;
  if (lemipc->nbr_players <= 0)
    {
      LOG_MSG("Ending game\n");
      clean_ipcs(lemipc);
    }
  return (1);
}

t_player	*get_player_slot(t_lemipc *lemipc)
{
  int		i;
  int		my_pid;

  my_pid = getpid();
  i = -1;
  while (++i < MAX_PLAYERS)
    {
      if (!lemipc->players[i].is_free && lemipc->players[i].pid == my_pid)
	return (&lemipc->players[i]);
    }
  return (NULL);
}

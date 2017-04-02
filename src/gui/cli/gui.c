/*
** gui.c for  in /home/linder/PSU_2016_lemipc/src/gui/cli
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 19:02:46 2017 linder
** Last update Sun Apr  2 19:09:44 2017 linder
*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <assert.h>
#include "common.h"
#include "gui_cli.h"

t_lemipc	*g_lemipc = NULL;

void	check_player(t_lemipc *s_lemipc, int *c, int *x, int *y)
{
  int	i2;

  i2 = -1;
  while (++i2 < MAX_PLAYERS)
    {
      if (!s_lemipc->players[i2].is_free &&
	  s_lemipc->players[i2].x == *x &&
	  s_lemipc->players[i2].y == *y &&
	  s_lemipc->players[i2].team_id != -1)
	*c = s_lemipc->players[i2].team_id + '0';
    }
}

char	display_map(t_lemipc *s_lemipc)
{
  int	max;
  int	x;
  int	y;
  int	c;

  max = round(sqrt(MAX_PLAYERS));
  y = -1;
  printf("Nbr players : %d\n", s_lemipc->nbr_players);
  while (++y < max) {
    x = -1;
    while (++x < max)
      {
	c = '_';
	check_player(s_lemipc, &c, &x, &y);
	printf("%c", c);
      }
    printf("\n");
  }
  printf("\n");
  if (s_lemipc->team_id_won != -1)
    {
      printf("Team id %d won !\n", s_lemipc->team_id_won);
      return (1);
    }
  return (0);
}

void	sig_handler(int signum)
{
  signum = signum;
  if (g_lemipc)
    {
      if (g_lemipc->nbr_players <= 0)
	{
	  LOG_MSG("Ending game\n");
	  clean_ipcs(g_lemipc);
        }
    }
  exit(0);
}

char	usage()
{
  fprintf(stderr, "Usage: ./gui path\n");
  return (1);
}

int             main(int ac, char **av)
{
    t_lemipc    *lemipc;

    if (ac != 2)
        return usage();
    signal(SIGINT, sig_handler);
    signal(SIGUSR1, sig_handler);
    if (!get_shared_lemipc(&lemipc, av[1]))
        return 0;
    g_lemipc = lemipc;
    while (1) {
        if (display_map(lemipc)) {
            clean_ipcs(lemipc);
            return 0;
        }
        usleep((GAME_SLEEP * 1000000) / 10);
    }
}

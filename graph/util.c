/*
** util.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 14:31:18 2017 linder
** Last update Thu Mar 30 16:39:47 2017 linder
*/

#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include "gui.h"

int		check_nbr(int nbr, int size)
{
  float		nb;
  float		res;
  bool		good;
  int		ret;

  good = false;
  nb = (float)nbr;
  while (good == false)
    {
      res = size / nb;
      if (roundf(res) == res)
	good = true;
      nb++;
    }
  ret = (int)res;
  return (ret);
}

static void	sighandler(int signum)
{
  if (signum == SIGINT)
    {
      printf("\n");
      exit(0);
    }
}

void		catch_signals()
{
  int		i;

  i = -1;
  while (++i < MAX_SIG)
    signal(i, sighandler);
}

/*
** util.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 14:31:18 2017 linder
** Last update Sun Apr  2 14:40:27 2017 linder
*/

#include <signal.h>
#include <math.h>
#include <stdbool.h>
#include "common.h"
#include "gui_sdl.h"

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

void	sighandler(int signum)
{
    exit(0);
}

void		catch_signals()
{
  signal(SIGINT, sighandler);
}
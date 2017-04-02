/*
** util.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 19:01:51 2017 linder
** Last update Sun Apr  2 19:02:30 2017 linder
*/

#include "common.h"

char	is_nbr(char *str)
{
  int	i;
  int	len;

  len = strlen(str);
  i = -1;
  while (++i < len)
    {
      if (str[i] < '0' || str[i] > '9')
	return (0);
    }
  return (1);
}

int	abs(int x)
{
  if (x < 0)
    return (-x);
  return (x);
}

char	exit_error(char *msg, char exit_number)
{
  if (msg == NULL)
    fprintf(stderr, "%s\n", strerror(errno));
  else
    fprintf(stderr, "%s\n", msg);
  return (exit_number);
}

int rand_nbr(int min, int max)
{
    return (rand() % max) + min;
}
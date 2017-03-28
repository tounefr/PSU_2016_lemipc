/*
** util.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/src
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 18:29:55 2017 linder
** Last update Tue Mar 28 18:34:31 2017 linder
*/

#include <string.h>

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

/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 10:48:20 2017 linder
** Last update Tue Mar 28 10:54:31 2017 linder
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void	usage()
{
  printf("Usage : ./lemipc path_to_key team_number\n\n");
  printf("path_to_key is a valid path that will be use by ftok\n");
  printf("team_number is the team number assigned to the current player\n");
  exit(0);
}

int	main(int ac, char **av)
{
  if (ac == 2 && strcmp(av[1], "-h") == 0)
    usage();
  if (ac != 3)
    {
      fprintf(stderr, "The number of arguments should be 3. Use ./lemipc -h for more details\n");
      exit(84);
    }
}

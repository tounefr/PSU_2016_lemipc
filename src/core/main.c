/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 10:48:20 2017 linder
** Last update Tue Mar 28 14:42:17 2017 linder
*/

#include "core.h"

t_lemipc *g_lemipc = NULL;

static char usage()
{
    printf("Usage : ./lemipc path_to_key team_number\n\n"
                   "path_to_key is a valid path that will be use by ftok\n"
                   "team_number is the team number "
                    "assigned to the current player\n");
    return 84;
}

int main(int ac, char **av)
{
    if (ac != 3 ||
        !strcmp(av[1], "-h") ||
        !is_nbr(av[2]))
        return usage();
    return !game_start(av[1], atoi(av[2]));
}

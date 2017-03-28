/*
** error.c for  in /home/linder/cours/system unix/PSU_2016_lemipc
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 11:42:43 2017 linder
** Last update Tue Mar 28 12:02:36 2017 linder
*/

#include <stdlib.h>
#include <stdio.h>
#include "../include/lemipc.h"

void	exit_error(char *msg, int exit_number)
{
  fprintf(stderr, "%s", msg);
  exit(exit_number);
}

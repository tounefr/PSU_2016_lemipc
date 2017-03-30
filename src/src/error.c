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
#include <string.h>
#include <errno.h>
#include "lemipc.h"

char	exit_error(char *msg, char exit_number)
{
    if (msg == NULL)
        fprintf(stderr, "%s\n", strerror(errno));
    else
      fprintf(stderr, "%s\n", msg);
  return exit_number;
}

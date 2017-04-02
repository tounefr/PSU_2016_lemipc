/*
** rand_rgb.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 10:27:56 2017 linder
** Last update Sat Apr  1 17:33:09 2017 linder
*/

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gui_sdl.h"

void            rand_rgb(t_rgb *color)
{
  color->r = rand()%220+30;
  color->g = rand()%220+30;
  color->b = rand()%220+30;
}

void		set_rgb(t_rgb *color, char *name)
{
  if (strcmp(name, "black") == 0)
    {
      color->r = 0;
      color->g = 0;
      color->b = 0;
    }
  if (strcmp(name, "white") == 0)
    {
      color->r = 255;
      color->g = 255;
      color->b = 255;
    }
}

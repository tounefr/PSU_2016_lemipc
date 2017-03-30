/*
** clear_win.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 10:41:55 2017 linder
** Last update Thu Mar 30 10:48:54 2017 linder
*/

#include "gui.h"

void		clear_win(int height, int width, SDL_Renderer *renderer, t_rgb *color)
{
  int		i;
  int		j;

  j = 0;
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  while (j < width) {
    i = 0;
    while (i < height)
      SDL_RenderDrawPoint(renderer, j, i++);
    j++;
  }
  SDL_RenderPresent(renderer);
  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
}

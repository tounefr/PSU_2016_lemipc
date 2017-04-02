/*
** clear_win.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 10:41:55 2017 linder
** Last update Sat Apr  1 17:32:30 2017 linder
*/

#include "common.h"
#include "gui_sdl.h"

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

void    draw_square(SDL_Renderer *renderer,
                 t_board *board,
                 int x, int y, t_rgb *color)
{
  int   i;
  int   j;

  SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, 255);
  i = (x - 1) * board->step;
  while (i < (board->step + (x - 1) * board->step)) {
    j = (y - 1) * board->step;
    while (j < (board->step + (y - 1) * board->step))
      SDL_RenderDrawPoint(renderer, i, j++);
    i++;
  }
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void    draw_grille(SDL_Renderer *renderer, t_board *board)
{
  int   i;
  int   j;
  int   k;
  int   step;

  step = check_nbr(sqrt(board->nb_case), board->height);
  k = step;
  while (k < board->width) {
    i = 0;
    while (i < board->height)
      SDL_RenderDrawPoint(renderer, k, i++);
    k += step;
  }
  k = step;
  while (k < board->height) {
    j = 0;
    while (j < board->width)
      SDL_RenderDrawPoint(renderer, j++, k);
    k += step;
  }
  board->step = step;
  board->final_case_nb = (k / step);
}

char on_event_exit(SDL_Event *event)
{
  if (event->type == SDL_QUIT ||
      event->key.keysym.sym == SDLK_ESCAPE)
    return (1);
  return (0);
}

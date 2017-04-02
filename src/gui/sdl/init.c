/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Wed Mar 29 23:30:25 2017 linder
** Last update Sun Apr  2 16:53:02 2017 linder
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common.h"
#include "gui_sdl.h"

t_lemipc	*g_lemipc = NULL;

void		draw_square(SDL_Renderer *renderer, t_board *board, int x, int y)
{
  int           i;
  int           j;
  
  i = (x-1) * board->step;
  while (i < (board->step + (x-1) * board->step))
    {
      j = (y-1) * board->step;
      while (j < (board->step + (y-1) * board->step))
	SDL_RenderDrawPoint(renderer, i, j++);
      i++;
    }
  SDL_RenderPresent(renderer);
}

void		draw_grille(SDL_Renderer *renderer, t_board *board)
{
  int		i;
  int		j;
  int		k;
  int		step;

  printf("start\n");
  step = check_nbr(sqrt(board->nb_case), board->height);
  k = step;
  while (k < board->width)
    {
      i = 0;
      while (i < board->height)
	SDL_RenderDrawPoint(renderer, k, i++);
      k += step;
    }
  k = step;
  while (k < board->height)
    {
      j = 0;
      while (j < board->width)
	SDL_RenderDrawPoint(renderer, j++, k);
      k += step;
    }
  SDL_RenderPresent(renderer);
  board->step = step;
  board->final_case_nb = (k / step);
  printf("end\n");
}

int		check_player(t_lemipc *s_lemipc, int *x, int *y)
{
  int i2;

  i2 = -1;
  while (++i2 < MAX_PLAYERS) {
    if (!s_lemipc->players[i2].is_free &&
	s_lemipc->players[i2].x == *x &&
	s_lemipc->players[i2].y == *y &&
	s_lemipc->players[i2].team_id != -1)
      return (1);
  }
  return (0);
}


int		init(t_board *board, t_rgb *color_rgb, t_lemipc *lemipc)
{
  SDL_Window	*fenetre;
  SDL_Renderer	*renderer;
  int		y;
  int		x;

  if (SDL_VideoInit(NULL) < 0)
    return (84);
  if ((fenetre = SDL_CreateWindow(board->name, SDL_WINDOWPOS_CENTERED,
				  SDL_WINDOWPOS_CENTERED, board->width, board->height, 0)) == NULL)
    return (84);
  if ((renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED |
				     SDL_RENDERER_PRESENTVSYNC)) == NULL)
    return (84);
  while (1)
    {
      printf("START_INIT\n");
      if ((need_quit()) == 1)
	return (0);
      while (y++ < round(sqrt(MAX_PLAYERS)))
	{
	  while (x++ < round(sqrt(MAX_PLAYERS)))
	    {
	      SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	      SDL_RenderClear(renderer);
	      clear_win(board->height, board->width, renderer, color_rgb);
	      draw_grille(renderer, board);
	      if (check_player(lemipc, &x, &y) == 1)
		draw_square(renderer, board, x, y);
	    }
	}
      SDL_Delay(1000);
      printf("refreshed\n");
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
  return (0);
}

int		main(int ac, char **av)
{
  t_rgb		color_rgb;
  t_board	board;
  t_lemipc	*lemipc;

  printf("START\n");
  if (ac != 2)
    {
      fprintf(stderr, "Usage: ./gui path\n");
      return (1);
    }
  srand(time(NULL));
  catch_signals();
  if (!get_shared_lemipc(&lemipc, av[1]))
    {
      fprintf(stderr, "Error get shared lemipc\n");
      return (0);
    }
  g_lemipc = lemipc;
  board.height = 400;
  board.width = 400;
  board.nb_case = 56;
  board.name = "LEMIPC";
  init(&board, &color_rgb, lemipc);
  return (0);
}

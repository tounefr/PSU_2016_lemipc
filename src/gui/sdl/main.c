/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Wed Mar 29 23:30:25 2017 linder
** Last update Wed Mar 29 23:30:31 2017 linder
*/

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

int		check_nbr(int nbr, int size)
{
  float nb;
  float res;
  bool good;
  int ret;

  good = false;
  nb = (float)nbr;
  while (good == false)
    {
      res = size / nb;
      if (roundf(res) == res)
	good = true;
      nb++;
    }
  ret = (int)res;
  return (ret);
}

int		draw_grille(SDL_Renderer *renderer, int height, int width, int nbr_case)
{
  int		i;
  int		j;
  int		k;
  int		count;
  

  count = height / sqrt(nbr_case);
  count = check_nbr(sqrt(nbr_case), height);
  k = count;
  while (k < width) {
    i = 0;
    while (i < height) {
      SDL_RenderDrawPoint(renderer, k, i);
      i++;
    }
    k += count;
  }
  k = count;
  while (k < height) {
    j = 0;
    while (j < width) {
      SDL_RenderDrawPoint(renderer, j, k);
      j++;
    }
    k += count;
  }
  SDL_RenderPresent(renderer);
  return (k / count);
}

void		clear_win(int height, int width, SDL_Renderer *renderer)
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
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

int		main(int argc, char **argv)
{
  SDL_Window	*fenetre;
  SDL_Renderer	*renderer;
  int		height = 800;
  int		width = 800;
  int		nbr_case = 49;
  int		i;

  if (SDL_VideoInit(NULL) < 0)
    return (84);
  if ((fenetre = SDL_CreateWindow("Coucou", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
				  width, height , 0)) == NULL)
    return (84);
  if ((renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED |
				     SDL_RENDERER_PRESENTVSYNC)) == NULL)
    return (84);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  i = draw_grille(renderer, height, width, nbr_case);
  SDL_Delay(2000);
  printf("%d\n", i);

  clear_win(height, width, renderer);

  i = draw_grille(renderer, height, width, 256);
  SDL_Delay(2000);
  printf("%d\n", i);

  clear_win(height, width, renderer);
  
  i = draw_grille(renderer, height, width, 580);
  SDL_Delay(2000);
  printf("%d\n", i);

  clear_win(height, width, renderer);

  i = draw_grille(renderer, height, width, 1000);
  SDL_Delay(2000);
  printf("%d\n", i);

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(fenetre);
  SDL_Quit();
}

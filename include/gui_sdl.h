/*
** gui.h for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Thu Mar 30 10:07:42 2017 linder
** Last update Sun Apr  2 13:21:59 2017 linder
*/

#ifndef _GUI_H_
# define _GUI_H_

#include <SDL2/SDL.h>

#define MAX_SIG 31

typedef struct	s_board
{
  int		height;
  int		width;
  int		nb_case;
  int		step;
  int		final_case_nb;
  char		*name;
}		t_board;

/*
*** clear_win.c
*/

void		clear_win(int, int, SDL_Renderer *, t_rgb *);

/*
*** util.c
*/

int		check_nbr(int, int);
void		catch_signals();
int		need_quit();
void draw_grille(SDL_Renderer *renderer, t_board *board);
void draw_square(SDL_Renderer *renderer,
                 t_board *board,
                 int x, int y, t_rgb *color);

#endif /* !_GUI_H_ */

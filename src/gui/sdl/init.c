/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Wed Mar 29 23:30:25 2017 linder
** Last update Sun Apr  2 22:44:45 2017 linder
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common.h"
#include "gui_sdl.h"

t_lemipc *g_lemipc = NULL;

void clear_screen(SDL_Renderer *renderer)
{
    SDL_Rect rect;

    rect.x = 0;
    rect.y = 0;
    rect.w = WIN_WIDTH;
    rect.h = WIN_HEIGHT;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void    draw_players(SDL_Renderer *renderer,
    t_board *board, t_player players[MAX_PLAYERS])
{
    int i2;

    i2 = -1;
    while (++i2 < MAX_PLAYERS) {
      if (!players[i2].is_free && players[i2].team_id != -1) {
	draw_square(renderer, board, players[i2].x,
		    players[i2].y, &players[i2].color);
      }
    }
}

void            main_loop(t_board *board,
                          t_lemipc *lemipc,
                          SDL_Renderer *renderer)
{
    SDL_Event	event;

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        clear_screen(renderer);
        draw_grille(renderer, board);
        draw_players(renderer, board, lemipc->players);
        SDL_RenderPresent(renderer);
        SDL_Delay(100);
    }
}

int                 init(t_board *board, t_lemipc *lemipc)
{
    SDL_Window      *fenetre;
    SDL_Renderer    *renderer;
    int             y;
    int             x;

    if (SDL_VideoInit(NULL) < 0)
        return (84);
    if ((fenetre = SDL_CreateWindow(board->name, SDL_WINDOWPOS_CENTERED,
              SDL_WINDOWPOS_CENTERED,
              board->width, board->height, 0)) == NULL)
        return (84);
    if ((renderer = SDL_CreateRenderer(fenetre, -1,
				       SDL_RENDERER_ACCELERATED
				       | SDL_RENDERER_PRESENTVSYNC)) == NULL)
        return (84);
    main_loop(board, lemipc, renderer);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return (0);
}

int             main(int ac, char **av)
{
    t_board     board;
    t_lemipc    *lemipc;

    if (ac != 2) {
        fprintf(stderr, "Usage: ./gui path\n");
        return (1);
    }
    srand(time(NULL));
    catch_signals();
    if (!get_shared_lemipc(&lemipc, av[1])) {
        fprintf(stderr, "Error get shared lemipc\n");
        return (0);
    }
    g_lemipc = lemipc;
    board.height = WIN_HEIGHT;
    board.width = WIN_WIDTH;
    board.nb_case = MAX_PLAYERS;
    board.name = "LEMIPC";
    init(&board, lemipc);
    return (0);
}

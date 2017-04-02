/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Wed Mar 29 23:30:25 2017 linder
** Last update Sun Apr  2 12:27:24 2017 linder
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "gui_sdl.h"
#include "common.h"

void draw_grille(SDL_Renderer *renderer, t_board *board) {
    int i;
    int j;
    int k;
    int step;

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
    SDL_RenderPresent(renderer);
    board->step = step;
    board->final_case_nb = (k / step);
}

int init(t_board *board, t_rgb *color_rgb) {
    SDL_Window *fenetre;
    SDL_Renderer *renderer;

    if (SDL_VideoInit(NULL) < 0)
        return (84);
    if ((fenetre = SDL_CreateWindow(board->name, SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, board->width, board->height, 0)) == NULL)
        return (84);
    if ((renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC)) == NULL)
        return (84);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    draw_grille(renderer, board);
    SDL_Delay(10000000);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return (0);
}

int main() {
    t_rgb color_rgb;
    t_board board;

    srand(time(NULL));
    catch_signals();
    board.height = 400;
    board.width = 400;
    board.nb_case = 56;
    board.name = "LEMIPC";
    set_rgb(&color_rgb, "black");
    if ((init(&board, &color_rgb)) != 0)
        return (84);
    return (0);
}

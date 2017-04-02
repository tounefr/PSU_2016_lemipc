/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc/graph
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Wed Mar 29 23:30:25 2017 linder
** Last update Sun Apr  2 18:16:48 2017 linder
*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "common.h"
#include "gui_sdl.h"

t_lemipc *g_lemipc = NULL;
char g_running = 1;

void draw_square(SDL_Renderer *renderer, t_board *board, int x, int y, t_rgb *color) {
    int i;
    int j;

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
    board->step = step;
    board->final_case_nb = (k / step);
}

/*
int check_player(t_lemipc *s_lemipc, int *x, int *y) {
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
 */

char on_event_exit(SDL_Event *event)
{
    if (event->type == SDL_QUIT ||
        event->key.keysym.sym == SDLK_ESCAPE)
        return (1);
    return (0);
}

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


void draw_players(SDL_Renderer *renderer, t_board *board, t_player players[MAX_PLAYERS])
{
    int i2;

    i2 = -1;
    while (++i2 < MAX_PLAYERS) {
        if (!players[i2].is_free && players[i2].team_id != -1) {
            draw_square(renderer, board, players[i2].x, players[i2].y, &players[i2].color);
        }
    }
}

int init(t_board *board, t_lemipc *lemipc) {
    SDL_Window *fenetre;
    SDL_Renderer *renderer;
    int y;
    int x;
    SDL_Event	event;


    if (SDL_VideoInit(NULL) < 0)
        return (84);
    if ((fenetre = SDL_CreateWindow(board->name, SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED, board->width, board->height, 0)) == NULL)
        return (84);
    if ((renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED |
                                                    SDL_RENDERER_PRESENTVSYNC)) == NULL)
        return (84);

    /*
    while (g_running) {
        SDL_WaitEvent(&event);
        if (on_event_exit(&event))
            break;
        clear_screen(renderer);

        while (y++ < round(sqrt(MAX_PLAYERS))) {
            while (x++ < round(sqrt(MAX_PLAYERS))) {
                draw_grille(renderer, board);
                if (check_player(lemipc, &x, &y) == 1) {
                    draw_square(renderer, board, x, y, &lemipc->players->color);
                    printf("%d %d\n", x, y);
                }
            }
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
        printf("refreshed\n");
    }
     */

    while (1) {
        SDL_PollEvent(&event);
        if (event.type == SDL_QUIT)
            break;
        clear_screen(renderer);
        draw_grille(renderer, board);
      // SDL_RenderPresent(renderer);

        draw_players(renderer, board, lemipc->players);
        SDL_RenderPresent(renderer);

        SDL_Delay(100);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return (0);
}

int main(int ac, char **av) {
    t_board board;
    t_lemipc *lemipc;

    printf("START\n");
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

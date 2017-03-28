/*
** main.c for  in /home/linder/cours/system unix/PSU_2016_lemipc
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Tue Mar 28 10:48:20 2017 linder
** Last update Tue Mar 28 14:42:17 2017 linder
*/

#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <semaphore.h>
#include "lemipc.h"

char init_player_map(t_player ***players) {
    int x;
    int y;

    *players = malloc(sizeof(t_player) * MAP_HEIGHT);
    if (*players == NULL)
        return 0;
    y = -1;
    while (++y < MAP_HEIGHT) {
        (*players)[y] = malloc(sizeof(t_player) * MAP_WIDTH);
        x = -1;
        while (++x < MAP_WIDTH)
            (*players)[y][x] = 0;
    }
}

static char start(char *path, int team_nb) {
    key_t key;
    int shm_key;
    t_ipc_shared *s_ipc_shared;

    if ((key = ftok(path, 0)) == -1)
        return exit_error(NULL, 84);
    shm_key = shmget(key, sizeof(t_ipc_shared), IPC_CREAT);

    if (shm_key == -1)
        return exit_error(NULL, 84);
    s_ipc_shared = (t_ipc_shared*)shmat(shm_key, NULL, SHM_R | SHM_W);
    if (s_ipc_shared == -1)
        return exit_error(NULL, 84);

    return 0;
}

static char usage() {
    printf("Usage : ./lemipc path_to_key team_number\n\n"
                   "path_to_key is a valid path that will be use by ftok\n"
                   "team_number is the team number assigned to the current player\n");
    return 84;
}

int main(int ac, char **av) {
    if (ac != 3 ||
        !strcmp(av[1], "-h") ||
        !is_nbr(av[2]))
        return usage();
    return start(av[1], atoi(av[2]));
}

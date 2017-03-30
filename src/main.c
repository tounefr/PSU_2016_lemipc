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
#include <signal.h>
#include <time.h>
#include <math.h>
#include "lemipc.h"

t_lemipc *g_lemipc = NULL;

t_player *get_player_in_same_team(t_player *me, t_player *players) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (players[i].team_id == me->team_id &&
            players[i].is_free == 0 &&
            players[i].pid != me->pid)
            return &players[i];
    }
    return NULL;
}

char on_player_leave(t_player *me, t_lemipc *lemipc) {
    t_player *smne_in_team;

    if (me == NULL)
        return 0;
    LOG_MSG("\non_player_leave\n");
    LOG_MSG("Cur nbr players=%d\n", lemipc->nbr_players);
    if (me->is_master) {
        smne_in_team = get_player_in_same_team(me, &lemipc->players);
        if (smne_in_team) {
            LOG_MSG("PID=%d is now the master\n", smne_in_team->pid);
            smne_in_team->is_master = 1;
        }
    }
    init_s_player(me);
    lemipc->nbr_players--;
    if (lemipc->nbr_players <= 0) {
        LOG_MSG("Ending game\n");
        clean_ipcs(lemipc);
    }
    return 1;
}

t_player *get_player_slot(t_lemipc *lemipc) {
    int i;
    int my_pid;

    my_pid = getpid();
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!lemipc->players[i].is_free && lemipc->players[i].pid == my_pid)
            return &lemipc->players[i];
    }
    return NULL;
}

char is_player_master(t_player *players, int team_id) {
    int i;
    int my_pid;

    my_pid = getpid();
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
                players[i].team_id == team_id &&
                players[i].pid != my_pid)
            return 0;
    }
    return 1;
}

t_pos get_xy_pos(int i) {
    t_pos pos;

    pos.x = (i % (int)round(sqrt(MAX_PLAYERS)));
    pos.y = (i / (int)round(sqrt(MAX_PLAYERS)));
    pos.i = i;
    return pos;
}

t_pos rand_player_pos(t_lemipc *lemipc) {
    int i;
    int available_pos;
    int rand_nbr;
    t_pos rand_pos;

    i = -1;
    available_pos = 0;
    rand_pos.x = -1;
    rand_pos.y = -1;
    while (++i < MAX_PLAYERS) {
        if (lemipc->players[i].is_free)
            available_pos++;
    }
    if (available_pos == 0)
        rand_pos;
    rand_nbr = rand() % available_pos;
    i = -1;
    available_pos = 0;
    while (++i < MAX_PLAYERS) {
        if (lemipc->players[i].is_free)
            available_pos++;
        if (available_pos == rand_nbr)
            rand_pos = get_xy_pos(i);
    }
    return rand_pos;
}

void debug_players(t_player *players) {
    int i;
    int c;

    c = 0;
    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free) {
            c++;
            printf("x=%d y=%d is_free=%d pid=%d team_id=%d is_master=%d\n",
                players[i].x,
                   players[i].y,
                   players[i].is_free,
                   players[i].pid,
                   players[i].team_id,
                   players[i].is_master
            );
        }
    }
    printf("count = %d\n", c);
}


char init_new_player(t_player **me, int team_id, t_lemipc *lemipc) {
    t_pos xy_pos;
    t_player *player;

    xy_pos = rand_player_pos(lemipc);
    if (xy_pos.x == -1 && xy_pos.y == -1)
        return 0;
    player = &lemipc->players[xy_pos.i];
    player->is_free = 0;
    player->pid = getpid();
    player->team_id = team_id;
    player->is_master = is_player_master(&lemipc->players, team_id);
    player->x = xy_pos.x;
    player->y = xy_pos.y;
    *me = player;
    LOG_MSG("my pos x=%d y=%d\n", player->x, player->y);
    return 1;
}

char new_player_slot(t_player **me, t_lemipc *lemipc, int team_id) {
    if (lemipc->nbr_players >= MAX_PLAYERS)
        return exit_error("Failed to allocate new player slot\n", 0);
    lemipc->nbr_players++;
    LOG_MSG("Cur nbr players=%d\n", lemipc->nbr_players);
    return init_new_player(me, team_id, lemipc);
}

void clean_ipcs(t_lemipc *lemipc) {
    if (lemipc->nbr_players <= 0) {
        shmctl(lemipc->shm_key, IPC_RMID, NULL);
        LOG_MSG("IPCS cleaned\n");
    }
}

void sighandler(int signum) {
    if (signum == SIGINT) {
        if (g_lemipc != NULL)
            on_player_leave(get_player_slot(g_lemipc), g_lemipc);
        exit(0);
    }
}

void init_s_player(t_player *player) {
    player->x = -1;
    player->y = -1;
    player->pid = -1;
    player->is_free = 1;
    player->team_id = -1;
    player->is_master = -1;
}

char init_s_lemipc(t_lemipc *lemipc, int shm_key) {
    int i;

    LOG_MSG("Starting the game\n", getpid());
    lemipc->shm_key = shm_key;
    i = -1;
    while (++i < MAX_PLAYERS) {
        init_s_player(&lemipc->players[i]);
    }
    return 1;
}

char get_shared_lemipc(t_lemipc **s_lemipc, char *path) {
    key_t key;
    int shm_key;
    int created;

    key = ftok(path, 0);
    created = 0;
    shm_key = shmget(key, sizeof(t_lemipc), SHM_R | SHM_W);
    if (-1 == shm_key) {
        shm_key = shmget(key, sizeof(t_lemipc), IPC_CREAT | SHM_R | SHM_W);
        if (-1 == shm_key)
            return exit_error(NULL, 0);
        created = 1;
    }
    LOG_MSG("Shm key=%d\n", shm_key);
    *s_lemipc = shmat(shm_key, NULL, SHM_R | SHM_W);
    if (s_lemipc == ((void*) - 1))
        return exit_error(NULL, 0);
    g_lemipc = *s_lemipc;
    if (created && !init_s_lemipc(*s_lemipc, shm_key))
        return 0;
    return 1;
}

char can_playing(t_lemipc *s_lemipc, t_player *me) {
    int i;
    char different_team;
    char has_friend;

    i = -1;
    different_team = 0;
    has_friend = 0;
    while (++i < MAX_PLAYERS) {
        if (s_lemipc->players[i].is_free == 0 &&
            s_lemipc->players[i].team_id != me->team_id)
            different_team = 1;
        if (s_lemipc->players[i].team_id == me->team_id &&
            s_lemipc->players[i].pid != me->pid)
            has_friend = 1;
    }
    return (different_team && has_friend);
}

char focus_ennemy(t_player *me, t_player *players) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
            players[i].team_id != me->team_id) {
            me->player_focus = &players[i];
            return 1;
        }
    }
    me->player_focus = NULL;
    return 0;
}

char display_map(t_lemipc *s_lemipc) {
    int max;
    int x;
    int y;
    int i;
    int i2;
    int c;

    max = round(sqrt(MAX_PLAYERS));
    y = -1;
    while (++y < max) {
        x = -1;
        while (++x < max) {
            i = (y * max) + x;
            i2 = -1;
            c = '_';
            while (++i2 < MAX_PLAYERS) {
                if (!s_lemipc->players[i2].is_free &&
                    s_lemipc->players[i2].x == x &&
                    s_lemipc->players[i2].y == y &&
                    s_lemipc->players[i2].team_id != -1)
                        c = s_lemipc->players[i2].team_id + '0';
            }
            printf("%c", c);

        }
        printf("\n");
    }
    printf("\n");
}

char has_player_on_this_pos(t_player *players, int x, int y) {
    int i;

    i = -1;
    while (++i < MAX_PLAYERS) {
        if (!players[i].is_free &&
            players[i].x == x &&
            players[i].y == y) {
            return 1;
        }
    }
    return 0;
}

char is_good_pos(int x, int y) {
    int max;

    max = round(sqrt(MAX_PLAYERS)) - 1;
    return (x >= 0 && x <= max && y >= 0 && y <= max);
}

int  abs(int x) {
    if (x < 0)
        return -x;
    return x;
}

int calc_dist(int x1, int y1, int x2, int y2) {
    return abs(x2 - x1) + abs(y2 - y1);
}

t_pos init_pos(int x, int y) {
    t_pos pos;

    pos.x = x;
    pos.y = y;
    return pos;
}

char check_dest_pos(t_player *me,
                    t_dist_cmp *dist_cmp,
                    t_pos test_pos,
                    t_player **players) {
    int v;

    if (!is_good_pos(test_pos.x, test_pos.y))
        return 0;
    v = calc_dist(test_pos.x, test_pos.y, me->player_focus->x, me->player_focus->y);
    if (v < dist_cmp->min)
        dist_cmp->min = v;
    if (has_player_on_this_pos(players, test_pos.x, test_pos.y))
        return 0;
    dist_cmp->dest.x = test_pos.x;
    dist_cmp->dest.y = test_pos.y;
    return 1;
}

char eat_ennemies_around(t_player *me) {
}

char move_forward(t_lemipc *s_lemipc, t_player *me) {
    int max;
    char flag;
    t_dist_cmp dist_cmp;

    if (!me->player_focus)
        return 0;
    max = round(sqrt(MAX_PLAYERS)) - 1;
    flag = 0;
    //top
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y - 1), &s_lemipc->players);
    //right-top
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y - 1), &s_lemipc->players);
    //right
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y), &s_lemipc->players);
    //right-bottom
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x + 1, me->y + 1), &s_lemipc->players);
    //bottom
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x, me->y + 1), &s_lemipc->players);
    //left-bottom
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y + 1), &s_lemipc->players);
    //left
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y), &s_lemipc->players);
    //left-top
    flag |= check_dest_pos(me, &dist_cmp, init_pos(me->x - 1, me->y - 1), &s_lemipc->players);

    me->x = dist_cmp.dest.x;
    me->y = dist_cmp.dest.y;

    eat_ennemies_around(me);

    return 1;
}

/*
char master_game_mode(t_lemipc *s_lemipc, t_player *me) {
}
char slave_game_mode(t_lemipc *s_lemipc, t_player *me) {
}
*/

char loop(t_lemipc *s_lemipc, t_player *me) {
    while (1) {
        if (/*!can_playing(s_lemipc, me) ||
            */!focus_ennemy(me, &s_lemipc->players) ||
            !move_forward(s_lemipc, me)) {

            LOG_MSG("[IDLE] Me: pid=%d x=%d y=%d team_id=%d\n",
                    me->pid,
                    me->x,
                    me->y,
                    me->team_id);

        } else {
            LOG_MSG("[PLAYING] Me: pid=%d x=%d y=%d team_id=%d | ennemy: pid=%d x=%d y=%d team_id=%d\n",
                    me->pid,
                    me->x,
                    me->y,
                    me->team_id,
                    me->player_focus->pid,
                    me->player_focus->x,
                    me->player_focus->y,
                    me->player_focus->team_id);
        }
       display_map(s_lemipc);

        /*
        if (me->is_master)
            master_game_mode(s_lemipc, me);
        else
            slave_game_mode(s_lemipc, me);
            */
        sleep(1);
    }
    return 1;
}

static char start(char *path, int team_nb) {
    t_player *me;
    t_lemipc *s_lemipc;

    signal(SIGINT, sighandler);
    srand(time(NULL));
    if (!get_shared_lemipc(&s_lemipc, path))
        return 0;
    if (!new_player_slot(&me, s_lemipc, team_nb))
        return 0;
    debug_players(&s_lemipc->players);
    return loop(s_lemipc, me);
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
    LOG_MSG("Process id=%d starting\n", getpid());
    return !start(av[1], atoi(av[2]));
}

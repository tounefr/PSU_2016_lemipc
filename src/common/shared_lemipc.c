
#include "common.h"

void init_s_player(t_player *player)
{
    player->x = -1;
    player->y = -1;
    player->pid = -1;
    player->is_free = 1;
    player->team_id = -1;
    player->is_master = -1;
}

char init_s_lemipc(t_lemipc *lemipc, int shm_key)
{
    int i;

    LOG_MSG("Starting the game\n");
    if (-1 == sem_init(&lemipc->move_lock, 1, 1))
        return 0;
    lemipc->nbr_players = 0;
    lemipc->shm_key = shm_key;
    i = -1;
    while (++i < MAX_PLAYERS)
        init_s_player(&lemipc->players[i]);
    return 1;
}

void clean_ipcs(t_lemipc *lemipc)
{
    if (lemipc->nbr_players <= 0) {
        shmctl(lemipc->shm_key, IPC_RMID, NULL);
        sem_close(&lemipc->move_lock);
        LOG_MSG("IPCS cleaned\n");
    }
}

char get_shared_lemipc(t_lemipc **s_lemipc, char *path)
{
    key_t key;
    int shm_key;
    int created;

    key = ftok(path, 0);
    created = 0;
    shm_key = shmget(key, sizeof(t_lemipc), SHM_R | SHM_W);
    if (-1 == shm_key) {
        shm_key = shmget(key, sizeof(t_lemipc), IPC_CREAT | SHM_R | SHM_W);
        if (-1 == shm_key)
            return 0;
        created = 1;
    }
    LOG_MSG("Shm key=%d\n", shm_key);
    *s_lemipc = shmat(shm_key, NULL, SHM_R | SHM_W);
    if (s_lemipc == ((void*) - 1))
        return 0;
    if (created && !init_s_lemipc(*s_lemipc, shm_key))
        return 0;
    return 1;
}
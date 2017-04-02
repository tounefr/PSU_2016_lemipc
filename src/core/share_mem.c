/*
** share_mem.c for  in /home/linder/PSU_2016_lemipc/src/core
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 19:01:05 2017 linder
** Last update Sun Apr  2 19:01:47 2017 linder
*/

#define _GNU_SOURCE
#include <dlfcn.h>
#include <assert.h>
#include "common.h"
#include "core.h"

char	get_shr_mem_handle(t_lemipc **s_lemipc, char *path)
{
  void	*shared_handle;
  char	(*get_shared_lemipc)(t_lemipc **, char *);

  shared_handle = dlopen("./liblemipc_shared.so", RTLD_LAZY);
  if (!shared_handle)
    return (0);
  get_shared_lemipc = dlsym(shared_handle, "get_shared_lemipc");
  if (!get_shared_lemipc)
    return (0);
  if (!get_shared_lemipc(s_lemipc, path))
    return (0);
  dlclose(shared_handle);
  g_lemipc = *s_lemipc;
  return (1);
}

void	clean_ipcs(t_lemipc *lemipc)
{
  if (lemipc->nbr_players <= 0)
    {
      shmctl(lemipc->shm_key, IPC_RMID, NULL);
      sem_close(&lemipc->move_lock);
      LOG_MSG("IPCS cleaned\n");
    }
}

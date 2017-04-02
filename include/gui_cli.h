/*
** gui_cli.h for  in /home/linder/PSU_2016_lemipc/include
** 
** Made by linder
** Login   <linder@epitech.net>
** 
** Started on  Sun Apr  2 19:05:14 2017 linder
** Last update Sun Apr  2 19:05:16 2017 linder
*/

#ifndef PSU_2016_LEMIPC_GUI_CLI_H
#define PSU_2016_LEMIPC_GUI_CLI_H

#include <semaphore.h>

#include "common.h"

extern t_lemipc *g_lemipc;

void    check_player(t_lemipc *s_lemipc, int *c, int *x, int *y);

#endif //PSU_2016_LEMIPC_GUI_CLI_H

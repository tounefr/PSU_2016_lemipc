//
// Created by thomas on 01/04/17.
//

#ifndef PSU_2016_LEMIPC_GUI_CLI_H
#define PSU_2016_LEMIPC_GUI_CLI_H

#include <semaphore.h>

#include "common.h"

extern t_lemipc *g_lemipc;

void    check_player(t_lemipc *s_lemipc, int *c, int *x, int *y);

#endif //PSU_2016_LEMIPC_GUI_CLI_H

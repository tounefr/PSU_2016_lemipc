//
// Created by thomas on 31/03/17.
//

#ifndef PSU_2016_LEMIPC_GUI_H
#define PSU_2016_LEMIPC_GUI_H

typedef struct s_gui
{
    int     win_width;
    int     win_height;
    char    win_name[1000];
} t_gui;

void *gui_init(t_gui*);

#endif //PSU_2016_LEMIPC_GUI_H


#include "lemipc.h"

char is_nbr(char *str) {
    int i;
    int len;

    len = strlen(str);
    i = -1;
    while (++i < len) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
    }
    return 1;
}

int  abs(int x) {
    if (x < 0)
        return -x;
    return x;
}
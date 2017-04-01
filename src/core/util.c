
#include "common.h"

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

char	exit_error(char *msg, char exit_number)
{
    if (msg == NULL)
        fprintf(stderr, "%s\n", strerror(errno));
    else
        fprintf(stderr, "%s\n", msg);
    return (exit_number);
}
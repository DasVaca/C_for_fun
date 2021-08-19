#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "err.h"

int min(int a, int b) {
    log_write("min(%i, %i)\n", a, b);
    /* minimum between a and b */
    return (a > b) ? b: a;
}

int is_number(char *s) {
    log_write("is_number(%s)\n", s);
    /* return 1 if every character is a digit */
    int sl = strlen(s);
    for(int i = 0; i < sl; i++) {
        if (s[i] < '0' || s[i] > '9') {
            return 0;
        }
    }
    return 1;
}

int randint(int liminf, int limsup) {
    /*  limits inclusive */
    return (rand() % (limsup - liminf)) + liminf;
}

int between(int value, int liminf, int limsup) {
    /* bounds inclusive */
    return value >= liminf && value <= limsup;
}

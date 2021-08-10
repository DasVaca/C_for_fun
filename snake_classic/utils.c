#include <stdlib.h>
#include "utils.h"

int randint(int liminf, int limsup) {
    /*  limits inclusive */
    return (rand() % (limsup - liminf)) + liminf;
}

int between(int value, int liminf, int limsup) {
    /* bounds inclusive */
    return value >= liminf && value <= limsup;
}

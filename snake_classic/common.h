#ifndef COMMON_H
#define COMMON_H

#include "snake.h"

/* li = lim inf */

int has_hit_wall(struct snake_t *, int liy, int lsy, int lix, int lsx);
int is_dead(struct snake_t *, int liy, int lsy, int lix, int lsx);
int has_eated_food(struct snake_t *s, int foody, int foodx);

#endif

#include "utils.h"
#include "common.h"

/* li - lim inf
 * ls - lim sup*/

int has_hit_wall(struct snake_t * s, int liy, int lsy, int lix, int lsx) {
    /* return non-zero if has hited the wall, 0 otherwise */
    return !(between(s->body->y, liy, lsy) && between(s->body->x, lix, lsx));
}

int is_dead(struct snake_t * s, int liy, int lsy, int lix, int lsx) {
    /* return non-zero if is dead, 0 otherwise */
    return has_hit_wall(s, liy, lsy, lix, lsx) || is_eating_itself(s);
}

int has_eated_food(struct snake_t * s, int foody, int foodx) {
    return s->body->y == foody && s->body->x == foodx;
}

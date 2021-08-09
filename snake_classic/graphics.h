#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include "snake.h"

void draw_food(WINDOW *, int y, int x);
void draw_snake(WINDOW *, struct snake_t * snake);

#endif

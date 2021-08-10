#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include "snake.h"

#define HW_PRP 0.25
#define GW_PRP (1 - HW_PRP)

typedef struct {
    int h, w, begy, begx, endy, endx;
    WINDOW * win;
} WIN;

void draw_food(WINDOW *, int y, int x);
void draw_snake(WINDOW *, struct snake_t * snake);
void init_graphics();

WIN * init_win(int h, int w, int begy, int begx);

#endif

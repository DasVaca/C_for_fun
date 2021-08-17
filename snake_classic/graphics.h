#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <ncurses.h>
#include "snake.h"

typedef struct {
    int h, w, begy, begx, endy, endx;
    WINDOW * win;
} WIN;

WIN * init_win(int h, int w, int begy, int begx);
void init_graphics();

void draw_food(WINDOW *, int y, int x);
void draw_snake(WINDOW *, struct snake_t * snake);
void update_score(WINDOW *, int);
void update_size(WINDOW * win, int); 
void update_level(WINDOW * win, int);


#endif

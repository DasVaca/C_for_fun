#include <stdlib.h>
#include "graphics.h"


void draw_food (WINDOW * win, int y, int x) {
    mvwaddch(win, y, x, ACS_BLOCK | A_BLINK);
}

void draw_snake(WINDOW * win, struct snake_t * snake) {
    static int last_y = -1;
    static int last_x = -1;

    /* it clears tail, so we don't need to clear the entire screen */
    if (last_y > 0 && last_x > 0) {
        wattron(win, COLOR_PAIR(COLOR_BLACK));
        mvwaddch(win, last_y, last_x, ' ');
        wattroff(win, COLOR_PAIR(COLOR_BLACK));
    }

    struct snake_body_t * traveler = snake->body;

    while (traveler->next) {
        mvwaddch(win, traveler->y, traveler->x, ACS_BLOCK);
        traveler = traveler->next;
    }

    last_y = traveler->y;
    last_x = traveler->x;
}

WIN * init_win(int h, int w, int begy, int begx) {
    /* Create a newwin on a wrapper with extra information */
    WIN * win = calloc(1, sizeof(win));

    win->h = h;
    win->w = w;
    win->begy = begy;
    win->begx = begx;
    win->endy = begy + h;
    win->endx = begx + w;

    win->win = newwin(h, w, begy, begx);

    return win;
}

void init_graphics() {
    initscr();
    noecho();
    nocbreak();
    curs_set(0);
    start_color();
}

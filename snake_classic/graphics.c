#include <stdlib.h>
#include "graphics.h"

void init_graphics() {
    initscr();
    noecho();
    curs_set(0);
    start_color();
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

void draw_food (WINDOW * win, int y, int x) {
    mvwaddch(win, y, x, ACS_BLOCK | A_BLINK);
}

void draw_snake(WINDOW * win, struct snake_t * snake) {
    /* Clear tail of snake */
    struct snake_body_t * tail = get_body_at(snake, snake->size);
    mvwaddch(win, tail->y, tail->x, ' ');

    /* Draws the rest of the snake */
    struct snake_body_t * traveler = snake->body;
    while (traveler->next) {
        mvwaddch(win, traveler->y, traveler->x, ACS_BLOCK);
        traveler = traveler->next;
    }
}

void update_score(WINDOW * win, int score) {
    mvwprintw(win, 1, 2, "Score: %3i", score);
}

void update_size(WINDOW * win, int size) {
    mvwprintw(win, 3, 2, "Size : %3i", size);
}

void update_level(WINDOW * win, int level) {
    mvwprintw(win, 5, 2, "Level: %3i", level);
}

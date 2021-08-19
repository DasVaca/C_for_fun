#include <stdlib.h>
#include "graphics.h"
#include "err.h"

WIN * init_win(int h, int w, int begy, int begx) {
    /* Create a newwin on a wrapper with extra information */
    log_write("\n== INIT WIN ==\n");
    log_write("params: h=%i, w=%i, begy=%i, begx=%i\n", h, w, begy, begx);

    WIN * win = calloc(1, sizeof(*win));

    log_write("win created at %5p\n", win);

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
    log_write("\n== DRAW FOOD ==\n");
    log_write("win=%5p, y=%i, x=%i\n", win, y, x);

    mvwaddch(win, y, x, ACS_BLOCK | A_BLINK);
}

void draw_snake(WINDOW * win, struct snake_t * snake) {
    log_write("\n== DRAW SNAKE ==\n");

    static int y = -1, x = -1;

    /* Clear tail of snake */
    if (y != -1) {
        log_write("erase tail (%3i, %3i)\n", y, x);
        mvwaddch(win, y, x, ' ');
    }

    /* Draws the rest of the snake */
    struct snake_body_t * traveler = snake->body;
    while (traveler->next) {
        log_write("draw (%3i, %3i)\n", traveler->y, traveler->x);

        mvwaddch(win, traveler->y, traveler->x, ACS_BLOCK);
        traveler = traveler->next;
    }

    y = traveler->y;
    x = traveler->x;
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

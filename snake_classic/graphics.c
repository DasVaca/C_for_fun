#include "graphics.h"

void draw_food (WINDOW * win, int y, int x) {
    mvwaddch(win, y, x, ACS_BLOCK | A_BLINK);
}

void draw_snake(WINDOW * win, struct snake_t * snake) {
    struct snake_body_t * traveler = snake->body;

    do {
        mvwaddch(win, traveler->y, traveler->x, ACS_BLOCK);
    } while ((traveler = traveler->next));
}

#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "graphics.h"
#include "utils.h"
#include "common.h"

typedef struct snake_t SNAKE;

int main() {
    init_graphics();

    srand(time(NULL));

    WIN * hw = init_win(LINES*HW_PRP, COLS, 0, 0);
    WIN * gw = init_win(LINES*GW_PRP, COLS, LINES*HW_PRP, 0);

    halfdelay(5);
    keypad(gw->win, TRUE);
    
    /* Position is given relative to game window */
    SNAKE * snake = init_snake(5, randint(1, gw->h-1), randint(1, gw->w-1)); 
    int foody = randint(1, gw->h-1);
    int foodx = randint(1, gw->w-1);
    int score = 0;

    draw_food(gw->win, foody, foodx);

    box(hw->win, 0, 0);
    box(gw->win, 0, 0);
    wrefresh(gw->win);
    wrefresh(hw->win);

    int input, last_input = 'u';
    while( (input = wgetch(gw->win)) != 'q') {
        switch (input) {
            case KEY_UP: input = 'u'; break;
            case KEY_DOWN: input = 'd'; break;
            case KEY_LEFT: input = 'l'; break;
            case KEY_RIGHT: input = 'r'; break;
            default: input = last_input; break;
        }

        last_input = input;

        move_snake(snake, input);

        if (is_dead(snake, 1, gw->h-2, 1,  gw->w-2)) {
            break;
        }

        if (has_eated_food(snake, foody, foodx)) {
            foody = randint(1, gw->h-1);
            foodx = randint(1, gw->w-1);
            draw_food(gw->win, foody, foodx);
            
            grow(snake, input);
            box(gw->win, 0, 0);

            update_score(hw->win, ++score);
            wrefresh(hw->win);
        }

        draw_snake(gw->win, snake);
    }

    destroy_snake(snake);
    endwin();
    return 0;
}

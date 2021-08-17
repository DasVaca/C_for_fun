#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "graphics.h"
#include "utils.h"
#include "common.h"

typedef struct snake_t SNAKE;

const int levels[] = {5, 3, 2, 1, 0};

int main(int argc, char * argv[]) {
    init_graphics();

    srand(time(NULL));

    WIN * hw = init_win(LINES*0.5, COLS*0.2, LINES*0.25, COLS*0.8);
    WIN * gw = init_win(LINES, COLS*0.8, 0, 0);

    int level = argc == 3 ? atoi(argv[2]) % 5: 0;
    int initial_length = argc == 2 ? atoi(argv[1]) % MAX_SNAKE_LENGTH : 5;

    halfdelay(levels[level]);
    keypad(gw->win, TRUE);
    
    /* Position is given relative to game window */
    SNAKE * snake = init_snake(initial_length, randint(1, gw->h-1), randint(1, gw->w-1)); 
    int foody = randint(1, gw->h-1);
    int foodx = randint(1, gw->w-1);
    int score = 0;

    draw_food(gw->win, foody, foodx);

    box(hw->win, 0, 0);
    box(gw->win, 0, 0);
    update_size(hw->win, snake->size);
    update_level(hw->win, level+1);
    update_score(hw->win, score);
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

            update_size(hw->win, snake->size);
            update_score(hw->win, ++score);
            wrefresh(hw->win);
        }

        draw_snake(gw->win, snake);
    }

    destroy_snake(snake);
    endwin();
    return 0;
}

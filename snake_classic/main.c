#include <stdio.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>
#include "snake.h"
#include "graphics.h"
#include "utils.h"
#include "common.h"
#include "err.h"

#define MAX_LEVEL 4
#define LEVEL_INC_GAP 3

#define DEFAULT_SNAKE_LENGTH 3
#define DEFAULT_LEVEL 0

typedef struct snake_t SNAKE;

const int levels[] = {5, 3, 2, 1};

void start_game(int, int, int);

int main(int argc, char * argv[]) {
    /* Init log/debug info */
    if (!init_log()) { puts("Coudn't init log"); }
    log_write("== LOG START ==\n");

    /* To use randint */
    srand(time(NULL));

    /* Game macros and initial values */
    int score = 0;
    int initial_length = DEFAULT_SNAKE_LENGTH; 
    int level = DEFAULT_LEVEL;

    if (argc >= 2 && is_number(argv[1])) {
        initial_length = min(atoi(argv[1]), DEFAULT_SNAKE_LENGTH);
    }

    if (argc >= 3 && is_number(argv[2])) {
        level = min(atoi(argv[2]), DEFAULT_LEVEL);
    }

    /* Start ncurses */
    initscr();
    noecho();
    curs_set(0);
    start_color();

    start_game(score, level, initial_length);

    endwin();
    end_log();
    return 0;
}

void start_game(int score, int level, int initial_length) {
    log_write("\n== START GAME ==\n");

    /* Set layout */
    WIN * hw = init_win(LINES*0.5, COLS*0.2, LINES*0.25, COLS*0.8);
    WIN * gw = init_win(LINES, COLS*0.8, 0, 0);

    /* Set "refresh rate" and support for arrow keys */
    halfdelay(levels[level]);
    keypad(gw->win, TRUE);
    
    /* Set game elements, position is given relative to game window */
    SNAKE * snake = init_snake(initial_length, randint(1, gw->h-1), randint(1, gw->w-1)); 
    int foody = randint(1, gw->h-1);
    int foodx = randint(1, gw->w-1);

    /* Draw initial first screen, probably will be replaced by welcome window */
    draw_food(gw->win, foody, foodx);

    box(hw->win, 0, 0);
    box(gw->win, 0, 0);
    update_size(hw->win, snake->size);
    update_level(hw->win, level);
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
            log_write("dead");
            break;
        }

        if (has_eated_food(snake, foody, foodx)) {
            log_write("eat");
            foody = randint(1, gw->h-1);
            foodx = randint(1, gw->w-1);
            draw_food(gw->win, foody, foodx);
            
            grow(snake, input);

            if (++score % LEVEL_INC_GAP == 0) {
                level = min(level + 1, MAX_LEVEL - 1);

                halfdelay(levels[level]);
                update_level(hw->win, level);
            }
            
            update_size(hw->win, snake->size);
            update_score(hw->win, score);
            wrefresh(hw->win);
        }

        draw_snake(gw->win, snake);
    }

    destroy_snake(snake);
    delwin(hw->win);
    delwin(gw->win);
    free(hw);
    free(gw);
}

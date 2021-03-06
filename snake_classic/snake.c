#include <stdlib.h>
#include "snake.h"
#include "err.h"

/* Note: Checking for null-parsed errors is a pain,
 * so it is omitted. */

struct snake_t * init_snake(int initial_size, int initial_pos_y, int initial_pos_x) {
    /* **************************************************
     * Explode if given size if negative or way too big.
     * **************************************************/

    /* Sanity check */
    if (initial_size < 0 || initial_size > MAX_SNAKE_LENGTH) {
        exit(0);
    }
    
    /* Allocate space for the head */
    struct snake_t * snake = calloc(1, sizeof(*snake));
    snake->size = initial_size;
    snake->body = calloc(1, sizeof(*snake->body));
    snake->body->next = NULL;

    /* Set initial position on head */
    snake->body->y = initial_pos_y;
    snake->body->x = initial_pos_x;

    /* Fill the rest of the body */
    struct snake_body_t * traveler = snake->body;
    while (--initial_size > 0) {
        traveler->next = calloc(1, sizeof(*traveler));
        traveler = traveler->next;
        traveler->next = NULL;
        /* Set initial position on every cell of the body */
        traveler->y = initial_pos_y;
        traveler->x = initial_pos_x;
    }
    
    return snake;
}

int is_eating_itself(struct snake_t * snake) {
    /*********************************************************
     * Return 1 is the head is colliding with body, 0 if not.
     * *******************************************************/
    int is_eating_itself = 0;
    struct snake_body_t * traveler = snake->body;
    
    /* We will only check if the head is colliding.*/
    while ((traveler = traveler->next)) {
        if (snake->body->x == traveler->x && snake->body->y == traveler->y) {
            is_eating_itself = 1;
            break;
        }
    }
    
    return is_eating_itself;
}

void grow (struct snake_t * snake, int direction) {
    /* Add another node on the linked list. */
    struct snake_body_t * last = get_body_at(snake, snake->size);
    last->next = calloc(1, sizeof(*last));
    // Mimic the position of the last one
    last->next->y = last->y;
    last->next->x = last->x;

    last = last->next;
    
    switch (direction) {
        case 'u': last->y++; break;
        case 'd': last->y--; break;
        case 'l': last->x++; break;
        case 'r': last->x--; break;
    }

    last->next = NULL;
    snake->size++;
}

void shrink (struct snake_t * snake) {
    /* Remove the last node. */
    struct snake_body_t * second_last = get_body_at(snake, snake->size - 1);
    free(second_last->next);
    second_last->next = NULL;
    snake->size--;
}

struct snake_body_t * get_body_at(struct snake_t * snake, int position) {
    /* ******************************************************
     * The relation is position = index + 1, so if the snake
     * is has size 10, the body at 10 is the tail and
     * the body at 1 is the head.
     * ******************************************************/
    
    /* Sanity check */
    if (snake->size < position || position <= 0) {
        exit(0);
    }
    
    struct snake_body_t * body_at = snake->body;
    while (--position > 0) {
        body_at = body_at->next;
    }

    return body_at;
}

void move_snake(struct snake_t * snake, int direction) {
    /* Direction should be given as 'u'-up, 'd'-down, etc */
    int y = snake->body->y;
    int x = snake->body->x;

    int holder_x, holder_y;
    
    struct snake_body_t * traveler = snake->body;
    
    while ((traveler = traveler->next)) {
        /* Copy the position of the one in front */
        holder_x = traveler->x;
        holder_y = traveler->y;

        traveler->x = x;
        traveler->y = y;

        x = holder_x;
        y = holder_y;
    }
    /* Move the head at the end */
    switch (direction) {
        case 'u': snake->body->y--; break;
        case 'r': snake->body->x++; break;
        case 'd': snake->body->y++; break;
        case 'l': snake->body->x--; break;
    }
}

void destroy_snake(struct snake_t * snake) {
    log_write("\n== DESTROY SNAKE ==\n");

    struct snake_body_t * traveler = snake->body, * to_delete;

    while (traveler->next) {
       to_delete = traveler;
       traveler = traveler->next;
       log_write("free (%i, %i)\n", to_delete->y, to_delete->x);
       free(to_delete);
    }

    log_write("free (%i, %i)\n", traveler->y, traveler->x);
    log_write("free snake\n");

    free(traveler);
    free(snake);
}

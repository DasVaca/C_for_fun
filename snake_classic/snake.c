#include "snake.h"
#include <stdlib.h>

/* Note: Checking for null-parsed errors is a pain,
 * so it is omitted. */

struct snake_t * init(int initial_size) {
    /* **************************************************
     * Explode if given size if negative or way too big.
     * See macros.h for the MAX_BUFFER_SIZE
     * **************************************************/

    /* Sanity check */
    if (initial_size < 0 || initial_size > MAX_BUFFER_SIZE) {
        exit(0);
    }
    
    /* Allocate space for the head */
    struct snake_t * snake = calloc(1, sizeof(snake));
    snake->size = initial_size;
    snake->body = calloc(1, sizeof(snake->body));
    snake->body->next = NULL;

    /* Fill the rest of the body */
    struct snake_body_t * traveler = snake->body;
    while (--initial_size > 0) {
        traveler->next = calloc(1, sizeof(traveler));
        traveler = traveler->next;
        traveler->next = NULL;
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

void grow (struct snake_t * snake, int y, int x) {
    /* Add another node on the linked list. */
    struct snake_body_t * last = get_body_at(snake, snake->size);
    last->next = calloc(1, sizeof(last));
    last->next->next = NULL;
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

void destroy_snake(struct snake_t * snake) {
    struct snake_body_t * traveler = snake->body, * to_delete;

    while (traveler->next) {
       to_delete = traveler;
       traveler = traveler->next;
       free(to_delete);
    }

    free(traveler);
    free(snake);
}

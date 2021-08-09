#ifndef SNAKE_H
#define SNAKE_H

#define MAX_BUFFER_SIZE 50

struct snake_body_t {
    int y, x;
    struct snake_body_t * next;
};

struct snake_t {
    int size;
    struct snake_body_t * body;
};

struct snake_t * init_snake(int initial_size); 
struct snake_body_t * get_body_at(struct snake_t *, int position); 

int is_eating_itself(struct snake_t *);

void grow_snake(struct snake_t *, int y, int x);
void shrink_snake(struct snake_t *);

void destroy_snake(struct snake_t * snake);

#endif

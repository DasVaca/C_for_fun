#ifndef SNAKE_H
#define SNAKE_H

struct snake_body_t {
    int y, x;
    struct snake_body_t * next;
};

struct snake_t {
    int size;
    struct snake_body_t * body;
};

struct snake_t * init_snake(int initial_size, int initial_pos_y, int initial_pos_x); 
struct snake_body_t * get_body_at(struct snake_t *, int position); 

int is_eating_itself(struct snake_t *);

void move_snake(struct snake_t *, int direction);

void grow(struct snake_t *, int direction);
void shrink(struct snake_t *);

void destroy_snake(struct snake_t * snake);

#endif

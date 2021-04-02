#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct map_t {
    uint8_t nrows;
    uint8_t ncols;
    uint8_t * map;
};

struct region_t {
    uint8_t region;
    uint32_t tot_count;
    uint32_t par_count;
};

void print_usage() {
    puts("Usage: ./app file_name.txt");
    puts("File name must be of the form");
    puts("nrows ncols");
    puts("1 1 1 1 - - 2 2 2");
    puts("2 - 2 1 - - - 2 -");
    puts("2 2 2 1 1 1 1 - -");
    puts("- - - 2 - 1 - 1 -");
}

struct map_t * get_map_from_file(char * filename) {
    /* Load the file into memory */
    FILE * fd = fopen(filename, "r");
    
    fseek(fd, 0L, SEEK_END);

    int fsz = ftell(fd);

    fseek(fd, 0L, SEEK_SET);
    
    uint8_t * buffer = calloc(1, sizeof(buffer) * fsz);

    if (!buffer) {
        return NULL;
    }

    fread(buffer, sizeof(*buffer), fsz, fd);

    fclose(fd);

    puts("== File information ==");
    printf("-> file size: %i\n", fsz);

    struct map_t * map = calloc(1, sizeof(struct map_t));

    if (!map) {
        free(buffer);
        return NULL;
    }

    /* Extract the informacion */
    map -> nrows = buffer[0] - '0';
    map -> ncols = buffer[2] - '0';
    map -> map = calloc(1, sizeof(map -> map) * (map->nrows * map->ncols));

    if (!map) {
        free(buffer);
        free(map);
        return NULL;
    }

    for (int i = 4; i < fsz; i += 2) {
        map -> map[(i - 4)/2] = buffer[i];
    }

    free(buffer);

    puts("== Map information ==");
    printf("-> nrows: %u\n", map->nrows);
    printf("-> ncols: %u\n", map->ncols);
    puts("-> map:");

    for (int i = 0; i < map->nrows; i++) {
        for (int j = 0; j < map->ncols; j++) {
            printf("%c ", map->map[i * map->ncols + j]);
        } 
        putchar('\n');
    } 

    return map;

}

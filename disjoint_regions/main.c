/* Compiled with gcc 10.2 as follows:
 *  gcc main.c -o main
 */

#include "util.h"

struct region_t ** identify_regions(struct map_t * map) {
    struct region_t ** r = NULL;

    int size = map->nrows * map->ncols;
    int rsz = 0;

    int i, j;
    for (i = 0; i < size; i++) {
        // There's not a region or the end of the map
        if (map->map[i] == '-' || map->map[i] == '\0') {
            continue;
        }

        // count how many regions there are
        int seen = 0;

        for (j = 0; j < rsz; j++) {
            if (r[j]->region == map->map[i]) {
                r[j]->tot_count++;
                seen = 1;
                break;
            }
        }
        
        // haven't seen the region, so we need to make room for one more guy.
        if (!seen) {
            // for larger maps is better to allocate a lot of spaces at once, but this is an
            // example toy.
            r = realloc(r, ++rsz * sizeof(*r));
            // !!! always check what realloc return, i didn't for the sake of the programs length

            // clean garbage and set initial values
            r[rsz - 1] = calloc(1, sizeof(**r));
            r[rsz - 1]->region = map->map[i]; 
            r[rsz - 1]->tot_count = 1; 
            r[rsz - 1]->par_count = 0;
        }
    } 

    // an unelegant null terminator, 
    // for larger maps it is recommended to store the size somewhere.
    r = realloc(r, ++rsz * sizeof(r));

    r[rsz - 1] = NULL; 
    
    return r;
}

void pick_some_coords(struct map_t * m, uint8_t region, int * row, int * col) {
    // actually we just pick the first one that belongs to that region.
    for (int i = 0; i < m->nrows; i++) {
        for (int j = 0; j < m->ncols; j++) {
            if (m->map[i * m->ncols + j] == region) {
                *row = i;
                *col = j;
                
                goto EXIT;
            } 
        }
    }

    EXIT:
    ;
}

int walk_on_region(struct map_t * m, struct region_t * r, int row, int col, int * visited) {
    /* Out of bounds */
    if (row >= m->nrows || row < 0 || col >= m->ncols || col < 0) {
        return 0;
    }
    /* Not the region we are looking for */
    if (m->map[row * m->ncols + col] != r->region) {
        return 0;
    }
    /* We already saw it */
    if(visited[row * m->ncols + col]) {
        return 0;
    }

    printf("-> Coords (%i, %i)\n", row, col);

    visited[row * m->ncols + col] = 1; // mark as visited
    
    r->par_count++;

    walk_on_region(m, r, row, col + 1, visited);
    walk_on_region(m, r, row, col - 1, visited);
    walk_on_region(m, r, row + 1, col, visited);
    walk_on_region(m, r, row - 1, col, visited);
}

void count_partial_region(struct region_t ** r, struct map_t * m) {
    // visited is a matrix n by m where each entry visited is marked with a one
    int * visited = calloc(1, m->nrows * m->ncols * sizeof(*visited));

    for (int i = 0; r[i]; i++) {
        printf("-> Analizing region %c\n", r[i]->region);

        int row, col;

        pick_some_coords(m, r[i]->region, &row, &col);

        // clean visited for each region
        memset(visited, 0, m->nrows * m->ncols * sizeof(*visited));

        walk_on_region(m, r[i], row, col, visited);

        puts("-> Visited map");
        for (int i = 0; i < m->nrows; i++) {
            for (int j = 0; j < m->ncols; j++) {
                printf("%i ", visited[i * m->ncols + j]);
            }
            putchar('\n');
        }
    }

    free(visited);
}



int main(int argc, char * argv[]) {
    if (argc == 1) {
        print_usage();
        return 1;
    }

    struct map_t * map = get_map_from_file(argv[1]);

    struct region_t ** regions = identify_regions(map);    

    puts("\n== Regions ==");
    for (int i = 0; regions[i]; i++) {
        printf("%c ", regions[i]->region);
    }
    
    puts("\n== Magic ==");
    count_partial_region(regions, map);

    puts("\n== Disjoint Regions ==");
    for (int i = 0; regions[i]; i++) {
        printf("-> %c is disjoint? %i\n", regions[i]->region, regions[i]->tot_count != regions[i]->par_count);
    }

    /* DO NOT FORGET TO GIVE BACK THE MEMORY */
    for (int i = 0; regions[i]; i++) {
        free(regions[i]);
    }
    free(regions);
    free(map->map);
    free(map);
    return 0;
}

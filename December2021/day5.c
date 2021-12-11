#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

typedef struct {
    int** diagram;
    int maxY;
    int maxX;
} vent_map;

vent_map* get_input();
int add_to_diagram(vent_map* map, int x1, int y1, int x2, int y2);
void print_map(const vent_map* map);

int main() {
    vent_map* map = get_input();
    /* print_map(map); */
    
    int count_2 = 0;
    for (int i = 0; i <= map->maxY; i++) {
        for(int j = 0; j <= map->maxX; j++) {
            if(map->diagram[i][j] >= 2) {
                count_2++;
            }
        }
    }

    printf("Solution: %d\n", count_2);

    for(int i = 0; i <= map->maxY; i++) {
        free(map->diagram[i]);
    }

    free(map->diagram);
    free(map);
    return 0;
}

vent_map* get_input() {
    vent_map* map = (vent_map*) Calloc(1, sizeof(vent_map));
    map->maxX = 0;
    map->maxY = 0;
    map->diagram = (int**) Calloc(map->maxY, sizeof(int*));

    for(;;) {
        int x1, x2;
        int y1, y2;

        scanf("%d,%d -> %d, %d%*c", &x1, &y1, &x2, &y2);

        /* // Uncomment for part 1 solution
        if (!(x1 == x2) && !(y1 == y2)) {
            continue;
        }
        */
        

        if (x1 == -1) {
            break;
        }

        printf("(%d, %d) -> (%d, %d)\n", x1, y1, x2, y2);
        add_to_diagram(map, x1, y1, x2, y2);
    }

    return map;
}

int add_to_diagram(vent_map* map, int x1, int y1, int x2, int y2) {
    if (y1 > map->maxY || y2 > map->maxY) {
        int oldMax = map->maxY;
        map->maxY = y1 > y2 ? y1 : y2;
        map->diagram = (int**) Realloc(map->diagram, map->maxY + 1, sizeof(int*));

        for (int i = oldMax + 1; i <= map->maxY; i++) {
            map->diagram[i] = (int*) Calloc(map->maxX + 1, sizeof(int));
        }
    }

    if (x1 > map->maxX || x2 > map->maxX) {
        int oldMax = map->maxX;
        map->maxX = x1 > x2 ? x1 : x2;

        for(int i = 0; i <= map->maxY; i++) {
            if (map->diagram[i] != NULL) {
                map->diagram[i] = (int*) Realloc(map->diagram[i], map->maxX + 1, sizeof(int));
                for(int j = oldMax + 1; j <= map->maxX; j++) {
                    map->diagram[i][j] = 0;
                }
            } else {
                map->diagram[i] = (int*) Calloc(map->maxX + 1, sizeof(int));
            }
        }
    }

    if (x1 == x2) {
        /* Y is different, X is same (ROWS) */
        for (int i = y1; i != (y1 >= y2 ? y2 - 1 : y2 + 1); y1 >= y2 ? i-- : i++) { /* Inclusive Y */
            map->diagram[i][x1] += 1;
        }
    } else if (y1 == y2) {
        /* X is different, Y is same (COLUMNS) */
        for (int i = x1; i != (x1 >= x2 ? x2 - 1 : x2 + 1); x1 >= x2 ? i-- : i++) { /* Inclusive X */
            map->diagram[y1][i] += 1;
        }
    } else {
        /* Diagonals */
        int bigger_y = y1 > y2 ? y1 : y2;
        int smaller_y = y1 > y2 ? y2 : y1;
        int bigger_x = x1 > x2 ? x1 : x2;
        int smaller_x = x1 > x2 ? x2 : x1;

        int num_values = bigger_y - smaller_y;
        int* y_values = (int*) Calloc(num_values + 1, sizeof(int));
        int* x_values = (int*) Calloc(num_values + 1, sizeof(int));
        for(int i = 0; i <= num_values; i++) {
            x_values[i] = x1 > x2 ? bigger_x - i : smaller_x + i;
            y_values[i] = y1 > y2 ? bigger_y - i : smaller_y + i;
        }

        for(int i = 0; i <= num_values; i++) {
            map->diagram[y_values[i]][x_values[i]] += 1;
        }

        free(x_values);
        free(y_values);
    }

    return 1;
}

void print_map(const vent_map* map) {
    for(int i = 0; i <= map->maxY; i++) {
        for(int j = 0; j <= map->maxX; j++) {
            char str[10];
            sprintf(str, "%d", map->diagram[i][j]);
            printf("%s ", map->diagram[i][j] == 0 ? "." : str);
        }
        printf("\n");
    }
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utilities.h"

#define MAX_INPUT_SIZE 10
int* get_input();
void print_input(const int* input);
int* create_sliding_sums(const int* input);
int count_input(const int* input);
int num_larger_than_previous(const int* array);

int main(){
    int* input = get_input();
    
    /* Part 1 */
    int part1 = num_larger_than_previous(input);

    puts("---------------");
    puts("Part 1");
    printf("Got %d larger than previous\n", part1);
    
    /* Part 2 */
    int* sums = create_sliding_sums(input);
    int part2 = num_larger_than_previous(sums);

    puts("---------------");
    puts("Part 2");
    printf("Got %d larger than previous\n", part2);
    

    free(sums);
    free(input);
    return 0;
}

int* get_input() {
    int array_count = 0;
    int* array = (int*) Calloc(0, sizeof(int));

    for (;;) {
        char buffer[MAX_INPUT_SIZE + 1] = { 0 };
        fgets(buffer, MAX_INPUT_SIZE, stdin);

        /* Remove newline char */
        buffer[strlen(buffer) - 1] = 0;
        
        array = (int*) Realloc(array, array_count + 1, sizeof(int));
        array[array_count++] = atoi(buffer);

        /* Keep 0 in array for checking later */
        if (!strcmp(buffer, "0")) {
            break;
        }
    }

    return array;
}

void print_input(const int* input) {
    for (int i = 0; input[i] != 0; i++) {
        printf("Got %d\n", input[i]);
    }
}

int* create_sliding_sums(const int* input) {
    int input_count = count_input(input);

    int sums_count = 0;
    int* sums = (int*) Calloc(0, sizeof(int));
    for (int i = 0; input[i] != 0; i++) {
        if (i + 2 > input_count) {
            continue;
        }
        sums = (int*) Realloc(sums, ++sums_count, sizeof(int));

        sums[i] = input[i] + input[i + 1] + input[i + 2];
    }

    sums = (int*) Realloc(sums, sums_count + 1, sizeof(int));
    sums[sums_count] = 0;
    return sums;
}

int count_input(const int* input) {
    int total;
    for (total = 0; input[total] != 0; total++);
    return total;
}

int num_larger_than_previous(const int* array) {
    int larger_than_previous = 0;
    int previous = 0;
    for (int i = 0; array[i] != 0; i++) {
        if (previous != 0 && array[i] > previous) {
            larger_than_previous++;
        }
        previous = array[i];
    }

    return larger_than_previous;
}

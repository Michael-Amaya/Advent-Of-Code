#include "utilities.h"
#include <stdio.h>
#include <stdlib.h>

void* Calloc(int total, int size) {
    void* tmp = calloc(total, size);

    if (tmp == NULL) {
        free(tmp);
        puts("There was an error allocating memory");
        exit(-1);
    }

    return tmp;
}

void* Realloc(void* pointer, int total, int size) {
    void* tmp = realloc(pointer, total * size);

    if (tmp == NULL) {
        free(tmp);
        puts("There was an error reallocating memory");
        exit(-1);
    }

    return tmp;
}


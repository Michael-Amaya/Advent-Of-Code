#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilities.h"

#define MAX_INPUT_LEN 100

typedef struct {
    int depth;
    int position;
    int aim;
} Submarine;


void moveSub1(Submarine* sub);
void moveSub2(Submarine* sub);

int main() {
    /*
    Submarine sub1;
    sub1.depth = 0;
    sub1.position = 0;
    sub1.aim = 0;
    moveSub1(&sub1);
    printf("Answer: %d\n", sub1.depth * sub1.position);
    */

    Submarine sub2;
    sub2.depth = 0;
    sub2.position = 0;
    sub2.aim = 0;
    moveSub2(&sub2);
    printf("Answer: %d\n", sub2.depth * sub2.position);
    
    return 0;
}

void moveSub1(Submarine* sub) {
    char buffer[MAX_INPUT_LEN + 1];
    for (;;) {
        fgets(buffer, MAX_INPUT_LEN, stdin);
        
        /* Remove newline character */
        buffer[strlen(buffer) - 1] = 0;
        char direction[11] = { 0 };
        char distance[11] = { 0 };
        int count = 0;
        int passedSpace = 0;
        for(size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == ' ') {
                count = 0;
                direction[i] = 0;
                passedSpace = 1;
                continue;
            }

            if (!passedSpace) {
                direction[count++] = buffer[i];
            } else {
                distance[count++] = buffer[i];
            }
        }

        if (!strcmp(buffer, "0")) {
            break;
        }

        int dist = atoi(distance);
        // printf("Direction: %s\n", direction);
        // printf("DEPTH: %d, got %s\n", dist, distance);

        if (!strcmp(direction, "up")) {
            sub->depth -= dist;
        } else if (!strcmp(direction, "down")) {
            sub->depth += dist;
        } else if (!strcmp(direction, "forward")) {
            sub->position += dist;
        } else {
            printf("Invalid Instruction: %s\n", direction);
        }
    }
}

void moveSub2(Submarine* sub) {
    char buffer[MAX_INPUT_LEN + 1];
    for (;;) {
        fgets(buffer, MAX_INPUT_LEN, stdin);
        
        /* Remove newline character */
        buffer[strlen(buffer) - 1] = 0;
        char direction[11] = { 0 };
        char distance[11] = { 0 };
        int count = 0;
        int passedSpace = 0;
        for(size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == ' ') {
                count = 0;
                direction[i] = 0;
                passedSpace = 1;
                continue;
            }

            if (!passedSpace) {
                direction[count++] = buffer[i];
            } else {
                distance[count++] = buffer[i];
            }
        }

        if (!strcmp(buffer, "0")) {
            break;
        }

        int dist = atoi(distance);

        if (!strcmp(direction, "up")) {
            sub->aim -= dist;
        } else if (!strcmp(direction, "down")) {
            sub->aim += dist;
        } else if (!strcmp(direction, "forward")) {
            sub->position += dist;
            sub->depth += sub->aim * dist;
        } else {
            printf("Invalid Instruction: %s\n", direction);
        }
    }
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "utilities.h"

#define MAX_LINE_LEN 12

typedef struct _Node {
    char* data;
    struct _Node* next;
    struct _Node* previous;
} Node;

typedef struct {
    int size;
    Node* head;
} LinkedList;

typedef struct {
    char** arr;
    int count;
} string_array;

string_array* get_input();
int to_decimal(char* binary);
Node* get_last_node(LinkedList* list);
Node* find_item(LinkedList* list, char* data);
void remove_node(LinkedList* list, char* data);

void remove_arr(string_array* arr, char* data);

int main() {
    string_array* input = get_input();
    char* most_occuring = (char*) Calloc(MAX_LINE_LEN + 1, sizeof(char));
    char* least_occuring = (char*) Calloc(MAX_LINE_LEN + 1, sizeof(char));
    int* zero_count = (int*) Calloc(MAX_LINE_LEN, sizeof(int));
    int* one_count = (int*) Calloc(MAX_LINE_LEN, sizeof(int));

    for (int i = 0; i < input->count; i++) {
        for(int j = 0; j < MAX_LINE_LEN; j++) {
            if (input->arr[i][j] == '0') {
                zero_count[j] += 1;
            } else {
                one_count[j] += 1;
            }
        }
    }

    for(int i = 0; i < MAX_LINE_LEN; i++) {
        most_occuring[i] = one_count[i] > zero_count[i] ? '1' : '0';
        least_occuring[i] = one_count[i] > zero_count[i] ? '0' : '1';
    }

    most_occuring[MAX_LINE_LEN] = 0;
    least_occuring[MAX_LINE_LEN] = 0;

    int most = to_decimal(most_occuring);
    int least = to_decimal(least_occuring);

    printf("Answer to 1: %d\n", most * least);

    LinkedList* list1 = (LinkedList*) Calloc(1, sizeof(LinkedList));

    for(int i = 0; i < input->count; i++) {
        if(!strcmp(input->arr[i], "0")) {
            continue;
        }

        Node* newNode = (Node*) Calloc(1, sizeof(Node));
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->data = input->arr[i];

        if (list1->size == 0) {
            list1->head = newNode;
        } else {
            Node* lastNode = get_last_node(list1);
            lastNode->next = newNode;
            newNode->previous = lastNode;
        }
        list1->size++;
    }

    for (int i = 0; i < MAX_LINE_LEN; i++) {
        char _most_occuring = 0;
        int _zero_count = 0;
        int _one_count = 0;

        Node* current = list1->head;
        while(current != NULL) {
            if(current->data[i] == '0') {
                _zero_count++;
            } else {
                _one_count++;
            }

            current = current->next;
        }

        _most_occuring = _zero_count > _one_count ? '0' : '1';

        current = list1->head;
        while(current != NULL) {
            if (current == NULL) {
                break;
            }

            if(_zero_count == _one_count) {
                if (current->data[i] != '1') {
                    remove_node(list1, current->data);
                }
            } else {
                if(current->data[i] != _most_occuring) {
                    remove_node(list1, current->data);
                }
            }

            current = current->next;
        }

        if(list1->size == 1) {
            break;
        }
    }

    LinkedList* list2 = (LinkedList*) Calloc(1, sizeof(LinkedList));

    for(int i = 0; i < input->count; i++) {
        if(!strcmp(input->arr[i], "0")) {
            continue;
        }

        Node* newNode = (Node*) Calloc(1, sizeof(Node));
        newNode->next = NULL;
        newNode->previous = NULL;
        newNode->data = input->arr[i];

        if (list2->size == 0) {
            list2->head = newNode;
        } else {
            Node* lastNode = get_last_node(list2);
            lastNode->next = newNode;
            newNode->previous = lastNode;
        }
        list2->size++;
    }

    for (int i = 0; i < MAX_LINE_LEN; i++) {
        char _least_occuring = -1;
        int _zero_count = 0;
        int _one_count = 0;

        Node* current = list2->head;
        while(current != NULL) {
            if(current->data[i] == '0') {
                _zero_count++;
            } else {
                _one_count++;
            }

            current = current->next;
        }

        _least_occuring = _zero_count > _one_count ? '1' : '0';

        current = list2->head;
        while(current != NULL) {
            if (current == NULL) {
                break;
            }

            if(_zero_count == _one_count) {
                if (current->data[i] != '0') {
                    remove_node(list2, current->data);
                }
            } else {
                if(current->data[i] != _least_occuring) {
                    remove_node(list2, current->data);
                }
            }

            current = current->next;
        }

        if(list2->size == 1) {
            break;
        }
    }

    printf("Answer to 2: %d\n", to_decimal(list1->head->data) * to_decimal(list2->head->data));

    free(most_occuring);
    free(least_occuring);
    free(zero_count);
    free(one_count);
    for(int i = 0; i < input->count;i++) {
        free(input->arr[i]);
    }
    free(input->arr);
    free(input);
    return 0;
}


string_array* get_input() {
    int size = 0;
    char** input = (char**) Calloc(size, sizeof(char*));
    for (;;) {
        char buffer[MAX_LINE_LEN + 2] = { 0 };
        fgets(buffer, MAX_LINE_LEN + 2, stdin);
        
        /* Remove new line */
        buffer[strlen(buffer) - 1] = 0;

        input = (char**) Realloc(input, size + 1, sizeof(char*));
        input[size] = (char*) Calloc(strlen(buffer) + 1, sizeof(char));
        
        strcpy(input[size++], buffer);

        if (!strcmp(buffer, "0")) {
            break;
        }
    }

    string_array* arr = (string_array*) Calloc(1, sizeof(string_array));
    arr->arr = input;
    arr->count = size;

    return arr;
}

int to_decimal(char* binary) {
    int power = strlen(binary) - 1;
    int decimal_value = 0;

    for(size_t i = 0; i < strlen(binary); i++) {
        if (binary[i] == '1') {
            decimal_value += pow(2, power);
        }

        power--;
    }

    return decimal_value;
}

Node* get_last_node(LinkedList* list) {
    Node* current = list->head;

    while (current->next != NULL) {
        current = current->next;
    }

    return current;
}

Node* find_item(LinkedList* list, char* data) {
    Node* current = list->head;

    while(current != NULL) {
        if(current->data == data) {
            break;
        }
        current = current->next;
    }

    return current;
}

void remove_node(LinkedList* list, char* data) {
    Node* item_to_remove = find_item(list, data);

    if (item_to_remove == NULL) {
        return;
    }

    if (item_to_remove == list->head) {
        list->head = item_to_remove->next;
        list->head->previous = NULL;
    } else if (item_to_remove->next == NULL) {
        item_to_remove->previous->next = item_to_remove->next;
    } else {
        item_to_remove->previous->next = item_to_remove->next;
        item_to_remove->next->previous = item_to_remove->previous;
    }

    free(item_to_remove);
    list->size--;
}

void remove_arr(string_array* arr, char* data) {
    for(int i = 0; i < arr->count; i++) {
        if(arr->arr[i] == data) {
            free(data);
            char* space = (char*) Calloc(2, sizeof(char));
            space[0] = ' ';
            arr->arr[i] = space;
        }
    }
}

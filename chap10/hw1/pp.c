#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

struct node* top = NULL;

void push(struct node **top, int data) {
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        return;
    }
    newNode->data = data;
    newNode->next = *top;
    *top = newNode;
}

void printStack(struct node *top) {
    struct node *current = top;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    char input[100];

    while (1) {
        fgets(input, 100, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strchr(input, '.') != NULL) {
            printf("Print stack\n");
            double num = atof(input);
            int integerPart = (int)num;
            push(&top, integerPart);
            printStack(top);
            break;
        } else if (!isdigit(input[0])) {
            printStack(top);
            break;
        } else {
            int data = atoi(input);
            push(&top, data);
        }
    }

    return 0;
}


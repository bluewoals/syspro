#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node *head, struct node *tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;

    if (tail->next == NULL) {
        head->next = new_node;
    } else {
        tail->next->next = new_node;
    }
    tail->next = new_node;
}

void printQueue(struct node *head) {
    printf("Print queue\n");
    struct node *current = head->next;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *tail = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;
    tail->next = NULL;

    char input[100];
    while (1) {
        fgets(input, 100, stdin);

        if (isdigit(input[0])) {
            int data = atoi(input);
            addq(head, tail, data);
        } else if (input[0] == 'x') {
            printQueue(head);
            break;
        }
    }

    free(head);
    free(tail);

    return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

typedef struct operate {
    Node* head;
    void (*queue_empty)(struct operate*);
    void (*stack_empty)(struct operate*);
    void (*push)(struct operate*, int);
    void (*queue_pop)(struct operate*);
    void (*queue_front)(struct operate*);
    void (*queue_print)(struct operate*);
    void (*stack_pop)(struct operate*);
    void (*stack_top)(struct operate*);
    void (*stack_print)(struct operate*);
} Operate;

void queue_empty(Operate* list) {
    if (list->head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

void stack_empty(Operate* list) {
    if (list->head == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = list->head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

void push(Operate* list, int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        Node* current = list->head;
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
}

void queue_pop(Operate* list) {
    if (list->head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", list->head->data);
    Node* temp = list->head;
    list->head = list->head->next;
    free(temp);
}

void queue_front(Operate* list) {
    if (list->head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    printf("%d\n", list->head->data);
}

void queue_print(Operate* list) {
    Node* current = list->head;
    if (current == NULL) {
        printf("Queue is empty\n");
        return;
    }
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
    // printf("\n");
}

void stack_pop(Operate* list) {
    if (list->head == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = list->head;
    Node* prev = NULL;

    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    } else {
        list->head = NULL;  // if there is only have one node
    }
    printf("%d\n", current->data);
    free(current);
}

void stack_top(Operate* list) {
    if (list->head == NULL) {
        printf("Stack is empty\n");
        return;
    }
    Node* current = list->head;
    while (current->next != NULL) {
        current = current->next;
    }
    printf("%d\n", current->data);
}

void print_reverse(Node* node) {
    if (node == NULL) return;
    print_reverse(node->next);
    printf("%d\n", node->data);
}

void stack_print(Operate* list) {
    if (list->head == NULL) {
        printf("Stack is empty\n");
        return;
    }
    print_reverse(list->head);
    // printf("\n");
}

void initNode(Operate* list) {
    list->head = NULL;
    list->queue_empty = queue_empty;
    list->stack_empty = stack_empty;
    list->push = push;
    list->queue_pop = queue_pop;
    list->queue_front = queue_front;
    list->queue_print = queue_print;
    list->stack_pop = stack_pop;
    list->stack_top = stack_top;
    list->stack_print = stack_print;
}

void execute(Operate* list, const char* op_type, const char* cmd, const char* data) {
    // printf("DEBUG: op_type=%s, cmd=%s, data=%s\n", op_type, cmd, data);

    int value = data ? atoi(data) : -1;
    if (strcmp(op_type, "queue") == 0) {
        if (strcmp(cmd, "push") == 0)
            list->push(list, value);
        else if (strcmp(cmd, "pop") == 0)
            list->queue_pop(list);
        else if (strcmp(cmd, "front") == 0)
            list->queue_front(list);
        else if (strcmp(cmd, "print") == 0)
            list->queue_print(list);
        else if (strcmp(cmd, "empty") == 0)
            list->queue_empty(list);
    } else if (strcmp(op_type, "stack") == 0) {
        if (strcmp(cmd, "push") == 0)
            list->push(list, value);
        else if (strcmp(cmd, "pop") == 0)
            list->stack_pop(list);
        else if (strcmp(cmd, "top") == 0)
            list->stack_top(list);
        else if (strcmp(cmd, "print") == 0)
            list->stack_print(list);
        else if (strcmp(cmd, "empty") == 0)
            list->stack_empty(list);
    }
}

int main() {
    Operate stack, queue;
    initNode(&stack);
    initNode(&queue);
    int n;
    scanf("%d", &n);
    getchar();  // clear "\n"

    while (n--) {
        char input[50];
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;
        char* token = strtok(input, " ");
        char* op_type = token;
        token = strtok(NULL, " ");
        char* cmd = token;
        token = strtok(NULL, " ");
        char* data = token;

        if (strcmp(op_type, "stack") == 0)
            execute(&stack, op_type, cmd, data);
        else if (strcmp(op_type, "queue") == 0)
            execute(&queue, op_type, cmd, data);
    }

    return 0;
}

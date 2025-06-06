#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dnode_s {
    int data;
    struct dnode_s* front;
    struct dnode_s* back;
} dnode_t;

typedef dnode_t* nodep_t;

nodep_t head = NULL;
nodep_t tail = NULL;

nodep_t createNode(int data) {
    nodep_t newNode = (nodep_t)malloc(sizeof(dnode_t));
    newNode->data = data;
    newNode->front = NULL;
    newNode->back = NULL;
    return newNode;
}

void addFront(int data) {
    nodep_t newNode = createNode(data);
    if (head == NULL) {
        head = tail = newNode;
    } else {
        newNode->back = head;
        head->front = newNode;
        head = newNode;
    }
}

void addBack(int data) {
    nodep_t newNode = createNode(data);
    if (tail == NULL) {
        head = tail = newNode;
    } else {
        tail->back = newNode;
        newNode->front = tail;
        tail = newNode;
    }
}

void removeFront() {
    if (head == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = head;
    if (head == tail) {
        head = tail = NULL;
    } else {
        head = head->back;
        head->front = NULL;
    }
    free(temp);
}

void removeBack() {
    if (tail == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t temp = tail;
    if (head == tail) {
        head = tail = NULL;
    } else {
        tail = tail->front;
        if (tail) tail->back = NULL;
    }
    free(temp);
}

void emptyList() {
    if (head == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    while (head != NULL) {
        nodep_t temp;
        temp = head;
        head = head->back;
        free(temp);
    }
    tail = NULL;
}

int getListLength() {
    int len = 0;
    nodep_t cur = head;
    while (cur != NULL) {
        len++;
        cur = cur->back;
    }
    return len;
}

void insertAfter(int pos, int data) {
    int len = getListLength();
    if (pos < 1 || pos > len) {
        printf("Invalid command\n");
        return;
    }

    nodep_t cur = head;
    for (int i = 1; i < pos; i++)
        cur = cur->back;

    nodep_t newNode = createNode(data);
    newNode->back = cur->back;
    newNode->front = cur;

    if (cur->back != NULL)
        cur->back->front = newNode;
    else
        tail = newNode;
    cur->back = newNode;
}

void removeAt(int pos) {
    int len = getListLength();
    if (pos < 1 || pos > len) {
        printf("Invalid command\n");
        return;
    }

    nodep_t cur = head;
    for (int i = 1; i < pos; i++)
        cur = cur->back;

    if (cur->front != NULL)
        cur->front->back = cur->back;
    else
        head = cur->back;
    if (cur->back != NULL)
        cur->back->front = cur->front;
    else
        tail = cur->front;

    free(cur);
}

void printList() {
    if (head == NULL) {
        printf("Double link list is empty\n");
        return;
    }
    nodep_t cur = head;
    while (cur != NULL) {
        printf("%d\n", cur->data);
        cur = cur->back;
    }
}

int main() {
    int numOfOperate;
    scanf(" %d", &numOfOperate);
    while (numOfOperate--) {
        char cmd[50];
        scanf(" %s", cmd);
        if (!strcmp(cmd, "addFront")) {
            int data;
            scanf(" %d", &data);
            addFront(data);
        } else if (!strcmp(cmd, "addBack")) {
            int data;
            scanf(" %d", &data);
            addBack(data);
        } else if (!strcmp(cmd, "removeFront")) {
            removeFront();
        } else if (!strcmp(cmd, "removeBack")) {
            removeBack();
        } else if (!strcmp(cmd, "empty")) {
            emptyList();
        } else if (!strcmp(cmd, "print")) {
            printList();
        } else if (!strcmp(cmd, "insert")) {
            int pos, data;
            scanf(" %d %d", &pos, &data);
            insertAfter(pos, data);
        } else if (!strcmp(cmd, "remove")) {
            int pos;
            scanf(" %d", &pos);
            removeAt(pos);
        }
    }

    return 0;
}

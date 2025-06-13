#include <stdio.h>
#include <stdlib.h>
#define SIZE 4

typedef enum { FALSE,
               TRUE } bool;

bool isFull(int head, int tail) {
    return (((tail - head + 1) % SIZE) == 0);
}

bool enqueue(int data[], int index[], int key) {
    if (isFull(index[0], index[1])) {
        return FALSE;
    }
    index[1] = (index[1] + 1) % SIZE;  // Update head
    data[index[1]] = key;              // Insert new element
    return TRUE;
}

int main() {
    int k = 0, i = 0, index[3] = {0, 0, 0}, data[SIZE];
    bool result;

    for (int i = 0; i < 5; i++) {
        result = enqueue(data, index, k++);
        if (!result) {
            printf("Queue full\n");
        } else {
            printf("Enqueue %d\n", k - 1);
        }
    }

    return 0;
}

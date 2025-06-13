#include <stdio.h>
#include <stdlib.h>

typedef struct node_s {
    char data;
    struct node_s *right, *left;
} tree_t;

// typedef tree_t* btree;

int main() {
    char tree_type, data[50];
    scanf("%c %s", &tree_type, data);

    if (tree_type == 'P') {
        //
    }
    tree_t *root = NULL;

    return 0;
}

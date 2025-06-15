#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a > *(int *)b); // 升序比較
}

int main() {
    int arr[] = {4, 2, 1, 3, 5};
    qsort(arr, 5, sizeof(int), cmp);
    for (int i = 0; i < 5; i++) {
        printf("%d ", arr[i]);
    }
    return 0;
}

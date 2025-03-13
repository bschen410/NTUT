#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int cmp(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

void isTri(int a, int b, int c, int *arr) {
    qsort(arr, 3, sizeof(int), cmp);
    // printf("%d %d %d\n", arr[0], arr[1], arr[2]);
    if (a + b > c && a + c > b && b + c > a && a > 0 && b > 0 && c > 0) {
        if (a == b && b== c) printf("Equilateral Triangle\n");
        if (a == b || b == c || a == c) printf("Isosceles Triangle\n");
        if (pow(arr[2], 2) == pow(arr[0], 2) + pow(arr[1], 2))
            printf("Right Triangle\n");
        else if (pow(arr[2], 2) > (pow(arr[0], 2) + pow(arr[1], 2)))
            printf("Obtuse Triangle\n");
        else if (pow(arr[2], 2) < (pow(arr[0], 2) + pow(arr[1], 2)))
            printf("Acute Triangle\n");
    } else
        printf("Not Triangle\n");
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int a, b, c;
        scanf("%d %d %d", &a, &b, &c);
        int arr[3] = {a, b, c};
        isTri(a, b, c, arr);
        if (i != n - 1)
            for (int j = 0; j < n; j++) printf("*");
        printf("\n");
    }
    return 0;
}

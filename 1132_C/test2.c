#include <stdio.h>
#include <limits.h>

int find2Min(int data[], int size) {
    int min1 = INT_MAX, min1Index = -1;
    int min2 = INT_MAX, min2Index = -1;
    for (int i = 0; i < size; i++) {
        if (data[i] < min1) {
            min1 = data[i];
            min1Index = i;
        } else if (data[i] < min2) {
            min2 = data[i];
            min2Index = i;
        }
    }
    return min2Index;
}

int main() {
    int data[] = {5, 1, 3, 6, 2};
    printf("2 min=%d\n", find2Min(data, 5));
    return 0;
}

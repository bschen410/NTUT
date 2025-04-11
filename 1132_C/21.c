#include <stdio.h>
#include <string.h>

#define SWAP(x, y) \
    {              \
        int t;     \
        t = x;     \
        x = y;     \
        y = t;     \
    }

int getMinIndex(int d[], int left, int right, int *jdgTime, int *mveTime) {
    int minIndex = left, count = 0;
    for (int i = left + 1; i < right; i++) {
        if (d[i] < d[minIndex]) minIndex = i;
        (*jdgTime)++;
    }
    return minIndex;
}

void selectSort(int d[], int n, int *jdgTime, int *mveTime) {
    int index = 0;
    for (int i = 0; i < n; i++) {
        index = getMinIndex(d, i, n, jdgTime, mveTime);
        SWAP(d[i], d[index]);
        if (i != index) (*mveTime) += 3;
    }
}

void insertionSort(int a[], int n, int *jdgTime, int *mveTime) {
    int target = 0, i = 0, j = 0;
    for (i = 1; i < n; i++) {
        target = a[i];
        (*mveTime)++;
        for (j = i;; j--) {
            (*jdgTime)++;
            if (!(j > 0)) break;
            (*jdgTime)++;
            if (!(a[j - 1] > target)) break;
            a[j] = a[j - 1];
            (*mveTime)++;
        }
        a[j] = target;
        (*mveTime)++;
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int input[n], selArray[n], insArray[n];
    for (int i = 0; i < n; i++) scanf("%d", &input[i]);
    memcpy(selArray, input, sizeof(input));
    memcpy(insArray, input, sizeof(input));
    int jdgTime = 0, mveTime = 0;
    selectSort(selArray, n, &jdgTime, &mveTime);
    printf("%d %d\n", jdgTime, mveTime);
    jdgTime = 0;
    mveTime = 0;
    insertionSort(insArray, n, &jdgTime, &mveTime);
    printf("%d %d\n", jdgTime, mveTime);
}

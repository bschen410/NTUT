#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int moreThan(int *sequence1, int *sequence2, int len) {
    for (int i = 0; i < len; i++) {
        if (sequence1[i] > sequence2[i]) return 1;
        if (sequence1[i] < sequence2[i]) return 0;
    }
    return 0;
}
void sort(int **squence, int row, int len) {
    int *temp;
    for (int r = 1; r < row; r++) {
        for (int i = 0; i < row - r; i++) {
            if (moreThan(squence[i], squence[i + 1], len)) {
                temp = squence[i];
                squence[i] = squence[i + 1];
                squence[i + 1] = temp;
            }
        }
    }
}
int isEqualArray(int *a, int *b, int size) {
    for (int i = 0; i < size; i++)
        if (a[i] != b[i]) return 0;
    return 1;
}
int main() {
    int elements;
    scanf("%d ", &elements);
    // write array to int
    int *array = (int *)malloc(20 * sizeof(int));
    char *input = (char *)malloc(40 * sizeof(char));
    gets(input);
    for (int i = 0; i < strlen(input); i += 2) {
        array[i / 2] = input[i] - '0';
    }
    // convert to sequence
    int **sequence = (int **)malloc(20 * sizeof(int *));
    int index = strlen(input) / 2 - elements + 2;
    int *temp = (int *)malloc(elements * sizeof(int));
    int row = 0, invalid = 0, totalSeq = 0;
    for (int i = 0; i < index; i++) {
        for (int e = 0; e < elements; e++) {
            temp[e] = array[i + e];
        }
        // check repeated element
        for (int m = 0; m < elements - 1; m++) {
            for (int n = m + 1; n < elements; n++) {
                if (temp[m] == temp[n]) invalid = 1;
            }
        }
        // calculate total seqs
        if (!invalid) totalSeq++;
        // check repeated row
        for (int j = 0; j < row; j++) {
            if (isEqualArray(sequence[j], temp, elements)) invalid = 1;
        }
        // copy to sequence if valid
        if (invalid) {
            invalid = 0;
            continue;
        }
        sequence[row] = (int *)malloc(elements * sizeof(int));
        for (int e = 0; e < elements; e++)
            sequence[row][e] = temp[e];
        row++;
    }
    // sort
    sort(sequence, row, elements);
    // printer
    printf("%d\n", totalSeq);
    for (int r = 0; r < row; r++) {
        for (int i = 0; i < elements; i++) {
            printf("%d ", sequence[r][i]);
        }
        printf("\n");
    }
}
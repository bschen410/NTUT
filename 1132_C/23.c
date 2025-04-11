#include <stdio.h>
#include <stdlib.h>
#define SIZE 200

int **findInversion(int seq[], int n) {
    int **inv = (int **)malloc(sizeof(int *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        inv[i] = (int *)malloc(sizeof(int) * 2);
        inv[i][0] = -1;
        inv[i][1] = -1;
    }
    int index = 0;
    // return inv;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (seq[i] > seq[j]) {
                inv[index][0] = seq[i];
                inv[index][1] = seq[j];
                index++;
            }
        }
    }
    return inv;
}

void delDuplicate(int **inv, int n) {
    for (int i = 0; inv[i][0] != -1; i++) {
        for (int j = i + 1; inv[j][0] != -1; j++) {
            if ((inv[i][0] == inv[j][0]) && (inv[i][1] == inv[j][1])) {
                inv[j][0] = -2;
                inv[j][1] = -2;
            }
        }
    }
}

void sorting(int **inv, int n) {
    for (int i = 0; inv[i][0] != -1; i++) {
        for (int j = i + 1; inv[j][0] != -1; j++) {
            if (inv[i][0] > inv[j][0]) {
                int temp1 = inv[i][0];
                int temp2 = inv[i][1];
                inv[i][0] = inv[j][0];
                inv[i][1] = inv[j][1];
                inv[j][0] = temp1;
                inv[j][1] = temp2;
            } else if (inv[i][0] == inv[j][0]) {
                if (inv[i][1] > inv[j][1]) {
                    int temp1 = inv[i][0];
                    int temp2 = inv[i][1];
                    inv[i][0] = inv[j][0];
                    inv[i][1] = inv[j][1];
                    inv[j][0] = temp1;
                    inv[j][1] = temp2;
                }
            }
        }
    }
}

void printInversion(int **inv, int n) {
    int flag = 1;
    for (int i = 0; i < SIZE; i++) {
        if (inv[i][0] == -1) break;
        if (inv[i][0] == -2) continue;
        printf("(%d,%d)\n", inv[i][0], inv[i][1]);
        flag = 0;
    }
    if (flag) printf("0\n");
}

int main() {
    int n;
    scanf("%d", &n);
    int seq[SIZE];
    for (int i = 0; i < n; i++) scanf("%d", &seq[i]);
    int **inversion = findInversion(seq, n);
    delDuplicate(inversion, n);
    sorting(inversion, n);
    printInversion(inversion, n);
    return 0;
}

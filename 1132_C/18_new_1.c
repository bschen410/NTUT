#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

int dispersion;

int *inputSeq() {
    char str[SIZE];
    char buffer[5];
    fgets(buffer, sizeof(buffer), stdin);
    // getchar();
    fgets(str, sizeof(str), stdin);
    int *seq = (int *)malloc(sizeof(int) * SIZE);
    // for (int i = 0; i < SIZE; i++) {
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        seq[i] = -1;
    }
    // ? memset(seq, -1, sizeof(int) * SIZE);
    int seq_index = 0;
    // for (int i = 0; str[i] != '\n'; i++) {
    for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        if (str[i] == ' ') continue;
        seq[seq_index++] = str[i] - '0';
    }
    return seq;
}

int **checkDispersion(int *seq) {
    int index = 0;
    int **ans = (int **)malloc(sizeof(int *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        ans[i] = NULL;  // initialize to NULL
    }
    for (int i = 0; seq[i + dispersion - 1] != -1 && seq[i + dispersion - 1] != '\0'; i++) {
        int isDis = 1;
        for (int j = 0; j < dispersion; j++) {
            // printf("i: %d; j: %d\n", i, j);
            for (int k = j + 1; k < dispersion; k++) {
                if (seq[i + j] == seq[i + k]) {
                    isDis = 0;
                    break;
                }
            }
            // if (!isDis) break;
        }
        if (isDis) {
            ans[index] = (int *)malloc(sizeof(int) * dispersion);
            for (int j = 0; j < dispersion; j++) {
                ans[index][j] = seq[i + j];
            }
            index++;
        }
    }
    return ans;
}

int cmp(int *a, int *b) {
    if (a == NULL || b == NULL) return 0;
    for (int i = 0; i < dispersion; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return 0;
}

void sortAns(int **ans) {
    for (int i = 0; ans[i] != NULL; i++) {
        for (int j = i + 1; ans[j] != NULL; j++) {
            if (cmp(ans[i], ans[j]) > 0) {
                int *temp = ans[i];
                ans[i] = ans[j];
                ans[j] = temp;
            }
        }
    }
}

void delDulplicate(int **ans) {
    for (int i = 0; ans[i + 1] != NULL; i++) {
        // printf(": %d\n", *ans[i + 1]);
        for (int j = i + 1; ans[j] != NULL; j++) {
            // printf("i: %d; j: %d\n", i, j);
            if (cmp(ans[i], ans[j]) == 0) {
                // free(ans[j]);
                // ans[j] = NULL;
                for (int k = j;; k++) {
                    if (ans[k + 1] == NULL) {
                        ans[k] = NULL;
                        break;
                    }
                    ans[k] = ans[k + 1];
                }
            }
        }
    }
}

int main() {
    int count = 0;
    scanf("%d", &dispersion);
    int *seq = inputSeq();
    int **ans = checkDispersion(seq);
    for (int i = 0; ans[i] != NULL; i++) count++;
    sortAns(ans);
    printf("%d\n", count);
    delDulplicate(ans);
    for (int i = 0; ans[i] != NULL; i++) {
        for (int j = 0; j < dispersion; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
        free(ans[i]);
    }
    free(seq);
    free(ans);
    return 0;
}

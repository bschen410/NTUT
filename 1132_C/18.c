#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

int dispersion;

int *inputSeq() {
    char str[SIZE];
    char buffer[10];
    fgets(buffer, sizeof(buffer), stdin);  // clear buffer
    fgets(str, sizeof(str), stdin);
    str[strcspn(str, "\n")] = '\0';
    int *seq = (int *)malloc(sizeof(int) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        // for (int i = 0; str[i] != '\n' && str[i] != '\0'; i++) {
        seq[i] = -1;
    }
    int seq_index = 0;
    // for (int i = 0; str[i] != '\n'; i++) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ' ') continue;
        seq[seq_index++] = str[i] - '0';
    }
    return seq;
}

int check(int *seq, int idx) {
    for (int i = 0; i < dispersion; i++) {
        for (int j = i + 1; j < dispersion; j++) {
            if (seq[idx + i] == seq[idx + j]) {
                // printf(": %d : %d", seq[idx + i], seq[idx + j]);
                return 0;
            }
        }
    }
    return 1;
}

int **checkDispersion(int *seq) {
    int index = 0;
    int **ans = (int **)malloc(sizeof(int *) * SIZE);
    for (int i = 0; i < SIZE; i++) {
        ans[i] = NULL;  // initialize to NULL
    }
    for (int i = 0; i < SIZE; i++) {
        if (seq[i + dispersion - 1] == -1) {
            break;
        }
        if (check(seq, i)) {
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
    if (a == NULL || b == NULL) return -1;
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
    for (int i = 0; i < SIZE; i++) {
        if (ans[i] == NULL) continue;
        for (int j = i + 1; j < SIZE; j++) {
            if (ans[j] == NULL) continue;
            if (cmp(ans[i], ans[j]) == 0) {
                // free(ans[j]);
                ans[j] = NULL;
            }
        }
    }
}

int main() {
    int count = 0;
    scanf("%d", &dispersion);
    int *seq = inputSeq();
    // for (int i = 0; i < SIZE; i++) printf("%d ", seq[i]);
    int **ans = checkDispersion(seq);
    for (int i = 0; ans[i] != NULL; i++) count++;
    sortAns(ans);
    printf("%d\n", count);
    delDulplicate(ans);
    for (int i = 0; i < SIZE; i++) {
        if (ans[i] == NULL) continue;
        for (int j = 0; j < dispersion; j++)
            printf("%d ", ans[i][j]);
        printf("\n");
        free(ans[i]);
    }
    free(seq);
    free(ans);
    return 0;
}

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

int dispersion;

int *inputSeq() {
    char str[SIZE];
    getchar();
    fgets(str, sizeof(str), stdin);
    int *seq = (int *)malloc(sizeof(int) * SIZE);
    memset(seq, -1, sizeof(int) * SIZE);
    int seq_index = 0;
    for (int i = 0; str[i] != '\n'; i++) {
        if (str[i] == ' ') continue;
        seq[seq_index++] = str[i] - '0';
    }
    return seq;
}

int **checkDispersion(int *seq) {
    int **ans = (int **)malloc(sizeof(int *) * SIZE);
    memset(ans, -1, sizeof(int *) * SIZE);
    for (int i = 0; seq[i + dispersion - 1] != -1; i++) {
        int isDis = 1;
        for (int j = 0; j < dispersion; j++) {
            for (int k = j + 1; k < dispersion; k++) {
                if (seq[i + j] == seq[i + k]) {
                    isDis = 0;
                    break;
                }
            }
            if (!isDis) break;
        }
        if (isDis) {
            ans[i] = (int *)malloc(sizeof(int) * SIZE);
            memset(ans[i], -1, sizeof(int) * SIZE);
            for (int j = 0; j < dispersion; j++) {
                ans[i][j] = seq[i + j];
            }
        }
    }
    return ans;
}

int cmp(int *a, int *b) {
    for (int i = 0; i < dispersion; i++) {
        if (a[i] != b[i]) return a[i] - b[i];
    }
    return 0;
}

void sortAns(int **ans) {
    for (int i = 0; *ans[i] != -1; i++) {
        for (int j = i + 1; *ans[j] != -1; j++) {
            if (cmp(ans[i], ans[j]) > 0) {
                int *temp = ans[i];
                ans[i] = ans[j];
                ans[j] = temp;
            }
        }
    }
}

int main() {
    scanf("%d", &dispersion);
    int *seq = inputSeq();
    int **ans = checkDispersion(seq);
    sortAns(ans);
    for (int i = 0; *ans[i] != -1; i++) {
        for (int j = 0; j < dispersion; j++) {
            printf("%d ", ans[i][j]);
        }
        printf("\n");
    }
    // int *ans[SIZE] = {0};
    // end
    free(seq);
    free(ans);
    return 0;
}

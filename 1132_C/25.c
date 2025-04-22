#include <stdio.h>
#include <stdlib.h>
#define BOARD_SIZE 10
#define LINK 5

void inputBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            scanf("%d", &board[i][j]);
}

void swap(int output[100][3], int i, int j) {
    int temp[3];
    for (int k = 0; k < 3; k++) {
        temp[k] = output[i][k];
        output[i][k] = output[j][k];
        output[j][k] = temp[k];
    }
}

void sortOutput(int output[100][3], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (output[i][2] < output[j][2]) {
                swap(output, i, j);
            } else if (output[i][2] == output[j][2]) {
                if (output[i][0] > output[j][0]) {
                    swap(output, i, j);
                } else if (output[i][0] == output[j][0]) {
                    if (output[i][1] > output[j][1]) {
                        swap(output, i, j);
                    }
                }
            }
        }
    }
}

void printAns(int ans[BOARD_SIZE][BOARD_SIZE]) {
    int output[100][3] = {0};
    int count = 0;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (ans[i][j]) {
                output[count][0] = i;
                output[count][1] = j;
                output[count][2] = ans[i][j];
                count++;
            }
        }
    }
    sortOutput(output, count);
    for (int i = 0; i < count; i++)
        printf("%d%d %d\n", output[i][0], output[i][1], output[i][2]);
}

int ifOutOfBoard(int i, int j) {
    return !(i < 0 || i >= BOARD_SIZE || j < 0 || j >= BOARD_SIZE);
}

int *checkScore(int board[BOARD_SIZE][BOARD_SIZE], int ans[BOARD_SIZE][BOARD_SIZE]) {
    int *score = (int *)malloc(4 * sizeof(int));
    for (int i = 0; i < 4; i++) score[i] = 0;
    // horizontal
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - LINK + 1; j++) {
            if (ifOutOfBoard(i, j - 1) && board[i][j - 1] == 1) continue;
            if (ifOutOfBoard(i, j + LINK) && board[i][j + LINK] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (board[i][j + k]) sum++;
            }
            if (i == 0 && j == 6) printf("sum: %d\n", sum);
            if (sum == LINK) {
                score[0] += 1;
            }
        }
    }
    // vertical
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (ifOutOfBoard(i - 1, j) && board[i - 1][j] == 1) continue;
            if (ifOutOfBoard(i + LINK, j) && board[i + LINK][j] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (board[i + k][j]) sum++;
            }
            if (sum == LINK) {
                score[1] += 1;
            }
        }
    }
    // right-top to left-bottom
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = LINK - 1; j < BOARD_SIZE; j++) {
            if (ifOutOfBoard(i - 1, j + 1) && board[i - 1][j + 1] == 1) continue;
            if (ifOutOfBoard(i + LINK, j - LINK) && board[i + LINK][j - LINK] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (board[i + k][j - k]) sum++;
            }
            if (sum == LINK) {
                score[2] += 1;
            }
        }
    }
    // left-top to right-bottom
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = 0; j < BOARD_SIZE - LINK + 1; j++) {
            if (ifOutOfBoard(i - 1, j - 1) && board[i - 1][j - 1] == 1) continue;
            if (ifOutOfBoard(i + LINK, j + LINK) && board[i + LINK][j + LINK] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (board[i + k][j + k]) sum++;
            }
            if (sum == LINK) {
                score[3] += 1;
            }
        }
    }
    return score;
}

void placeGo(int board[BOARD_SIZE][BOARD_SIZE], int ans[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                int *ori_score = checkScore(board, ans);
                board[i][j] = 1;
                int *new_score = checkScore(board, ans);
                int final_score = 0;
                for (int k = 0; k < 4; k++) {
                    new_score[k] -= ori_score[k];
                    if (new_score[k] < 0) new_score[k] = 0;
                    final_score += new_score[k];
                }
                ans[i][j] = final_score;
                board[i][j] = 0;
                free(ori_score);
                free(new_score);
            }
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int ans[BOARD_SIZE][BOARD_SIZE] = {0};
    inputBoard(board);
    placeGo(board, ans);
    // checkScore(board, ans);
    // printf("score: %d\n", checkScore(board, ans));
    printAns(ans);
}

#include <stdio.h>
#define BOARD_SIZE 10
#define LINK 5

void inputBoard(int board[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            scanf("%d", &board[i][j]);
}

void sortOutput(int output[100][3], int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (output[i][2] < output[j][2]) {
                int temp[3];
                for (int k = 0; k < 3; k++) {
                    temp[k] = output[i][k];
                    output[i][k] = output[j][k];
                    output[j][k] = temp[k];
                }
            } else if (output[i][2] == output[j][2]) {
                if (output[i][0] > output[j][0]) {
                    int temp[3];
                    for (int k = 0; k < 3; k++) {
                        temp[k] = output[i][k];
                        output[i][k] = output[j][k];
                        output[j][k] = temp[k];
                    }
                } else if (output[i][0] == output[j][0]) {
                    if (output[i][1] > output[j][1]) {
                        int temp[3];
                        for (int k = 0; k < 3; k++) {
                            temp[k] = output[i][k];
                            output[i][k] = output[j][k];
                            output[j][k] = temp[k];
                        }
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

int checkScore(int baord[BOARD_SIZE][BOARD_SIZE], int ans[BOARD_SIZE][BOARD_SIZE]) {
    int score = 0;
    // horizontal
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE - LINK + 1; j++) {
            if (baord[i][j - 1] == 1 || baord[i][j + LINK] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (baord[i][j + k]) sum++;
            }
            if (sum == LINK) {
                score += 1;
            }
        }
    }
    // vertical
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (baord[i - 1][j] == 1 || baord[i + LINK][j] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (baord[i + k][j]) sum++;
            }
            if (sum == LINK) {
                score += 1;
            }
        }
    }
    // right-top to left-bottom
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = LINK - 1; j < BOARD_SIZE; j++) {
            if (baord[i - 1][j + 1] == 1 || baord[i + LINK][j - LINK] == 1) continue;
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (baord[i + k][j - k]) sum++;
            }
            if (sum == LINK) {
                score += 1;
            }
        }
    }
    // left-top to right-bottom
    for (int i = 0; i < BOARD_SIZE - LINK + 1; i++) {
        for (int j = 0; j < BOARD_SIZE - LINK + 1; j++) {
            if (baord[i - 1][j - 1] == 1 || baord[i + LINK][j + LINK] == 1) {
                continue;
            }
            int sum = 0;
            for (int k = 0; k < LINK; k++) {
                if (baord[i + k][j + k]) sum++;
            }
            if (sum == LINK) {
                score += 1;
            }
        }
    }
    return score;
}

void placeGo(int board[BOARD_SIZE][BOARD_SIZE], int ans[BOARD_SIZE][BOARD_SIZE]) {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j] == 0) {
                board[i][j] = 1;
                // if (i == 8 || j == 3) {
                //     printf("%d %d %d\n", i, j, ans[i][j]);
                // }
                ans[i][j] = checkScore(board, ans);
                board[i][j] = 0;
            }
        }
    }
}

int main() {
    int board[BOARD_SIZE][BOARD_SIZE];
    int ans[BOARD_SIZE][BOARD_SIZE] = {0};
    inputBoard(board);
    placeGo(board, ans);
    checkScore(board, ans);
    printf("=====================\n");
    printAns(ans);
}

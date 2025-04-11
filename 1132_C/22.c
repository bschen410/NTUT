#include <stdio.h>
#include <string.h>
#define SIZE 200

typedef struct {
    int x1;
    int x2;
    int y1;
    int y2;
} Range;

void printSquare(int square[SIZE][SIZE], int scale);

void findBlack(int square[SIZE][SIZE], char **input, int scale, Range range) {
    // printf("%d\n", *input);
    if (**input == '\0') return;
    char current = **input;
    (*input)++;
    switch (current) {
        case '0':
            break;
        case '1':
            for (int i = range.x1; i <= range.x2; i++) {
                for (int j = range.y1; j <= range.y2; j++) {
                    square[i][j] = 1;
                }
            }
            break;
        case '2':
            // printf("pcurrent %c\n", **input);
            findBlack(square, input, scale / 2, (Range){range.x1, range.x1 + scale / 2 - 1, range.y1, range.y1 + scale / 2 - 1});
            // printf("ocurrent %c\n", **input);
            findBlack(square, input, scale / 2, (Range){range.x1, range.x1 + scale / 2 - 1, range.y1 + scale / 2, range.y2});
            // printf("icurrent %c\n", **input);
            findBlack(square, input, scale / 2, (Range){range.x1 + scale / 2, range.x2, range.y1, range.y1 + scale / 2 - 1});
            // printf("ucurrent %c\n", **input);
            findBlack(square, input, scale / 2, (Range){range.x1 + scale / 2, range.x2, range.y1 + scale / 2, range.y2});
            break;
    }
    // printSquare(square, 4);
    // printf("current %c\n", *input);
}

void printSquare(int square[SIZE][SIZE], int scale) {
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            printf("%d ", square[i][j]);
        }
        printf("\n");
    }
}

void printBlackPos(int square[SIZE][SIZE], int scale) {
    int flag = 1;
    for (int i = 0; i < scale; i++)
        for (int j = 0; j < scale; j++)
            if (square[i][j] == 1) {
                printf("%d,%d\n", i, j);
                flag = 0;
            }
    if (flag) printf("all white\n");
}

int main() {
    char DF_exp[SIZE];
    char *p = DF_exp;
    int scale;
    scanf("%s", DF_exp);
    scanf("%d", &scale);
    int square[SIZE][SIZE];
    memset(square, 0, sizeof(int) * SIZE * SIZE);
    findBlack(square, &p, scale, (Range){0, scale - 1, 0, scale - 1});
    // printSquare(square, scale);
    printBlackPos(square, scale);
    return 0;
}

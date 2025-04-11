#include <stdio.h>

typedef struct {
    int front[3][3];
    int up[3][3];
    int right[3][3];
    int down[3][3];
    int left[3][3];
    int back[3][3];
} Cube;

typedef enum {
    none,    // 0
    blue,    // 1
    red,     // 2
    yellow,  // 3
    white,   // 4
    orange,  // 5
    green,   // 6
} Color;

typedef enum {
    C_Left = 10,  // forward
    C_Mid = 11,
    C_Right = 12,
    R_Up = 20,  // left turn
    R_Mid = 21,
    R_Down = 22,
} OPcode;

void init(Cube *cube) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cube->front[i][j] = white;
            cube->up[i][j] = blue;
            cube->right[i][j] = red;
            cube->down[i][j] = green;
            cube->left[i][j] = orange;
            cube->back[i][j] = yellow;
        }
    }
}

void swapColumn(int a[3][3], int b[3][3], int column) {
    for (int i = 0; i < 3; i++) {
        int temp = a[i][column];
        a[i][column] = b[i][column];
        b[i][column] = temp;
    }
}

void swapColumn_rev(int a[3][3], int b[3][3], int column) {
    for (int i = 0; i < 3; i++) {
        int temp = a[i][column];
        a[i][column] = b[i][2 - column];
        b[i][2 - column] = temp;
    }
}

void swapRow(int a[3][3], int b[3][3], int row) {
    for (int i = 0; i < 3; i++) {
        int temp = a[row][i];
        a[row][i] = b[row][i];
        b[row][i] = temp;
    }
}

void swapRow_rev(int a[3][3], int b[3][3], int row) {
    for (int i = 0; i < 3; i++) {
        int temp = a[row][i];
        a[row][i] = b[2 - row][i];
        b[2 - row][i] = temp;
    }
}

void turnLeft(int a[3][3]) {
    int temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[i][j] = a[j][2 - i];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            a[i][j] = temp[i][j];
}

void turnRight(int a[3][3]) {
    int temp[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            temp[i][j] = a[2 - j][i];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            a[i][j] = temp[i][j];
}

void operate(Cube *cube, OPcode op) {
    switch (op) {
        case C_Left:
            swapColumn(cube->front, cube->up, op % 10);
            swapColumn_rev(cube->front, cube->back, op % 10);
            swapColumn(cube->front, cube->down, op % 10);
            turnLeft(cube->left);
            break;
        case C_Mid:
            swapColumn(cube->front, cube->up, op % 10);
            swapColumn_rev(cube->front, cube->back, op % 10);
            swapColumn(cube->front, cube->down, op % 10);
            break;
        case C_Right:
            swapColumn(cube->front, cube->up, op % 10);
            swapColumn_rev(cube->front, cube->back, op % 10);
            swapColumn(cube->front, cube->down, op % 10);
            turnRight(cube->right);
            break;
        case R_Up:
            swapRow(cube->front, cube->left, op % 10);
            swapRow_rev(cube->front, cube->back, op % 10);
            swapRow(cube->front, cube->right, op % 10);
            turnRight(cube->up);
            break;
        case R_Mid:
            swapRow(cube->front, cube->left, op % 10);
            swapRow_rev(cube->front, cube->back, op % 10);
            swapRow(cube->front, cube->right, op % 10);
            break;
        case R_Down:
            swapRow(cube->front, cube->left, op % 10);
            swapRow_rev(cube->front, cube->back, op % 10);
            swapRow(cube->front, cube->right, op % 10);
            turnLeft(cube->down);
            break;
        default:
            break;
    }
}

void printCube(int arr[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

int main() {
    Cube cube;
    init(&cube);
    int n;
    scanf("%d", &n);
    while (n--) {
        int op;
        scanf("%d", &op);
        operate(&cube, op);
    }
    printCube(cube.front);
    return 0;
}

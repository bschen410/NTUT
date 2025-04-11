#include <stdio.h>
#include <string.h>

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

void output(int a[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int arr[3][3];
    arr[0][0] = 1;
    arr[0][1] = 2;
    arr[0][2] = 3;
    arr[1][0] = 4;
    arr[1][1] = 5;
    arr[1][2] = 6;
    arr[2][0] = 7;
    arr[2][1] = 8;
    arr[2][2] = 9;
    turnRight(arr);
    output(arr);
}

#include <stdio.h>

typedef struct {
    int top, front, back, left, right, bottom;
} Dice;

void sort_val(int *arr) {
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (arr[i] > arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

int cal_point(int *arr) {
    if (arr[0] == arr[1] && arr[1] == arr[2] && arr[2] == arr[3]) return 18;
    if (arr[0] == arr[1] && arr[2] == arr[3]) return arr[2] + arr[3];
    if (arr[0] == arr[1] && arr[1] == arr[2] || arr[1] == arr[2] && arr[2] == arr[3]) return 0;
    if (arr[0] == arr[1])
        return arr[2] + arr[3];
    else if (arr[1] == arr[2])
        return arr[0] + arr[3];
    else if (arr[2] == arr[3])
        return arr[0] + arr[1];
    return 0;
}

void roll(Dice *dice, int direction) {
    int temp;
    switch (direction) {
        case 1:  // up
            temp = dice->top;
            dice->top = dice->front;
            dice->front = dice->bottom;
            dice->bottom = dice->back;
            dice->back = temp;
            break;
        case 2:  // down
            temp = dice->top;
            dice->top = dice->back;
            dice->back = dice->bottom;
            dice->bottom = dice->front;
            dice->front = temp;
            break;
        case 3:  // left
            temp = dice->top;
            dice->top = dice->left;
            dice->left = dice->bottom;
            dice->bottom = dice->right;
            dice->right = temp;
            break;
        case 4:  // right
            temp = dice->top;
            dice->top = dice->right;
            dice->right = dice->bottom;
            dice->bottom = dice->left;
            dice->left = temp;
            break;
    }
}

int main() {
    Dice dice[4];
    for (int i = 0; i < 4; i++) {
        dice[i].top = 1;
        dice[i].front = 3;
        dice[i].back = 4;
        dice[i].left = 5;
        dice[i].right = 2;
        dice[i].bottom = 6;
    }
    int n;
    scanf("%d", &n);
    while (n--) {
        for (int i = 0; i < 4; i++) {
            int input;
            scanf("%d", &input);
            roll(&dice[i], input);
        }
    }
    int dice_val[4] = {dice[0].top, dice[1].top, dice[2].top, dice[3].top};
    // for (int i = 0; i < 4; i++) printf("%d ", dice_val[i]);
    sort_val(dice_val);
    printf("%d\n", cal_point(dice_val));
    return 0;
}

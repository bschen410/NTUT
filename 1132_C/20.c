#include <stdio.h>

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
    if (arr[0] == arr[1])
        return arr[2] + arr[3];
    else if (arr[1] == arr[2])
        return arr[0] + arr[3];
    else if (arr[2] == arr[3])
        return arr[0] + arr[1];
    return 0;
}

int main() {
    // int dice_map[6][4] = {
    //     {'3, '4, '5, '2},
    //     {3, 4, '1, '6},
    //     {'6, '1, 5, 2},
    //     {'1, '6, 5, 2},
    //     {3, 4, '6, '1},
    //     {'4, '3, '2, '5}};
    int dice_map[6][4] = {
        {3, 4, 5, 2},
        {3, 4, 1, 6},
        {6, 1, 5, 2},
        {1, 6, 5, 2},
        {3, 4, 6, 1},
        {4, 3, 2, 5}};
    int n;
    scanf("%d", &n);
    int cur_val[4] = {1, 1, 1, 1};
    while (n--) {
        for (int i = 0; i < 4; i++) {
            int input;
            scanf("%d", &input);
            cur_val[i] = dice_map[cur_val[i] - 1][input - 1];
        }
    }
    for (int i = 0; i < 4; i++) printf("%d ", cur_val[i]);
    sort_val(cur_val);
    printf("\nPoint: %d\n", cal_point(cur_val));

    // same
    // if (val[a] == val.......) return 18;
    // elif a=b=c or b=c=d return 0
    // elif a=b or b=c or c=d return
    return 0;
}
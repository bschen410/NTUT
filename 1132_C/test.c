#include <stdio.h>

// 上、下、前、後、左、右
void change1(int *data) {
    int answer[6];
    answer[0] = data[3];
    answer[1] = data[2];
    answer[2] = data[0];
    answer[3] = data[1];
    answer[4] = data[4];
    answer[5] = data[5];
    for (int i = 0; i < 6; i++) {
        data[i] = answer[i];
    }
}

void change2(int *data) {
    int answer[6];
    answer[0] = data[2];
    answer[1] = data[3];
    answer[2] = data[1];
    answer[3] = data[0];
    answer[4] = data[4];
    answer[5] = data[5];
    for (int i = 0; i < 6; i++) {
        data[i] = answer[i];
    }
}

void change3(int *data) {
    int answer[6];
    answer[0] = data[4];
    answer[1] = data[5];
    answer[2] = data[2];
    answer[3] = data[3];
    answer[4] = data[1];
    answer[5] = data[0];
    for (int i = 0; i < 6; i++) {
        data[i] = answer[i];
    }
}

void change4(int *data) {
    int answer[6];
    answer[0] = data[5];
    answer[1] = data[4];
    answer[2] = data[2];
    answer[3] = data[3];
    answer[4] = data[0];
    answer[5] = data[1];
    for (int i = 0; i < 6; i++) {
        data[i] = answer[i];
    }
}

int main() {
    int n;
    scanf("%d", &n);
    int answer[4];
    int operation[n][4];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 4; j++) {
            scanf("%d", &operation[i][j]);
        }
    }

    for (int i = 0; i < 4; i++) {
        int data[6] = {1, 6, 4, 3, 5, 2};
        for (int j = 0; j < n; j++) {
            if (operation[j][i] == 1)
                change1(data);
            else if (operation[j][i] == 2)
                change2(data);
            else if (operation[j][i] == 3)
                change3(data);
            else
                change4(data);
            // printf("%d %d %d %d %d %d\n",data[0],data[1],data[2],data[3],data[4],data[5]);
        }
        answer[i] = data[0];
        // printf("i = %d => %d\n",i,data[0]);
    }
    for (int i = 0; i < 4; i++) {
        printf("%d ", answer[i]);
    }
    printf("\n");
    for (int i = 0; i < 4; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (answer[i] > answer[j]) {
                int temp = answer[i];
                answer[i] = answer[j];
                answer[j] = temp;
            }
        }
    }
    int score = 0;
    if (answer[0] == answer[1] && answer[1] == answer[2] && answer[2] == answer[3])
        score = 18;
    else if (answer[0] != answer[1] && answer[1] != answer[2] && answer[2] != answer[3])
        score = 0;
    else if (answer[0] == answer[1] && answer[1] == answer[2] && answer[2] != answer[3])
        score = 0;
    else if (answer[0] != answer[1] && answer[1] == answer[2] && answer[2] == answer[3])
        score = 0;
    else if (answer[0] == answer[1] && answer[2] == answer[3])
        score = answer[2] + answer[3];
    else {
        if (answer[0] == answer[1])
            score = answer[2] + answer[3];
        else if (answer[1] == answer[2])
            score = answer[0] + answer[3];
        else if (answer[2] == answer[3])
            score = answer[0] + answer[1];
    }

    printf("%d\n", score);
}
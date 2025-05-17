#include <stdio.h>
#include <string.h>

typedef struct student_s {
    char name[50];
    int score;
} student_t;

// 新增n位學生的資料
void input(student_t s[], int n) {
    for (int i = 0; i < n; i++)
        scanf("%s %d", s[i].name, &s[i].score);
}

// 回傳班級內分數最高的姓名(使用參數char name[])
void getHigh(student_t s[], int n, char name[], int *highScore) {
    *highScore = s[0].score;
    strcpy(name, s[0].name);
    for (int i = 1; i < n; i++) {
        if (s[i].score > *highScore) {
            *highScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// 回傳班級內分數最低的姓名(使用參數char name[])
void getLow(student_t s[], int n, char name[], int *lowScore) {
    *lowScore = s[0].score;
    strcpy(name, s[0].name);
    for (int i = 1; i < n; i++) {
        if (s[i].score < *lowScore) {
            *lowScore = s[i].score;
            strcpy(name, s[i].name);
        }
    }
}

// 回傳班級內所有學生的平均成績無條件捨去至整數
int getAverage(student_t s[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += s[i].score;
    return sum / n;
}

// 回傳班級內所有學生的中位數成績無條件捨去至整數
int getMedian(student_t s[], int n) {
    int scores[n];
    for (int i = 0; i < n; i++)
        scores[i] = s[i].score;

    // sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (scores[j] > scores[j + 1]) {
                int temp = scores[j];
                scores[j] = scores[j + 1];
                scores[j + 1] = temp;
            }
        }
    }

    if (n % 2 == 0)
        return (scores[n / 2 - 1] + scores[n / 2]) / 2;
    else
        return scores[n / 2];
}

int main() {
    int n;
    scanf("%d", &n);
    student_t s[n];

    input(s, n);

    char highestName[50];
    int highestScore;
    getHigh(s, n, highestName, &highestScore);
    printf("%s %d\n", highestName, highestScore);

    char lowestName[50];
    int lowestScore;
    getLow(s, n, lowestName, &lowestScore);
    printf("%s %d\n", lowestName, lowestScore);

    printf("%d\n", getAverage(s, n));

    printf("%d\n", getMedian(s, n));

    return 0;
}

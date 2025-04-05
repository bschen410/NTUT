#include <stdio.h>
#include <string.h>
#define SIZE 200

int isNum1Neg = 0;
int isNum2Neg = 0;

void inputNum(int *num1, int *num2) {
    char str1[SIZE], str2[SIZE];
    scanf("%s %s", str1, str2);
    for (int i = 0; str1[i] != '\0'; i++) {
        if (str1[i] == '-') {
            num1[i] = 0;
            isNum1Neg = 1;
            continue;
        }
        num1[i] = str1[i] - '0';
    }
    for (int i = 0; str2[i] != '\0'; i++) {
        if (str2[i] == '-') {
            num2[i] = 0;
            isNum2Neg = 1;
            continue;
        }
        num2[i] = str2[i] - '0';
    }
}

void printNum(int *num1, int *num2) {
    printf("num1: ");
    for (int i = 0; i < SIZE; i++) printf("%d", num1[i]);
    printf("\nnum2: ");
    for (int i = 0; i < SIZE; i++) printf("%d", num2[i]);
    printf("\n");
}

void reverse(int *num) {
    int start = 0, end = SIZE - 1;
    while (start < end) {
        int temp = num[start];
        num[start] = num[end];
        num[end] = temp;
        start++;
        end--;
    }
}

int *plus(int *num1, int *num2) {
    static int result[SIZE] = {0};
    int carry = 0;
    for (int i = SIZE - 1; i >= 0; i--) {
        int sum = num1[i] + num2[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    return result;
}

int main() {
    int num1[SIZE] = {0}, num2[SIZE] = {0};
    inputNum(num1, num2);
    reverse(num1);
    reverse(num2);
    // gen by AI
    // if (isNum1Neg && isNum2Neg) {
    //     printf("-");
    // } else if (isNum1Neg || isNum2Neg) {
    //     printf("-");
    // }
    // if (isNum1Neg && isNum2Neg) {
    //     for (int i = 0; i < SIZE; i++) num1[i] = -num1[i];
    //     for (int i = 0; i < SIZE; i++) num2[i] = -num2[i];
    // }
    int *plusAns = plus(num1, num2);
    printNum(num1, num2);
    return 0;
}

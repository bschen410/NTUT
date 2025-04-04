#include <stdio.h>
#include <string.h>
#define SIZE 200

void inputNum(int *num1, int *num2) {
    char str1[SIZE], str2[SIZE];
    scanf("%s %s", str1, str2);
    for (int i = 0; str1[i] != '\0'; i++)
        num1[i] = str1[i] - '0';
    for (int i = 0; str2[i] != '\0'; i++)
        num2[i] = str2[i] - '0';
}

void printNum(int *num1, int*)

int main() {
    int num1[SIZE] = {0}, num2[SIZE] = {0};  // it is reversed BTW
    inputNum(num1, num2);
    for (int i = 0; i < SIZE; i++) printf("%d", num1[i]);
    printf("\n\n");
    for (int i = 0; i < SIZE; i++) printf("%d", num2[i]);
    return 0;
}

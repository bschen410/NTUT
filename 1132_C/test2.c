#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.c"

typedef struct {
    int isNegative;
    int *digitArray;
    char *repr;
} longInt;

longInt subtract(longInt a, longInt b);
longInt strToLongInt(char *str);
longInt add(longInt a, longInt b);
longInt subtract(longInt a, longInt b);
longInt multiply(longInt a, longInt b);


int main() {
    char input1[201], input2[201];
    scanf("%s %s", input1, input2);
    longInt num1 = strToLongInt(input1), num2 = strToLongInt(input2);
    longInt result1 = add(num1, num2), result2 = subtract(num1, num2), result3 = multiply(num1, num2);
    if (result1.isNegative)
        printf("-");
    printf("%s\n", result1.repr);
    if (result2.isNegative)
        printf("-");
    printf("%s\n", result2.repr);
    if (result3.isNegative)
        printf("-");
    printf("%s\n", result3.repr);
}

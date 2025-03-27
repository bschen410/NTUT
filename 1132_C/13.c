#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cvtChar(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return -1;
}

int cvtToDex(char *input, int inCarry) {
    int dex = 0;
    for (int i = 0; i < strlen(input); i++)
        dex += cvtChar(input[i]) * pow(inCarry, strlen(input) - i - 1);
    return dex;
}

char *cvtBase(int dex, int outCarry) {
    char *output = malloc(100);
    int i = 0;
    while (dex) {
        int rem = dex % outCarry;
        if (rem < 10)
            output[i++] = rem + '0';
        else
            output[i++] = rem - 10 + 'A';
        dex /= outCarry;
    }
    output[i] = '\0';
    for (int j = 0; j < i / 2; j++) {
        char temp = output[j];
        output[j] = output[i - j - 1];
        output[i - j - 1] = temp;
    }
    return strlen(output) ? output : "0";
}

int main() {
    int inCarry, outCarry;
    char input[100];
    scanf("%d", &inCarry);
    scanf("%s", input);
    scanf("%d", &outCarry);
    printf("%s\n", cvtBase(cvtToDex(input, inCarry), outCarry));
    return 0;
}

#include <stdio.h>
#include <string.h>

int binary2Decimal(const char *binary) {
    int decimal = 0;
    while (*binary)
        decimal = (decimal << 1) + (*binary++ - '0');
    return decimal;
}

int decimal2Binary(int decimal) {
    int binary = 0, idx = 1;
    while (decimal > 0) {
        binary += (decimal % 2) * idx;
        decimal /= 2;
        idx *= 10;
    }
    return binary;
}

int C(int m, int *time) {
    (*time)++;
    if (m == 0 || m == 1)
        return *time - 1;
    else if (m % 2 == 0)
        return C(m / 2, time);
    else
        return C((m + 1) / 2, time);
}

int main() {
    while (1) {
        char binary[33];
        scanf("%32s", binary);
        if (strcmp(binary, "-1") == 0) break;
        int num = binary2Decimal(binary);
        int time = 0;
        printf("%04d\n", decimal2Binary(C(num, &time)));
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 200

int compare_magnitude(const char *num1, const char *num2) {
    while (*num1 == '0') num1++;
    while (*num2 == '0') num2++;
    int len1 = strlen(num1), len2 = strlen(num2);
    if (len1 != len2) return len1 - len2;
    return strcmp(num1, num2);
}

void big_add(const char *num1, const char *num2, char result[]) {
    int len1 = strlen(num1), len2 = strlen(num2);
    int carry = 0, i = len1 - 1, j = len2 - 1, k = 0;
    char temp[MAX_LEN + 1];

    while (i >= 0 || j >= 0 || carry) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;
        int sum = digit1 + digit2 + carry;
        temp[k++] = (sum % 10) + '0';
        carry = sum / 10;
    }

    for (i = 0; i < k; i++) {
        result[i] = temp[k - 1 - i];
    }
    result[k] = '\0';
}

void big_subtract(const char *num1, const char *num2, char result[]) {
    if (compare_magnitude(num1, num2) < 0) {
        big_subtract(num2, num1, result);
        memmove(result + 1, result, strlen(result) + 1);
        result[0] = '-';
        return;
    }

    int len1 = strlen(num1), len2 = strlen(num2);
    int borrow = 0, i = len1 - 1, j = len2 - 1, k = 0;
    char temp[MAX_LEN + 1];

    while (i >= 0 || j >= 0) {
        int digit1 = (i >= 0) ? num1[i--] - '0' : 0;
        int digit2 = (j >= 0) ? num2[j--] - '0' : 0;

        if (digit1 < digit2 + borrow) {
            digit1 += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        temp[k++] = (digit1 - digit2 - borrow) + '0';
    }

    while (k > 1 && temp[k - 1] == '0') {
        k--;
    }

    for (i = 0; i < k; i++) {
        result[i] = temp[k - 1 - i];
    }
    result[k] = '\0';
}

void big_multiply(const char *num1, const char *num2, char result[]) {
    int len1 = strlen(num1), len2 = strlen(num2);
    int prod[MAX_LEN * 2] = {0};
    int i, j, is_negative = 0;

    if (num1[0] == '-') {
        is_negative ^= 1;
        num1++;
    }
    if (num2[0] == '-') {
        is_negative ^= 1;
        num2++;
    }

    len1 = strlen(num1);
    len2 = strlen(num2);

    for (i = len1 - 1; i >= 0; i--) {
        for (j = len2 - 1; j >= 0; j--) {
            prod[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');
            if (prod[i + j + 1] >= 10) {
                prod[i + j] += prod[i + j + 1] / 10;
                prod[i + j + 1] %= 10;
            }
        }
    }

    i = 0;
    while (i < len1 + len2 && prod[i] == 0) {
        i++;
    }

    if (i == len1 + len2) {
        strcpy(result, "0");
        return;
    }

    j = 0;
    if (is_negative) {
        result[j++] = '-';
    }
    while (i < len1 + len2) {
        result[j++] = prod[i++] + '0';
    }
    result[j] = '\0';
}

int main() {
    char num1[MAX_LEN + 1], num2[MAX_LEN + 1];
    char sum[MAX_LEN + 2], diff[MAX_LEN + 2], prod[MAX_LEN * 2 + 2];

    scanf("%s", num1);
    scanf("%s", num2);

    if (num1[0] == '-' && num2[0] == '-') {
        big_add(num1 + 1, num2 + 1, sum);
        big_subtract(num2 + 1, num1 + 1, diff);
        big_multiply(num1, num2, prod);
        printf("-%s\n%s\n%s\n", sum, diff, prod);
    } else if (num1[0] == '-') {
        big_subtract(num2, num1 + 1, sum);
        big_add(num1 + 1, num2, diff);
        big_multiply(num1, num2, prod);
        printf("%s\n-%s\n%s\n", sum, diff, prod);
    } else if (num2[0] == '-') {
        big_subtract(num1, num2 + 1, sum);
        big_add(num1, num2 + 1, diff);
        big_multiply(num1, num2, prod);
        printf("%s\n-%s\n%s\n", sum, diff, prod);
    } else {
        big_add(num1, num2, sum);
        big_subtract(num1, num2, diff);
        big_multiply(num1, num2, prod);
        printf("%s\n%s\n%s\n", sum, diff, prod);
    }

    return 0;
}

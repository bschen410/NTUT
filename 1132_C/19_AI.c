#include <stdio.h>
#include <string.h>

#define MAX_LEN 45

int compare(char *a, char *b) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    if (len_a != len_b)
        return len_a > len_b;
    return strcmp(a, b) >= 0;
}

void subtract(char *a, char *b, char *result) {
    int len_a = strlen(a);
    int len_b = strlen(b);
    int diff = len_a - len_b;
    int borrow = 0;

    for (int i = len_a - 1; i >= 0; i--) {
        int digit_a = a[i] - '0';
        int digit_b = (i - diff >= 0) ? b[i - diff] - '0' : 0;
        int res = digit_a - digit_b - borrow;
        if (res < 0) {
            res += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = res + '0';
    }

    result[len_a] = '\0';

    int i = 0;
    while (result[i] == '0' && i < len_a - 1)
        i++;
    memmove(result, result + i, len_a - i + 1);
}

void multiply(char *divisor, int digit, char *result) {
    int len = strlen(divisor);
    int carry = 0, pos = 0;
    char temp[MAX_LEN] = {0};

    for (int i = len - 1; i >= 0; i--) {
        int prod = (divisor[i] - '0') * digit + carry;
        temp[pos++] = (prod % 10) + '0';
        carry = prod / 10;
    }
    if (carry)
        temp[pos++] = carry + '0';

    for (int i = 0; i < pos; i++)
        result[i] = temp[pos - i - 1];
    result[pos] = '\0';
}

void divide(char *dividend, char *divisor, char *quotient, char *remainder) {
    int len = strlen(dividend);
    char temp[MAX_LEN] = {0};
    char mult[MAX_LEN] = {0};
    char sub[MAX_LEN] = {0};
    int qpos = 0;

    temp[0] = '\0';

    for (int i = 0; i < len; i++) {
        int tlen = strlen(temp);
        temp[tlen] = dividend[i];
        temp[tlen + 1] = '\0';

        int j = 0;
        while (temp[j] == '0' && j < strlen(temp) - 1) j++;
        memmove(temp, temp + j, strlen(temp) - j + 1);

        int qdigit = 0;
        while (1) {
            multiply(divisor, qdigit + 1, mult);
            if (!compare(temp, mult)) break;
            qdigit++;
        }

        quotient[qpos++] = qdigit + '0';

        multiply(divisor, qdigit, mult);
        subtract(temp, mult, sub);
        strcpy(temp, sub);
    }

    quotient[qpos] = '\0';

    int i = 0;
    while (quotient[i] == '0' && i < qpos - 1) i++;
    memmove(quotient, quotient + i, qpos - i + 1);

    strcpy(remainder, temp);
}

int main() {
    char a[MAX_LEN], k[MAX_LEN];
    char q[MAX_LEN], r[MAX_LEN];

    scanf("%s", a);
    scanf("%s", k);

    divide(a, k, q, r);

    printf("%s\n", q);
    printf("%s\n", r);

    return 0;
}

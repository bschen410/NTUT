#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 300

int isNum(char c) {
    return (c >= '0' && c <= '9') ? 1 : 0;
}

char *reverse(char *c) {
    for (int i = 0, j = strlen(c) - 1; i < j; i++, j--) {
        char temp = c[i];
        c[i] = c[j];
        c[j] = temp;
    }
    return c;
}

char *plus(char *x, char *y) {
    char *ans = (char *)malloc(SIZE);
    int k = 0;
    for (int i = strlen(x) - 1, j = strlen(y) - 1, carry = 0; i >= 0 || j >= 0 || carry; i--, j--, k++) {
        ans[k] = ((i >= 0) ? x[i] : '0') + ((j >= 0) ? y[j] : '0') + carry - '0';
        carry = (ans[k] - '0') / 10;
        ans[k] = (ans[k] - '0') % 10 + '0';
    }
    ans[k] = '\0';
    return reverse(ans);
}

char *minus(char *x, char *y) {
    char *ans = (char *)malloc(SIZE);
    int isNeg = 0;
    if (strlen(x) < strlen(y) || (strlen(x) == strlen(y) && strcmp(x, y) < 0)) {
        char *temp = x;
        x = y;
        y = temp;
        isNeg = 1;
    }
    for (int i = strlen(x) - 1, j = strlen(y) - 1, k = 0, carry = 0; i >= 0 || j >= 0; i--, j--, k++) {
        ans[k] = ((i >= 0) ? x[i] : '0') - ((j >= 0) ? y[j] : '0') - carry + '0';
        carry = (ans[k] - '0') < 0;
        ans[k] = (ans[k] - '0' + 10) % 10 + '0';
    }
    strcat(ans, "-");
    return reverse(ans);
}

char *multiply(char *x, char *y) {
    char *ans = (char *)malloc(SIZE);
    memset(ans, '0', SIZE);
    int k;
    ans[0] = (x[0] == '-' ^ y[0] == '-') ? '-' : '+';
    for (int i = strlen(x) - 1; i >= 0 && isNum(x[i]); i--) {
        int t = i - strlen(x) + 1;
        for (int j = strlen(y) - 1; j >= 0 && isNum(y[i]); j--) {
            int tmp = (x[i] - '0') * (y[j] - '0') * pow(10, t++);
            for (k = i; tmp > 0; k++) {
                ans[k] += (tmp % 10);
                if (ans[k] > '9') {
                    ans[k + 1] += (ans[k] - '0') / 10;
                    ans[k] %= 10;
                }
                tmp /= 10;
            }
        }
    }
    ans[k + 1] = '\0';
    return reverse(ans);
}

int main() {
    char x[200], y[200];
    scanf("%s %s", x, y);
    printf("%s\n", plus(x, y));
    printf("%s\n", minus(x, y));
    printf("%s\n", multiply(x, y));
    return 0;
}

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
    int isNegX = (x[0] == '-');
    int isNegY = (y[0] == '-');
    if (isNegX) x++;
    if (isNegY) y++;

    int len_x = strlen(x);
    int len_y = strlen(y);
    int *temp = (int *)calloc(len_x + len_y, sizeof(int));  // 暫存結果
    char *ans = (char *)malloc(SIZE);
    memset(ans, 0, SIZE);

    // 從低位開始逐位相乘
    for (int i = len_x - 1; i >= 0; i--) {
        for (int j = len_y - 1; j >= 0; j--) {
            int mul = (x[i] - '0') * (y[j] - '0');
            int pos_low = (len_x - 1 - i) + (len_y - 1 - j);
            int pos_high = pos_low + 1;

            temp[pos_low] += mul;                  // 加到低位
            temp[pos_high] += temp[pos_low] / 10;  // 處理進位
            temp[pos_low] %= 10;                   // 保留個位數
        }
    }

    // 將結果轉換為字串
    int k = 0;
    int start = len_x + len_y - 1;
    while (start >= 0 && temp[start] == 0) {
        start--;  // 移除前導零
    }
    if (start < 0) {
        strcpy(ans, "0");  // 如果結果為 0
    } else {
        for (int i = start; i >= 0; i--) {
            ans[k++] = temp[i] + '0';
        }
        ans[k] = '\0';
    }

    free(temp);  // 釋放暫存陣列
    if (isNegX != isNegY) { // 如果符號不同，結果為負數
        char *result = (char *)malloc(SIZE);
        result[0] = '-';
        strcpy(result + 1, ans);
        free(ans);
        return result;
    }
    return ans;
}

int main() {
    char x[200], y[200];
    scanf("%s %s", x, y);
    printf("%s\n", plus(x, y));
    printf("%s\n", minus(x, y));
    printf("%s\n", multiply(x, y));
    return 0;
}

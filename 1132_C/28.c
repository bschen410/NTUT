#include <stdio.h>

int checkAlpha(char c) {
    if (c >= 'a' && c <= 'z') return 1;
    if (c >= 'A' && c <= 'Z') return 2;
    return 0;
}

int alternating_string() {
    char str[1000];
    int k;
    scanf("%s %d", str, &k);
    int maxLen = 0;
    for (int i = 0; str[i]; i++) {
        int len = 0, count = 0, flag = 0;
        for (int j = i; str[j]; j++) {
            if (checkAlpha(str[j]) == flag) {
                count++;
            } else {
                flag = checkAlpha(str[j]);
                len = 0;
                count = 1;
            }
            if (count == k) {
                flag = 3 - flag;
                len += k;
                count = 0;
                if (len > maxLen) maxLen = len;
            }
        }
    }
    if (maxLen <= k) return 0;
    return maxLen;
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) printf("%d\n", alternating_string());
    return 0;
}

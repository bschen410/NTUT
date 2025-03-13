#include <math.h>
#include <stdio.h>
#include <string.h>

char G(int n, int k) {
    char tmp[100] = {};
    if (n == 1 && k == 0) {
        return "0";
    } else if (n == 1 && k == 1) {
        return "1";
    } else if (k < pow(2, n - 1)) {
        strcat(tmp, "0");
        strcat(tmp, G(n - 1, k));
        return tmp;
    } else {
        strcat(tmp, "1");
        strcat(tmp, G(n - 1, pow(2, n) - 1 - k));
        return tmp;
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    printf("%s", G(4, 7));
    return 0;
}

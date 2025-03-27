#include <math.h>
#include <stdio.h>
#include <string.h>

char *G(int n, int k) {
    char tmp[100] = {};
    if (n == 1 && k == 0) {
        return "0";
    } else if (n == 1 && k == 1) {
        return "1";
    } else if (k < pow(2, n - 1)) {
        printf("0");
        return G(n - 1, k);
    } else {
        printf("1");
        return G(n - 1, pow(2, n) - 1 - k);
    }
}

int main() {
    while (1) {
        int n, k;
        scanf("%d", &n);
        if (n == -1) break;
        scanf("%d", &k);
        printf("%s\n", G(n, k));
    }
    return 0;
}

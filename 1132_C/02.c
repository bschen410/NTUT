#include <math.h>
#include <stdio.h>

int main() {
    int times = 5, i, score = 0;
    int n, status = 0, out = 0;
    while (times) {
        scanf("%d", &n);
        if (n == 0) {
            out++;
            times--;
            if (out == 3) {
                status = 0;
                out = 0;
            }
            continue;
        }
        status <<= n;
        status += pow(2, n - 1);
        for (i = 6; i >= 3; i--)
            if (status >= pow(2, i)) {
                score++;
                status -= pow(2, i);
            }
        times--;
    }
    printf("%d\n", score);
    //
    int stat[3] = {0, 0, 0};
    for (i = 0; i < 3; i++) {
        stat[i] = status % 2;
        status /= 2;
    }
    for (i = 0; i < 3; i++)
        printf("%d ", stat[i]);
    return 0;
}

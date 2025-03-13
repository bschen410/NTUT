#include <stdio.h>
#include <string.h>

float cvtPoint(char *c) {
    if (strcmp(c, "A") == 0)
        return 1;
    else if (strcmp(c, "J") == 0 || strcmp(c, "Q") == 0 || strcmp(c, "K") == 0)
        return 0.5;
    else if (strcmp(c, "10") == 0)
        return 10;
    else
        return c[0] - '0';
}

int main() {
    float sum[2] = {0};
    for (int i = 0; i < 2; i++) {
        char a[10], b[10], c[10];
        scanf(" %s %s %s", &a, &b, &c);
        sum[i] = cvtPoint(a) + cvtPoint(b) + cvtPoint(c);
        if (sum[i] > 10.5) sum[i] = 0;
    }
    // printf("%.2f %.2f\n", sum[0], sum[1]);
    for (int i = 0; i < 2; i++)
        if (sum[i] - (int)sum[i])
            printf("%.1f\n", sum[i]);
        else
            printf("%d\n", (int)sum[i]);
    if (sum[0] > sum[1])
        printf("X Win\n");
    else if (sum[0] < sum[1])
        printf("Y Win\n");
    else
        printf("Tie\n");
    return 0;
}

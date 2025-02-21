#include <math.h>
#include <stdio.h>

int main() {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    double x1, x2;
    double n = b * b - 4 * a * c;
    if (n >= 0) {
        x1 = ((-b) + sqrt(n)) / (2 * a);
        x2 = ((-b) - sqrt(n)) / (2 * a);
        if (x1 == x2) {
            printf("%.1f\n", x1);
        } else {
            printf("%.1f\n%.1f\n", x1, x2);
        }
    } else {
        x1 = (-b) / (2.0 * a);
        x2 = fabs(sqrt(-n) / (2 * a));
        printf("%.1f+%.1fi\n%.1f-%.1fi\n", x1, x2, x1, x2);
    }
    return 0;
}

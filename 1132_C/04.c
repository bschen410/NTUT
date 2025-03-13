#include <stdio.h>

int cvt(double x) {
    double d = (int)(x * 10) % 10;
    if (d < 5)
        return (int)x;
    else if (d > 5)
        return (int)x + 1;
    else if ((int)x % 2 == 0)
        return (int)x + 1;
    else
        return (int)x;
}

int main() {
    float w, h;
    double bmi;
    scanf("%f %f", &w, &h);
    if (!(20 <= w && w <= 200) || !(100 <= h && h <= 200)) {
        printf("ERROR\n");
        return 0;
    }
    bmi = w / (h / 100 * h / 100);
    bmi = cvt(bmi);
    printf("%.0lf\n", bmi);
    if (bmi < 18)
        printf("too low");
    else if (bmi > 24)
        printf("too high");
    return 0;
}

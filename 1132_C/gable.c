#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int a;
double f1(double x) { return sqrt(a - x * x); }
double f2(double x) { return (a * pow(x, 3) + 7 * x) / sqrt(a + x); }

void integral(double (*fptr)(double), double p, double q, double err) {
    int n = 2;
    double sum = 0.0;
    double h;
    double before, after;
    for (int i = 1; i < n; i++) sum += (*fptr)(p + i * ((q - p) * 1.0 / n));
    before = (q - p) * 1.0 / (2 * 2) * ((*fptr)(p) + (*fptr)(q) + 2 * sum);
    double estimated_error;
    double target_error = pow(10, -err);

    do {
        sum = 0.0;
        n *= 2;
        after = ((*fptr)(p) + (*fptr)(q));
        for (int i = 1; i < n; i++) after += 2.0 * (*fptr)(p + i * ((q - p) * 1.0) / n);
        after = after * (((q - p) * 1.0 / n) / 2);
        estimated_error = fabs(after - before);
        printf("err:%.16f, %.12f\n", estimated_error, after);
        before = after;
    } while (estimated_error > target_error);
    printf("result:%.12f\n", after);
}

int main() {
    int funcType, p, q, err;
    scanf(" %d", &funcType);
    while (funcType != 0) {
        if (funcType != 1 && funcType != 2)
            printf("Invalid\n");
        else
            scanf(" %d %d %d %d", &a, &p, &q, &err);

        if (funcType == 1)
            integral(f1, p, q, err);
        else if (funcType == 2)
            integral(f2, p, q, err);
        scanf(" %d", &funcType);
    }
}
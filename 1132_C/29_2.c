#include <math.h>
#include <stdio.h>

double f1(double a, double x) {
    double val = a - x * x;
    if (val < 0) return NAN;
    return sqrt(val);
}

double f2(double a, double x) {
    double val = a + x;
    if (val < 0) return NAN;
    // return (a * x * x * x + 7 * x) / sqrt(a + x);
    return (a * pow(x, 3) + 7 * x) / sqrt(a + x);
}

double trapezoidal(double (*f)(double, double), double a, double p, double q, int err_digits) {
    int n = 1;
    double h, T_prev = 0, T_curr;
    double epsilon = pow(10, -err_digits);

    while (1) {
        //
        double fp = f(a, p);
        double fq = f(a, q);
        if (isnan(fp) || isnan(fq)) return NAN;
        //

        h = (q - p) * 1.0 / n;
        double sum = 0.0;

        T_curr = f(a, p) + f(a, q);
        for (int i = 1; i < n; i++) {
            //
            double xi = p + i * h;
            double fx = f(a, xi);
            if (isnan(fx)) return NAN;
            //
            T_curr += 2.0 * f(a, p + i * h);
            // double xi = p + i * h;
            // sum += f(a, xi);
        }
        T_curr *= (h / 2.0);
        // T_curr = (h / 2.0) * (f(a, p) + f(a, q)) + h * sum;

        if (n > 1 && fabs(T_curr - T_prev) < epsilon)
            break;

        T_prev = T_curr;
        n *= 2;
    }

    return T_curr;
}

int main() {
    int choice;
    while (scanf(" %d", &choice) == 1) {
        if (choice == 0) break;
        if (choice != 1 && choice != 2) {
            printf("Invalid\n");
            continue;
        }
        int a, p, q;
        int err;
        scanf(" %d %d %d %d", &a, &p, &q, &err);
        // if (scanf(" %lf %lf %lf %d", &a, &p, &q, &err) != 4 || err <= 0) {
        //     printf("Invalid\n");
        //     continue;
        // }

        double result;
        if (choice == 1)
            result = trapezoidal(f1, a, p, q, err);
        else if (choice == 2)
            result = trapezoidal(f2, a, p, q, err);
        printf("%.12lf\n", result);
    }
    return 0;
}

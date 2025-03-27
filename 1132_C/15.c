#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false,
    true
} BOOL;
BOOL is_m_zero = false;

void simplify(int *x, int *y) {
    int a = abs(*x), b = abs(*y);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    *x /= gcd;
    *y /= gcd;
}

void print_m(int x_dis, int y_dis) {
    if (y_dis % x_dis == 0) {
        if (y_dis / x_dis == 1)
            printf("x ");
        else if (y_dis / x_dis == -1)
            printf("-x ");
        else if (y_dis / x_dis != 0)
            printf("%dx ", y_dis / x_dis);
        else
            is_m_zero = true;
    } else {
        if (x_dis * y_dis < 0)
            printf("-%d/%dx ", abs(y_dis), abs(x_dis));
        else
            printf("%d/%dx ", abs(y_dis), abs(x_dis));
    }
}

void print_b(int b1, int b2) {
    if (b1 == 0) return;
    if (is_m_zero == false && (b1 * b2) > 0) {
        printf("+ ");
    }
    if (b1 % b2 == 0) {
        if (b1 / b2 > 0)
            printf("%d", b1 / b2);
        else if (is_m_zero == true)
            printf("-%d", abs(b1 / b2));
        else
            printf("- %d", abs(b1 / b2));
    } else {
        if (b1 * b2 < 0)
            printf("- %d/%d", abs(b1), abs(b2));
        else
            printf("%d/%d", abs(b1), abs(b2));
    }
}

int main() {
    int n;
    scanf("%d", &n);
    while (n--) {
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        int x_dis = x1 - x2, y_dis = y1 - y2;
        simplify(&x_dis, &y_dis);
        int b1 = x2 * y1 - x1 * y2, b2 = x2 - x1;
        simplify(&b1, &b2);
        // print result
        printf("y = ");
        print_m(x_dis, y_dis);
        print_b(b1, b2);
        printf("\n");
    }
    return 0;
}

#include <ctype.h>
#include <stdio.h>

int n, m;

void f1(int x) {
    char alpha = 'A' - 1;
    while (x--) {
        for (int i = 0; i < x; i++) printf("#");
        for (int i = 1; i <= 2 * (m - x) - 1; i++) {
            if (i % 2)
                printf("*");
            else
                printf("%c", alpha);
        }
        alpha++;
        if (alpha > 'C') alpha = 'A';
        for (int i = 0; i < x; i++) printf("#");
        printf("\n");
    }
}

void f2(int x) {
    while (x--) {
        for (int i = m - x; i > 0; i--) printf("%d", i);
        for (int i = 0; i < 2 * x + 2; i++) printf("*");
        for (int i = 1; i <= m - x; i++) printf("%d", i);
        printf("\n");
    }
}

int main() {
    scanf("%d %d", &n, &m);
    if (!(1 <= n && n <= 2 && 2 <= m && m <= 9)) {
        printf("error\n");
        return 0;
    }
    if (n == 1)
        f1(m);
    else if (n == 2)
        f2(m);
    return 0;
}

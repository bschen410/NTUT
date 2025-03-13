#include <math.h>
#include <stdbool.h>
#include <stdio.h>

bool chkError(int s0, int s1, char e1, char e2) {
    bool flag = false;
    if (s0 < 0 || s0 > 63) {
        printf("S0 ERROR\n");
        flag = true;
    }
    if (s1 < 0 || s1 > 63) {
        printf("S1 ERROR\n");
        flag = true;
    }
    if (e1 < 'a' || e1 > 'f') {
        printf("e1 ERROR\n");
        flag = true;
    }
    if (e2 < 'a' || e2 > 'f') {
        printf("e2 ERROR\n");
        flag = true;
    }
    return flag;
}

int main() {
    int s0, s1, s2;
    char e1, e2;
    scanf("%d %d %c %c", &s0, &s1, &e1, &e2);
    if (chkError(s0, s1, e1, e2)) return 0;
    s2 = s1 | (int)pow(2, (int)(e1 - 97));
    //
    // printf("e2: %d\n", (int)pow(2, (int)(e2 - 97)));
    // printf("s2: %d\n", s1);
    // printf("%d\n", (int)pow(2, (int)(e2 - 97)) & s2);
    printf(((int)pow(2, (int)(e2 - 97)) & s2) > 0 ? "Y\n" : "N\n");
    printf(!(~s0 & s2) ? "Y\n" : "N\n");
    printf("%d\n", s0 & s2);
    printf("%d\n", s0 | s2);
    printf("%d\n", (63 - s2) & s0);

    return 0;
}

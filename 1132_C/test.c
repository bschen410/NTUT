#include <stdio.h>

typedef struct flag_s {
    unsigned b0: 2;
    unsigned b1: 1;
    unsigned b2: 2;
    unsigned b3: 1;
    unsigned b4: 2;
    unsigned status: 3;
} flag_t;

int main() {
    flag_t flag;
    scanf("%x", &flag);
    printf("%d %d\n", sizeof(unsigned), sizeof(flag_t));
    printf("%d %d %d\n", flag.b2, flag.b1, flag.b0);
    printf("%d %d %d\n", flag.status, flag.b4, flag.b3);
    return 0;
}

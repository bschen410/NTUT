#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int size = 300;
    char *c = (char *)malloc(size);
    c[0] = 'a';
    c[1] = 'b';
    c[2] = '\0';
    printf("%s", c);
    printf("%d", sizeof(c));
    return 0;
}

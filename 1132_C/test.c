#include <stdio.h>
#include <string.h>

void com(char *a, char **aa) {
    aa = a;
    printf("%s\n", aa);
}

int main() {
    char *a = "hello";
    char *aa;
    com(a, aa);
    return 0;
}

#include <stdio.h>
#include <string.h>

int myStrlen(char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

int main() {
    printf("%d\n", myStrlen("123456"));
}

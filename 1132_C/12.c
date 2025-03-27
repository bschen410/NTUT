#include <ctype.h>
#include <stdio.h>
#include <string.h>

int isError(char *str1, char *str2) {
    if (!(isalpha(str1[0]) && !(str1[0] == '_'))) return 1;
    if (!(isalpha(str2[0]) && !(str2[0] == '_'))) return 1;
    if (!(isalpha(str1[strlen(str1) - 1])) && !(str1[strlen(str1) - 1] == '_')) return 1;
    if (!(isalpha(str2[strlen(str2) - 1])) && !(str2[strlen(str2) - 1] == '_')) return 1;
    return 0;
}

void printRev(char *str) {
    for (int i = strlen(str) - 1; i >= 0; i--)
        printf("%c", str[i]);
    printf("\n");
}

int strLength(char *str) {
    int count = 0, i = 0;
    while (str[i] != '\0') {
        if (str[i] != ' ') count++;
        i++;
    }
    return count;
}

int main() {
    char str1[100], str2[100];
    gets(str1);
    gets(str2);
    if (isError(str1, str2)) {
        printf("Error\n");
        return 0;
    }
    printRev(str1);
    printRev(str2);
    printf("%s\n", strLength(str1) >= strLength(str2) ? str1 : str2);
    return 0;
}

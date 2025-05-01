#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 200

char *replace(char *words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1) - 1;
    int len2 = strlen(str2) - 1;
    while (words[i] != '\0') {
        if (strncmp(&words[i], str1, len1) == 0) {
            strncpy(&result[k], str2, len2);
            k += len2;
            i += len1;
        } else {
            result[k++] = words[i++];
        }
    }
    return result;
}

char *insert_front(char *words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1) - 1;
    int len2 = strlen(str2) - 1;
    while (words[i] != '\0') {
        if (strncmp(&words[i], str1, len1) == 0) {
            strncpy(&result[k], str2, len2);
            k += len2;
            result[k++] = ' ';
            strncpy(&result[k], &words[i], len1);
            k += len1;
            i += len1;
        } else {
            result[k++] = words[i++];
        }
    }
    return result;
}

char *insert_back(char *words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1) - 1;
    int len2 = strlen(str2) - 1;
    while (words[i] != '\0') {
        if (strncmp(&words[i], str1, len1) == 0) {
            strncpy(&result[k], &words[i], len1);
            k += len1;
            result[k++] = ' ';
            strncpy(&result[k], str2, len2);
            k += len2;
            i += len1;
        } else {
            result[k++] = words[i++];
        }
    }
    return result;
}

int main() {
    char words[SIZE], str1[SIZE], str2[SIZE];
    fgets(words, SIZE, stdin);
    fgets(str1, SIZE, stdin);
    fgets(str2, SIZE, stdin);
    printf("%s", replace(words, str1, str2));
    printf("%s", insert_front(words, str1, str2));
    printf("%s", insert_back(words, str1, str2));
    return 0;
}

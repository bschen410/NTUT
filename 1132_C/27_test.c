#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 200

char **split(char *input) {
    char **result = (char **)malloc(SIZE * sizeof(char *));
    int i = 0, j = 0, k = 0;
    for (int s = 0; s < SIZE; s++) {
        result[s] = (char *)malloc(SIZE * sizeof(char));
    }
    while (input[i] != '\0') {
        if (input[i] == ' ') {
            result[j][k] = '\0';
            j++;
            k = 0;
        } else {
            result[j][k++] = input[i];
        }
        i++;
    }
    result[j][k] = '\0';
    result[j + 1] = NULL;
    return result;
}

char *replace(char **words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    while (words[i] != NULL) {
        if ((strlen(words[i]) - 1 == len1 && !isalpha(words[i][strlen(words[i]) - 1]) && strncmp(words[i], str1, len1) == 0) ||
            (strlen(words[i]) == len1 && strncmp(words[i], str1, len1) == 0)) {
            strncpy(&result[k], str2, len2);
            k += len2;
            for (int s = 0; s < (strlen(words[i]) - len1); s++) {
                result[k++] = words[i][s + len1];
            }
            result[k++] = ' ';
        } else {
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
        }
        i++;
    }
    result[k - 1] = '\0';
    printf("%s\n", result);
    // return result;
}

char *insert_front(char **words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    while (words[i] != NULL) {
        if ((strlen(words[i]) - 1 == len1 && !isalpha(words[i][strlen(words[i]) - 1]) && strncmp(words[i], str1, len1) == 0) ||
            (strlen(words[i]) == len1 && strncmp(words[i], str1, len1) == 0)) {
            strncpy(&result[k], str2, len2);
            k += len2;
            result[k++] = ' ';
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
        } else {
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
        }
        i++;
    }
    result[k - 1] = '\0';
    printf("%s\n", result);
    // return result;
}

char *insert_back(char **words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    while (words[i] != NULL) {
        if ((strlen(words[i]) - 1 == len1 && !isalpha(words[i][strlen(words[i]) - 1]) && strncmp(words[i], str1, len1) == 0) ||
            (strlen(words[i]) == len1 && strncmp(words[i], str1, len1) == 0)) {
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
            strncpy(&result[k], str2, len2);
            k += len2;
            result[k++] = ' ';
        } else {
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
        }
        i++;
    }
    result[k - 1] = '\0';
    printf("%s\n", result);
    // return result;
}

char *removeWord(char **words, char *str1, char *str2) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int i = 0, j = 0, k = 0;
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    while (words[i] != NULL) {
        if ((strlen(words[i]) - 1 == len1 && !isalpha(words[i][strlen(words[i]) - 1]) && strncmp(words[i], str1, len1) == 0) ||
            (strlen(words[i]) == len1 && strncmp(words[i], str1, len1) == 0)) {
            //
        } else {
            strncpy(&result[k], words[i], strlen(words[i]));
            k += strlen(words[i]);
            result[k++] = ' ';
        }
        i++;
    }
    result[k - 1] = '\0';
    printf("%s\n", result);
    // return result;
}

char *reverse(char **words) {
    char *result = (char *)malloc(SIZE);
    memset(result, '\0', SIZE);
    int len;
    for (len = 0; words[len]; len++);
    len--;
    for (; len >= 0; len--) {
        strcat(result, words[len]);
        strcat(result, " ");
    }
    printf("%s\n", result);
    // return result;
}

int main() {
    char words[SIZE], str1[SIZE], str2[SIZE];
    fgets(words, SIZE, stdin);
    fgets(str1, SIZE, stdin);
    fgets(str2, SIZE, stdin);
    words[strcspn(words, "\n")] = '\0';
    str1[strcspn(str1, "\n")] = '\0';
    str2[strcspn(str2, "\n")] = '\0';
    char **sep_words = split(words);
    replace(sep_words, str1, str2);
    insert_front(sep_words, str1, str2);
    insert_back(sep_words, str1, str2);
    removeWord(sep_words, str1, str2);
    reverse(sep_words);
    return 0;
}

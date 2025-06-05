#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int coef;      // 係數
    int exp;       // 次方數
    struct Node* next;
} Node;

// 建立新節點
Node* createNode(int coef, int exp) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->exp = exp;
    newNode->next = NULL;
    return newNode;
}

// 插入節點，並照次方從大到小排序 + 合併同次項）
void insertNode(Node** head, int coef, int exp) {
    if (coef == 0) return;
    Node *prev = NULL, *curr = *head;
    while (curr && curr->exp > exp) {
        prev = curr;
        curr = curr->next;
    }
    if (curr && curr->exp == exp) {
        curr->coef += coef;
        if (curr->coef == 0) { // 刪除節點
            if (prev) prev->next = curr->next;
            else *head = curr->next;
            free(curr);
        }
    } else {
        Node* newNode = createNode(coef, exp);
        if (prev) {
            newNode->next = prev->next;
            prev->next = newNode;
        } else {
            newNode->next = *head;
            *head = newNode;
        }
    }
}

// 輸出多項式
void printPoly(Node* head) {
    if (!head) {
        printf("0\n");
        return;
    }
    int first = 1;
    while (head) {
        int c = head->coef, e = head->exp;
        if (c == 0) {
            head = head->next;
            continue;
        }
        if (!first && c > 0) printf("+");

        if (e == 0) {
            printf("%d", c);
        } else {
            if (c == 1) printf("x");
            else if (c == -1) printf("-x");
            else printf("%dx", c);

            if (e != 1)
                printf("^%d", e);
        }
        first = 0;
        head = head->next;
    }
    printf("\n");
}

// 釋放記憶體
void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

int main() {
    Node* poly = NULL;
    int arr1[100], arr2[100];
    int len1 = 0, len2 = 0;
    char ch;

    while (scanf("%d", &arr1[len1++]) && (ch = getchar()) != '\n');
    while (scanf("%d", &arr2[len2++]) && (ch = getchar()) != '\n');

    for (int i = 0; i < len1; i++)
        insertNode(&poly, arr1[i], len1 - 1 - i);
    for (int i = 0; i < len2; i++)
        insertNode(&poly, arr2[i], len2 - 1 - i);

    printPoly(poly);

    freeList(poly);
    return 0;
}

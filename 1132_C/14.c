#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int inte;  // integer
    int nume;  // numerator
    int deno;  // denominator
} Fraction;

void dealWithInput(char *input, Fraction *f) {
    if (sscanf(input, "%d(%d/%d)", &f->inte, &f->nume, &f->deno) == 3) {
        return;
    } else if (sscanf(input, "%d/%d", &f->nume, &f->deno) == 2) {
        f->inte = 0;
    } else {
        f->inte = atoi(input);
        f->nume = 0;
        f->deno = 1;
    }
}

void mixedToFraction(Fraction *f) {
    if (f->inte < 0) f->nume *= -1;
    f->nume += f->inte * f->deno;
    f->inte = 0;
}

void simplify(int *x, int *y) {
    int a = abs(*x), b = abs(*y);
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    int gcd = a;
    *x /= gcd;
    *y /= gcd;
}

void printAns(Fraction *ans) {
    if (ans->inte != 0) {
        if (ans->nume != 0)
            printf("%d(%d/%d)\n", ans->inte, ans->nume, ans->deno);
        else
            printf("%d\n", ans->inte);
    } else {
        if (ans->nume == 0)
            printf("0\n");
        else
            printf("%d/%d\n", ans->nume, ans->deno);
    }
}

void calculate(Fraction *a, Fraction *b, char operator, Fraction * ans) {
    mixedToFraction(a);
    mixedToFraction(b);
    switch (operator) {
        case '+':
            ans->nume = a->nume * b->deno + b->nume * a->deno;
            ans->deno = a->deno * b->deno;
            break;
        case '-':
            ans->nume = a->nume * b->deno - b->nume * a->deno;
            ans->deno = a->deno * b->deno;
            break;
        case '*':
            ans->nume = a->nume * b->nume;
            ans->deno = a->deno * b->deno;
            break;
        case '/':
            ans->nume = a->nume * b->deno;
            ans->deno = a->deno * b->nume;
            break;
    }
    if (ans->deno == 0) {
        printf("Error\n");
        return;
    }
    simplify(&ans->nume, &ans->deno);
    ans->inte = ans->nume / ans->deno;
    ans->nume %= ans->deno;
    if (ans->inte != 0 && ans->nume < 0)
        ans->nume = abs(ans->nume);
    printAns(ans);
}

int main() {
    while (1) {
        char input_a[100], input_b[100], operator, tmp;
        scanf("%s %c %s", input_a, &operator, input_b);
        Fraction *a = (Fraction *)malloc(sizeof(Fraction));
        Fraction *b = (Fraction *)malloc(sizeof(Fraction));
        Fraction *ans = (Fraction *)malloc(sizeof(Fraction));
        dealWithInput(input_a, a);
        dealWithInput(input_b, b);
        if (a->deno == 0 || b->deno == 0) {
            printf("Error\n");
            goto NEXT;
        }
        calculate(a, b, operator, ans);
    NEXT:
        free(a);
        free(b);
        free(ans);
        // fflush(stdin);
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        if (getchar() == 'n') break;
    }
    return 0;
}

#include <ctype.h>
#include <stdio.h>

typedef enum {
    start,
    build_number,
    build_float,
    build_neg,
    build_variable,
    build_string,
    zero,
    neg_zero,
    dot,
    // result
    integer,
    floating,
    variable,
    string
} state_t;

state_t next_state(state_t cur_state, char c) {
    if (cur_state == start) {
        if (c == '-') {
            return build_neg;
        } else if (isdigit(c) && c != '0') {
            return build_number;
        } else if (c == '0') {
            return zero;
        } else if (isalpha(c) || c == '_') {
            return build_variable;
        } else {
            return build_string;
        }
    } else if (cur_state == build_number) {
        if (isdigit(c)) {
            return build_number;
        } else if (c == '.') {
            return dot;
        } else if (c == '\0') {
            return integer;
        }
    } else if (cur_state == zero) {
        if (c == '.') {
            return dot;
        } else if (c == '\0') {
            return integer;
        }
    } else if (cur_state == build_neg) {
        if (c == '0') {
            return neg_zero;
        } else if (isdigit(c)) {
            return build_number;
        }
    } else if (cur_state == neg_zero) {
        if (c == '.') {
            return dot;
        }
    } else if (cur_state == dot) {
        if (isdigit(c)) {
            return build_float;
        }
    } else if (cur_state == build_float) {
        if (isdigit(c)) {
            return build_float;
        } else if (c == '\0') {
            return floating;
        }
    } else if (cur_state == build_variable) {
        if (isalnum(c) || c == '_') {
            return build_variable;
        } else if (c == '\0') {
            return variable;
        }
    } else if (cur_state == build_string) {
        if (c == '\0') {
            return string;
        }
    }
    return string;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        state_t current_state = start;
        char c[100];
        int index = 0;
        scanf("%s", c);
        do {
            current_state = next_state(current_state, c[index]);
        } while (c[index++] != '\0');
        if (current_state == integer) {
            printf("integer\n");
        } else if (current_state == floating) {
            printf("float\n");
        } else if (current_state == variable && index <= 11) {
            printf("variable\n");
        } else {
            printf("string\n");
        }
    }
    return 0;
}

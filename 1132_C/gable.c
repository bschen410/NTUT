#include <ctype.h>
#include <stdio.h>
typedef enum {
    start,
    negative,
    integer,
    build_number,
    zero,
    neg_zero,
    point,
    floating_point,
    build_floating_point,
    variable,
    build_variable,
    string
} state_t;

state_t next_state(state_t current_state, char c) {
    if (current_state == start) {
        if (c == '-') {
            return negative;
        } else if (c != '0' && isdigit(c)) {
            return build_number;
        } else if (c == '0') {
            return zero;
        } else if (isalpha(c) || c == '_') {
            return build_variable;
        }
    } else if (current_state == build_number) {
        if (isdigit(c)) {
            return build_number;
        } else if (c == '.') {
            return point;
        } else if (c == '\0') {
            return integer;
        }
    } else if (current_state == zero) {
        if (c == '.') {
            return point;
        } else if (c == '\0') {
            return integer;
        }
    } else if (current_state == negative) {
        if (c == '0') {
            return neg_zero;
        } else if (isdigit(c)) {
            return build_number;
        }
    } else if (current_state == neg_zero) {
        if (c == '.')
            return point;
    } else if (current_state == point) {
        if (isdigit(c)) {
            return build_floating_point;
        }
    } else if (current_state == build_floating_point) {
        if (isdigit(c)) {
            return build_floating_point;
        } else if (c == '\0') {
            return floating_point;
        }
    } else if (current_state == build_variable) {
        if (isalpha(c) || isdigit(c) || c == '_') {
            return build_variable;
        } else if (c == '\0') {
            return variable;
        }
    }
    return string;
}
void detect_type() {
    char str[100];
    int index = 0;
    scanf("%s", str);
    state_t current_state = start;
    do {
        current_state = next_state(current_state, str[index]);
        if (current_state == string && str[index] == '\0') {
            printf("string\n");
        } else if (current_state == integer) {
            printf("integer\n");
        } else if (current_state == floating_point) {
            printf("float\n");
        } else if (current_state == variable) {
            if (index < 11)
                printf("variable\n");
            else
                printf("string\n");
        }
    } while (str[index++] != '\0');
}

int main() {
    int input_times;
    scanf("%d", &input_times);
    for (int i = 0; i < input_times; i++) {
        detect_type();
    }
    return 0;
}
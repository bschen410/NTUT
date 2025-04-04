#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

longInt subtract(longInt a, longInt b);

longInt strToLongInt(char *str) {
    longInt output;
    output.repr = str;
    if (*str == '-') {
        output.isNegative = 1;
        output.repr++;
    } else
        output.isNegative = 0;
    output.digitArray = (int *)malloc(800);
    for (int index = 0; index < strlen(output.repr); index++)  // 10, 0~9
        output.digitArray[index] = output.repr[strlen(output.repr) - 1 - index] - '0';
    return output;
}

longInt add(longInt a, longInt b) {
    longInt output;
    if (a.isNegative && b.isNegative) {
        output.isNegative = 1;
    } else if (!a.isNegative && b.isNegative) {
        b.isNegative = 0;
        return subtract(a, b);
    } else if (a.isNegative && !b.isNegative) {
        a.isNegative = 0;
        return subtract(b, a);
    } else {
        output.isNegative = 0;
    }
    output.repr = (char *)malloc(201);
    output.digitArray = (int *)malloc(800);
    memset(output.digitArray, 0, 800);
    int carry = 0, maxDigit = strlen(a.repr) > strlen(b.repr) ? strlen(a.repr) : strlen(b.repr);
    for (int index = 0; index < maxDigit; index++) {
        if (index >= strlen(a.repr)) {
            output.digitArray[index] = (b.digitArray[index] + carry) % 10;
            carry = (b.digitArray[index] + carry) / 10;
        } else if (index >= strlen(b.repr)) {
            output.digitArray[index] = (a.digitArray[index] + carry) % 10;
            carry = (a.digitArray[index] + carry) / 10;
        } else {
            output.digitArray[index] = (a.digitArray[index] + b.digitArray[index] + carry) % 10;
            carry = (a.digitArray[index] + b.digitArray[index] + carry) / 10;
        }
    }
    if (carry) {
        maxDigit++;
        output.digitArray[maxDigit - 1] = carry;
    }
    for (int index = 0; index < maxDigit; index++) {
        output.repr[index] = output.digitArray[maxDigit - 1 - index] + '0';
    }
    output.repr[maxDigit] = '\0';
    return output;
}

longInt subtract(longInt a, longInt b) {// a=10, b=1000
    longInt output;
    if (!a.isNegative && b.isNegative) {
        b.isNegative = 0;
        return add(a, b);
    } else if (a.isNegative && !b.isNegative) {
        a.isNegative = 0;
        output = add(a, b);
        output.isNegative = 1;
        return output;
    } else if (a.isNegative && b.isNegative) {
        a.isNegative = 0;
        b.isNegative = 0;
        return subtract(b, a);
    }
    output.repr = (char *)malloc(201);
    output.digitArray = (int *)malloc(800);
    longInt large, small;
    if (strlen(a.repr) > strlen(b.repr)) {
        large = a;
        small = b;
        output.isNegative = 0;
    } else if (strlen(a.repr) < strlen(b.repr)) {
        large = b;
        small = a;
        output.isNegative = 1;
    } else {
        for (int i = 0; i < strlen(a.repr); i++) {
            if (a.repr[i] > b.repr[i]) {
                large = a;
                small = b;
                output.isNegative = 0;
                break;
            } else if (a.repr[i] < b.repr[i]) {
                large = b;
                small = a;
                output.isNegative = 1;
                break;
            } else if (i == strlen(a.repr)-1) {
                output.isNegative = 0;
                output.digitArray[0] = 0;
                output.repr[0] = '0';
                output.repr[1] = '\0';
                return output;
            }
        }
    }
    memset(output.digitArray, 0, 800);
    int maxDigit = strlen(large.repr);
    for (int index = 0; index < maxDigit; index++) {
        if (index < strlen(small.repr))
        output.digitArray[index] = large.digitArray[index] - small.digitArray[index];
        else
        output.digitArray[index] = large.digitArray[index];
    }
    for (int index = 0; index < maxDigit; index++) {
        if (output.digitArray[index] < 0) {
            output.digitArray[index] += 10;
            output.digitArray[index + 1]--;
        }
    }
    for (int i = 199; i >= 0; i--) {
        if (output.digitArray[i] != 0){
            maxDigit = i+1;
            break;
        }
    }
    for (int index = 0; index < maxDigit; index++) {
        output.repr[index] = output.digitArray[maxDigit - 1 - index] + '0';
    }
    output.repr[maxDigit] = '\0';
    return output;
}

longInt multiply(longInt a, longInt b) {
    longInt output;
    output.digitArray = (int *)malloc(800);
    output.repr = (char *)malloc(201);
    output.isNegative = a.isNegative ^ b.isNegative;
    memset(output.digitArray, 0, 800);
    for (int i = 0; i < strlen(a.repr); i++) {
        for (int j = 0; j < strlen(b.repr); j++) {
            output.digitArray[i + j] += a.digitArray[i] * b.digitArray[j];
        }
    }
    int carry = 0, temp = 0, maxDigit = strlen(a.repr) + strlen(b.repr) - 1;
    for (int index = 0; index < maxDigit; index++) {
        temp = (output.digitArray[index] + carry) % 10;
        carry = (output.digitArray[index] + carry) / 10;
        output.digitArray[index] = temp;
    }
    if (carry) {
        output.digitArray[maxDigit] = carry;
        maxDigit++;
    }
    for (int index = 0; index < maxDigit; index++) {
        output.repr[index] = output.digitArray[maxDigit - 1 - index] + '0';
    }
    output.repr[maxDigit] = '\0';
    return output;
}

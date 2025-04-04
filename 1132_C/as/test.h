#ifndef TEST_H
#define TEST_H

typedef struct {
    int isNegative;
    int *digitArray;
    char *repr;
} longInt;

longInt subtract(longInt a, longInt b);
longInt strToLongInt(char *str);
longInt add(longInt a, longInt b);
longInt subtract(longInt a, longInt b);
longInt multiply(longInt a, longInt b);


#endif
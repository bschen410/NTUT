#include <stdio.h>
#include <string.h>

#define GATEVALUE(Gate) int (*GateValue)()

typedef struct _Gate {
    int input1;
    int input2;
    GATEVALUE(Gate);
    // int (*GateValue)();
} Gate;

void CreateGate(Gate *obj, char *type, int input1, int input2);

int GateORValue(Gate *gate) {
    return gate->input1 | gate->input2;
}

int GateANDValue(Gate *gate) {
    return gate->input1 & gate->input2;
}

int GateNOTValue(Gate *gate) {
    // int x0 = gate->input1 & 1;
    // int x1 = (gate->input1 >> 1) & 1;
    // int x2 = (gate->input1 >> 2) & 1;
    // return (!x0 << 2) | (!x1 << 1) | (!x2 << 0);
    return 7 - gate->input1;
}

int GateBUFFERValue(Gate *gate) {
    return gate->input1;
}

int GateNANDValue(Gate *gate) {
    return 7 - (gate->input1 & gate->input2);
}

int GateNORValue(Gate *gate) {
    return 7 - (gate->input1 | gate->input2);
}

void CreateGate(Gate *obj, char *type, int input1, int input2) {
    obj->input1 = input1;
    obj->input2 = input2;

    if (!strcmp(type, "O"))
        obj->GateValue = GateORValue;
    else if (!strcmp(type, "A"))
        obj->GateValue = GateANDValue;
    else if (!strcmp(type, "N"))
        obj->GateValue = GateNOTValue;
    else if (!strcmp(type, "B"))
        obj->GateValue = GateBUFFERValue;
    else if (!strcmp(type, "NA"))
        obj->GateValue = GateNANDValue;
    else if (!strcmp(type, "NO"))
        obj->GateValue = GateNORValue;

    // return obj->GateValue(obj);
}

int decimalToBinary(int n) {
    int binary = 0, base = 1;

    while (n > 0) {
        int last_digit = n % 2;
        n /= 2;
        binary += last_digit * base;
        base *= 10;
    }

    return binary;
}

int main() {
    int x1, x2, x3;
    scanf("%d %d %d", &x1, &x2, &x3);
    char type1[5], type2[5], type3[5], type4[5], type5[5];
    scanf("%s %s %s %s %s", type1, type2, type3, type4, type5);
    Gate gate1, gate2, gate3, gate4, gate5;

    CreateGate(&gate1, type1, x1, x1);
    // printf("%d\n", gate1.GateValue(&gate1));
    // printf("%d\n", gate1.GATEVALUE(&gate1));
    CreateGate(&gate2, type2, x2, x2);
    // printf("%d\n", gate2.GateValue(&gate2));
    CreateGate(&gate3, type3, x3, x3);
    // printf("%d\n", gate3.GateValue(&gate3));
    CreateGate(&gate4, type4, gate1.GateValue(&gate1), gate2.GateValue(&gate2));
    // printf("%d\n", gate4.GateValue(&gate4));
    CreateGate(&gate5, type5, gate4.GateValue(&gate4), gate3.GateValue(&gate3));
    // printf("%d\n", gate5.GateValue(&gate5));

    // Gate testGate;
    // CreateGate(&testGate, "N", 1, 1);
    // printf("%d\n", testGate.GateValue(&testGate));

    printf("%03d\n", decimalToBinary(gate5.GateValue(&gate5)));

    return 0;
}

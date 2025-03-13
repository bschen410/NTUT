#include <limits.h>
#include <stdio.h>

typedef struct {
    int fee;
    int freeInCall;
    int freeOutCall;
    int freeTelCall;
    int freeInSMS;
    int freeOutSMS;
    double inCallPrize;
    double outCallPrize;
    double telCallPrize;
    double inSMSPrize;
    double outSMSPrize;
} Telecom;

Telecom charge[] = {
    {.fee = 183, .freeInCall = 500, .freeOutCall = 400, .freeTelCall = 300, .freeInSMS = 10, .freeOutSMS = 15, .inCallPrize = 0.08, .outCallPrize = 0.1393, .telCallPrize = 0.1349, .inSMSPrize = 1.1287, .outSMSPrize = 1.4803},
    {.fee = 383, .freeInCall = 600, .freeOutCall = 500, .freeTelCall = 400, .freeInSMS = 20, .freeOutSMS = 25, .inCallPrize = 0.07, .outCallPrize = 0.1304, .telCallPrize = 0.1217, .inSMSPrize = 1.1127, .outSMSPrize = 1.2458},
    {.fee = 983, .freeInCall = 700, .freeOutCall = 600, .freeTelCall = 500, .freeInSMS = 30, .freeOutSMS = 35, .inCallPrize = 0.06, .outCallPrize = 0.1087, .telCallPrize = 0.1018, .inSMSPrize = 0.9572, .outSMSPrize = 1.1243},
};

int inCall, outCall, telCall, inSMS, outSMS;

float computeCost(int index) {
    double cost = 0;
    if (inCall > charge[index].freeInCall)
        cost += (inCall - charge[index].freeInCall) * charge[index].inCallPrize;
    if (outCall > charge[index].freeOutCall)
        cost += (outCall - charge[index].freeOutCall) * charge[index].outCallPrize;
    if (telCall > charge[index].freeTelCall)
        cost += (telCall - charge[index].freeTelCall) * charge[index].telCallPrize;
    if (inSMS > charge[index].freeInSMS)
        cost += (inSMS - charge[index].freeInSMS) * charge[index].inSMSPrize;
    if (outSMS > charge[index].freeOutSMS)
        cost += (outSMS - charge[index].freeOutSMS) * charge[index].outSMSPrize;
    //
    if (cost >= charge[index].fee)
        return cost;
    else
        return charge[index].fee;
}

int main() {
    scanf("%d%d%d%d%d", &inCall, &outCall, &telCall, &inSMS, &outSMS);
    int i, bestPlan = charge[0].fee, bestCost = INT_MAX;
    for (i = 0; i < 3; i++) {
        int cost = (int)computeCost(i);
        if (cost < bestCost) {
            bestCost = cost;
            bestPlan = charge[i].fee;
        }
    }
    printf("%d\n%d", bestCost, bestPlan);
    return 0;
}

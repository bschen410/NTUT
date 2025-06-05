#include <stdio.h>
#include <limits.h>

#define SIZE 100

typedef struct {
    int machineID;
    int workHour;
} NewProcess;

typedef struct {
    int numOfProcess;
    NewProcess process[SIZE];
} NewWork;

int main() {
    int numOfMachine, numOfWork;
    scanf("%d %d", &numOfMachine, &numOfWork);
    NewWork work[numOfWork];
    for (int i = 0; i < numOfWork; i++) {
        int numOfProcess;
        scanf("%d", &numOfProcess);
        work[i].numOfProcess = numOfProcess;
        for (int j = 0; j < numOfProcess; j++)
            scanf("%d %d", &work[i].process[j].machineID, &work[i].process[j].workHour);
    }

    int machine[numOfMachine];
    int currentProcess[numOfWork];
    int currentTime = 0;
    memset(machine, 0, sizeof(machine));
    memset(currentProcess, 0, sizeof(currentProcess));

    while (1) {
        int earliestTime[numOfWork];
        memset(earliestTime, 0, sizeof(earliestTime));
        for (int i = 0; i < numOfWork; i++) {
            earliestTime[i] = max(machine[work[i].process[currentProcess[i]].machineID], earliestTime[i]);
        }
    }
    return 0;
}

#include <stdio.h>
#include <string.h>
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

int max(int a, int b) {
    return a > b ? a : b;
}

int main() {
    int numOfMachine, numOfWork;
    scanf("%d %d", &numOfMachine, &numOfWork);

    NewWork work[numOfWork];

    for (int i = 0; i < numOfWork; i++) {
        int numOfProcess;
        scanf("%d", &numOfProcess);
        work[i].numOfProcess = numOfProcess;
        for (int j = 0; j < numOfProcess; j++) {
            scanf("%d %d", &work[i].process[j].machineID, &work[i].process[j].workHour);
        }
    }

    int machineTime[10] = {0};      // 每台機器的可用時間 (最多10台機器)
    int currentProcess[10] = {0};   // 每個工作目前進行到哪道工序
    int finishTime[10] = {0};       // 每個工作的完成時間
    int finishedCount = 0;

    while (finishedCount < numOfWork) {
        int bestJob = -1;
        int bestFinishTime = INT_MAX;

        for (int i = 0; i < numOfWork; i++) {
            int p = currentProcess[i];
            if (p >= work[i].numOfProcess) continue; // 已完成的跳過

            int machineID = work[i].process[p].machineID;
            int timeNeeded = work[i].process[p].workHour;

            int prevTime = (p == 0) ? 0 : finishTime[i];
            int availableTime = max(machineTime[machineID], prevTime);
            int completeTime = availableTime + timeNeeded;

            // 選擇完成時間最早的，若相同則選工作編號小的
            if (completeTime < bestFinishTime ||
                (completeTime == bestFinishTime && i < bestJob)) {
                bestFinishTime = completeTime;
                bestJob = i;
            }
        }

        // 安排 bestJob 的目前這道工序
        int p = currentProcess[bestJob];
        int machineID = work[bestJob].process[p].machineID;
        int timeNeeded = work[bestJob].process[p].workHour;

        int prevTime = (p == 0) ? 0 : finishTime[bestJob];
        int startTime = max(machineTime[machineID], prevTime);
        int completeTime = startTime + timeNeeded;

        machineTime[machineID] = completeTime;
        finishTime[bestJob] = completeTime;
        currentProcess[bestJob]++;

        if (currentProcess[bestJob] == work[bestJob].numOfProcess)
            finishedCount++;
    }

    // 計算總完成時間
    int total = 0;
    for (int i = 0; i < numOfWork; i++)
        total += finishTime[i];

    printf("%d\n", total);

    return 0;
}

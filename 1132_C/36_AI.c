#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 105

// 定義工作節點的結構
typedef struct {
    int duration;   // 該工作所需時間
    int indegree;   // 有多少個前置工作（入度）
    int nextCount;  // 有多少個後續節點
    int next[MAX];  // 後續節點的索引列表
} Task;

Task tasks[MAX];
int finishTime[MAX];  // 每個節點完成的最早時間

// 拓撲排序來計算專案完成時間
int computeProjectTime(int nodeCount) {
    int queue[MAX], front = 0, rear = 0;

    // 初始化：把入度為0的節點放入queue
    for (int i = 1; i <= nodeCount; i++) {
        if (tasks[i].indegree == 0) {
            queue[rear++] = i;
            finishTime[i] = tasks[i].duration;
        }
    }

    int maxTime = 0;

    while (front < rear) {
        int current = queue[front++];

        for (int i = 0; i < tasks[current].nextCount; i++) {
            int next = tasks[current].next[i];

            // 更新下個任務的完成時間
            if (finishTime[next] < finishTime[current] + tasks[next].duration) {
                finishTime[next] = finishTime[current] + tasks[next].duration;
            }

            // 入度減1
            tasks[next].indegree--;

            if (tasks[next].indegree == 0) {
                queue[rear++] = next;
            }
        }

        // 記錄最大完成時間
        if (finishTime[current] > maxTime) {
            maxTime = finishTime[current];
        }
    }

    return maxTime;
}

int main() {
    int N;
    scanf("%d", &N);

    for (int project = 0; project < N; project++) {
        int M;
        scanf("%d", &M);

        // 初始化
        for (int i = 1; i <= M; i++) {
            tasks[i].indegree = 0;
            tasks[i].nextCount = 0;
            finishTime[i] = 0;
        }

        for (int i = 1; i <= M; i++) {
            int duration, K;
            scanf("%d %d", &duration, &K);
            tasks[i].duration = duration;

            for (int j = 0; j < K; j++) {
                int dependent;
                scanf("%d", &dependent);
                tasks[i].next[tasks[i].nextCount++] = dependent;
                tasks[dependent].indegree++;
            }
        }

        int result = computeProjectTime(M);
        printf("%d\n", result);
    }

    return 0;
}

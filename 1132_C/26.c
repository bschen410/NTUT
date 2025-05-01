#include <stdio.h>
#include <stdlib.h>

int stop, block1, block2;

void dfs(int n, int **map, int *visited, int current, int step, int *cost) {
    printf("step: %d | ", step);
    for (int i = 0; i < n; i++) printf("%d ", visited[i]);
    printf("current: %d\n", current);
    printf("\n");
    //
    if (step == stop - 1) {
        int ori1 = map[block1 - 1][block2 - 1];
        int ori2 = map[block2 - 1][block1 - 1];
        map[block1 - 1][block2 - 1] = -1;
        map[block2 - 1][block1 - 1] = -1;
        printf("- debug: block1 and block2 disconnected\n");
        dfs(n, map, visited, current, step + 1, cost);
        map[block1 - 1][block2 - 1] = ori1;
        map[block2 - 1][block1 - 1] = ori2;
        printf("- debug: block1 and block2 connected\n");
    }
    if (step == n - 1) {
        printf("- debug: reached end of path\n");
        return;
    }
    printf("- debug: start\n");
    for (int i = 0; i < n; i++) {
        int isVisited = 0;
        for (int j = 0; j < n; j++) {
            if (visited[j] == i) {
                isVisited = 1;
                break;
            }
        }
        if (map[current][i] > 0 && !isVisited) {
            printf("- debug: visit\n");
            visited[step + 1] = i;
            *cost += map[current][i];
            dfs(n, map, visited, i, step + 1, cost);
            *cost -= map[current][i];
            visited[step + 1] = -1;
        }
    }
}

int main() {
    int n, cost = 0;
    scanf("%d", &n);
    int **map = (int **)malloc(n * sizeof(int *));
    int *visited = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) map[i] = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n * n; i++) scanf("%d", &map[i / n][i % n]);
    //
    scanf("%d %d %d", &stop, &block1, &block2);
    for (int i = 0; i < n; i++) visited[i] = -1;
    visited[0] = 0;
    dfs(n, map, visited, 0, 0, &cost);
    // print visited
    printf("Final visited: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", visited[i] + 1);
    }
    printf("Cost: %d\n", cost);
    return 0;
}

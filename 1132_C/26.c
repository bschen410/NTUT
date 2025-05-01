#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *visited;
    int cost;
} PathInfo;

void dfs(int n, int **map, int *visited, int current, int step, int *cost, PathInfo *shortest) {
    if (step == n - 1) {
        if (*cost < shortest->cost) {
            for (int i = 0; i < n; i++) shortest->visited[i] = visited[i];
            // shortest->visited = visited;
            shortest->cost = *cost;
        }
        return;
    }
    for (int i = 0; i < n; i++) {
        int isVisited = 0;
        for (int j = 0; j < n; j++) {
            if (visited[j] == i) {
                isVisited = 1;
                break;
            }
        }
        if (map[current][i] > 0 && !isVisited) {
            // printf("- debug: visit\n", i);
            visited[step + 1] = i;
            *cost += map[current][i];
            dfs(n, map, visited, i, step + 1, cost, shortest);
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
    PathInfo shortest = {(int *)malloc(n * sizeof(int)), INT_MAX};
    //
    int stop, block1, block2;
    scanf("%d %d %d", &stop, &block1, &block2);
    for (int i = 0; i < n; i++) visited[i] = -1;
    visited[0] = 0;
    dfs(n, map, visited, 0, 0, &cost, &shortest);
    // printf("Shortest path: ");
    // for (int i = 0; i < n; i++) printf("%d ", shortest.visited[i] + 1);
    // printf("| Cost: %d\n", shortest.cost);
    map[block1 - 1][block2 - 1] = -1;
    map[block2 - 1][block1 - 1] = -1;
    for (int i = stop; i < n; i++) shortest.visited[i] = -1;
    PathInfo shortest2 = {(int *)malloc(n * sizeof(int)), INT_MAX};
    cost = 0;
    for (int i = 0; i < stop - 1; i++) {
        cost += map[shortest.visited[i]][shortest.visited[i + 1]];
    }
    dfs(n, map, shortest.visited, shortest.visited[stop - 1], stop - 1, &cost, &shortest2);
    // print visited
    for (int i = 0; i < n; i++) {
        printf("%d ", shortest2.visited[i] + 1);
    }
    printf("\n%d\n", shortest2.cost);
    return 0;
}

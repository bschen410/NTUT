#include <stdio.h>

typedef struct {
    char name;
    int point;
    int winTimes;
} Team;

void gameStart(Team *teams) {
    char team1, team2;
    scanf(" %c %c", &team1, &team2);
    int score1 = 0, score2 = 0;
    for (int i = 0; i < 4; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        score1 += a;
        score2 += b;
    }
    teams[team1 - 'A'].point += score1;
    teams[team2 - 'A'].point += score2;
    if (score1 > score2) {
        teams[team1 - 'A'].winTimes++;
    } else if (score2 > score1) {
        teams[team2 - 'A'].winTimes++;
    }
}

void printWinner(Team *teams) {
    char winner = 'A';
    int maxWinTimes = teams[0].winTimes;
    for (int i = 1; i < 3; i++) {
        if (teams[i].winTimes > maxWinTimes) {
            maxWinTimes = teams[i].winTimes;
            winner = teams[i].name;
        }
    }
    printf("%c %d\n", winner, teams[winner - 'A'].point);
}

int main() {
    Team teams[3] = {
        {'A', 0, 0},
        {'B', 0, 0},
        {'C', 0, 0}};
    int n;
    scanf("%d", &n);
    while (n--)
        gameStart(teams);
    printWinner(teams);
    // for (int i = 0; i < 3; i++) {
    //     printf("%c %d\n", teams[i].name, teams[i].point);
    // }
    return 0;
}

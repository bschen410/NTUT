#include <stdio.h>

typedef enum { OUT,
               BASE_HIT
} play_type_t;

typedef union {
    int base_hit;   // 1~4: number of bases
    char out_kind;  // 'F', 'S', 'G'
} play_result_t;

typedef struct {
    play_type_t type;
    play_result_t result;
} play_t;

typedef struct {
    int no;          // 擊球員的打擊次數
    play_t data[5];  // 擊球員的打擊結果
} basePlayer_t;

int main() {
    basePlayer_t player[9];
    for (int i = 0; i < 9; i++) {
        scanf("%d", &player[i].no);
        for (int j = 0; j < player[i].no; j++) {
            char input[10];
            scanf("%s", input);
            if (input[1] == 'O') {
                player[i].data[j].type = OUT;
                player[i].data[j].result.out_kind = input[0];
            } else {
                player[i].data[j].type = BASE_HIT;
                if (input[1] == 'R')
                    player[i].data[j].result.base_hit = 4;
                else
                    player[i].data[j].result.base_hit = input[0] - '0';
            }
        }
    }

    int t, hitter = -1, round = 0, out = 0;
    int score = 0, base[4] = {0};
    scanf("%d", &t);

    while (t) {
        hitter = (hitter + 1) % 9;

        if (player[hitter].data[round].type == BASE_HIT) {
            int hit = player[hitter].data[round].result.base_hit;
            if (hit == 4) {
                score++;
                for (int i = 0; i < 4; i++) {
                    if (base[i] > 0) {
                        base[i] = 0;
                        score++;
                    }
                }
            } else {
                for (int i = 3; i > 0; i--) {
                    if (base[i] > 0) {
                        base[i] = 0;
                        if (i + hit >= 4) score++;
                        else base[i + hit] = 1;
                    }
                }
                base[hit] = 1;
            }
        } else if (player[hitter].data[round].type == OUT) {
            out++;
            t--;
        }

        // printf("%d %d %d %d | ", hitter, round, out, score);
        // printf("%d %d %d %d\n", base[0], base[1], base[2], base[3]);

        if (out == 3) {
            out = 0;
            for (int i = 0; i < 4; i++) base[i] = 0;
        }
        if (hitter == 8) round++;
    }

    printf("%d\n", score);

    return 0;
}

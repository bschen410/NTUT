#include <stdio.h>
#include <string.h>

typedef enum scoreType_s { G,
                           GPA,
                           S
} scoreType_t;

typedef enum G_s { Aplus,
                   A,
                   Aduce,
                   Bplus,
                   B,
                   Bduce,
                   Cplus,
                   C,
                   Cduce,
                   F,
                   X
} G_t;

typedef enum GPA_s { b4dot3,
                     b4dot0,
                     b3dot7,
                     b3dot3,
                     b3dot0,
                     b2dot7,
                     b2dot3,
                     b2dot0,
                     b1dot7,
                     b1,
                     b0
} GPA_t;

typedef enum S_s { b90to100,
                   b85to89,
                   b80to84,
                   b77to79,
                   b73to76,
                   b70to72,
                   b67to69,
                   b63to66,
                   b60to62,
                   b1to59,
                   b0to0
} S_t;

typedef union student_s {
    int score;
    G_t G;
    GPA_t GPA;
    S_t S;
} student_t;

typedef struct studentInfo_s {
    char id[10];
    double ave_score;
} studentInfo_t;

char *scoreName[11] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "F", "X"};
char *GPAName[11] = {"4.3", "4.0", "3.7", "3.3", "3.0", "2.7", "2.3", "2.0", "1.7", "1", "0"};
char *SName[11] = {"90-100", "85-89", "80-84", "77-79", "73-76", "70-72", "67-69", "63-66", "60-62", "1-59", "0"};
int scoreList[11] = {95, 87, 82, 78, 75, 70, 68, 65, 60, 50, 0};

int main() {
    int m;
    scanf("%d", &m);
    scoreType_t scoreType[m];

    for (int i = 0; i < m; i++) {
        char input[10];
        scanf("%s", input);
        if (!strcmp(input, "G"))
            scoreType[i] = G;
        else if (!strcmp(input, "GPA"))
            scoreType[i] = GPA;
        else if (!strcmp(input, "S"))
            scoreType[i] = S;
    }

    int n;
    scanf("%d", &n);
    // student_t student[n];
    studentInfo_t studentInfo[n];

    for (int i = 0; i < n; i++) {
        char id[10];
        scanf("%s", id);
        strcpy(studentInfo[i].id, id);
        studentInfo[i].ave_score = 0;
        student_t student[m];
        for (int j = 0; j < m; j++) {
            char input[10];
            scanf("%s", input);
            if (scoreType[j] == G) {
                for (int k = 0; k < 11; k++)
                    if (!strcmp(input, scoreName[k])) {
                        student[j].G = k;
                        break;
                    }
                student[j].score = scoreList[student[j].G];
            } else if (scoreType[j] == GPA) {
                for (int k = 0; k < 11; k++)
                    if (!strcmp(input, GPAName[k])) {
                        student[j].GPA = k;
                        break;
                    }
                student[j].score = scoreList[student[j].GPA];
            } else if (scoreType[j] == S) {
                for (int k = 0; k < 11; k++)
                    if (!strcmp(input, SName[k])) {
                        student[j].S = k;
                        break;
                    }
                student[j].score = scoreList[student[j].S];
            }

            studentInfo[i].ave_score += student[j].score;
        }
    }

    // sort
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (studentInfo[j].ave_score > studentInfo[j + 1].ave_score) {
                studentInfo_t temp = studentInfo[j];
                studentInfo[j] = studentInfo[j + 1];
                studentInfo[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        studentInfo[i].ave_score /= m;
        printf("%s %d\n", studentInfo[i].id, (int)(studentInfo[i].ave_score));
    }
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定義教室結構
typedef struct {
    int id;
    int capacity;
} Classroom;

// 定義課程結構
typedef struct {
    int id;
    int students;
    int start;
    int end;
    int duration;
} Course;

// 定義最終排程結果的結構
typedef struct {
    int course_id;
    int room_id;
} Assignment;

// qsort 所需的比較函式：排序教室 (依容量由小到大)
int compare_classrooms(const void* a, const void* b) {
    Classroom* roomA = (Classroom*)a;
    Classroom* roomB = (Classroom*)b;
    return roomA->capacity - roomB->capacity;
}

// qsort 所需的比較函式：排序課程 (時長由長到短，ID 由大到小)
int compare_courses(const void* a, const void* b) {
    Course* courseA = (Course*)a;
    Course* courseB = (Course*)b;

    if (courseB->duration != courseA->duration) {
        return courseB->duration - courseA->duration;
    }
    return courseB->id - courseA->id;
}

// qsort 所需的比較函式：排序最終結果 (只依課程 ID 由小到大)
// 【此處為本次修正的重點】
int compare_assignments(const void* a, const void* b) {
    Assignment* assignA = (Assignment*)a;
    Assignment* assignB = (Assignment*)b;

    // 依照測試資料三的範例，輸出結果純粹以課程編號排序
    return assignA->course_id - assignB->course_id;
}

int main() {
    int M, N;
    scanf("%d %d", &M, &N);

    Classroom* rooms = (Classroom*)malloc(M * sizeof(Classroom));
    Course* courses = (Course*)malloc(N * sizeof(Course));

    for (int i = 0; i < M; i++) {
        scanf("%d %d", &rooms[i].id, &rooms[i].capacity);
    }

    for (int i = 0; i < N; i++) {
        scanf("%d %d %d %d", &courses[i].id, &courses[i].students, &courses[i].start, &courses[i].end);
        courses[i].duration = courses[i].end - courses[i].start;
    }

    int b;
    scanf("%d", &b);

    qsort(rooms, M, sizeof(Classroom), compare_classrooms);
    qsort(courses, N, sizeof(Course), compare_courses);

    int schedule[M][24];
    memset(schedule, 0, sizeof(schedule));

    Assignment* final_assignments = (Assignment*)malloc(N * sizeof(Assignment));
    int assignment_count = 0;
    long long total_hours = 0;
    int total_courses = 0;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            if ((b == 1 || b == 2) && courses[i].students > rooms[j].capacity) {
                continue;
            }

            int is_free = 1;
            for (int t = courses[i].start; t < courses[i].end; t++) {
                if (schedule[j][t] == 1) {
                    is_free = 0;
                    break;
                }
            }

            if (is_free) {
                for (int t = courses[i].start; t < courses[i].end; t++) {
                    schedule[j][t] = 1;
                }
                total_hours += courses[i].duration;
                total_courses++;

                if (b == 2) {
                    final_assignments[assignment_count].course_id = courses[i].id;
                    final_assignments[assignment_count].room_id = rooms[j].id;
                    assignment_count++;
                }
                break;
            }
        }
    }

    printf("max hours %lld\n", total_hours);
    printf("max courses %d\n", total_courses);

    if (b == 2) {
        qsort(final_assignments, assignment_count, sizeof(Assignment), compare_assignments);
        for (int i = 0; i < assignment_count; i++) {
            printf("%d %d\n", final_assignments[i].course_id, final_assignments[i].room_id);
        }
    }

    free(rooms);
    free(courses);
    free(final_assignments);

    return 0;
}
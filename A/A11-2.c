//
// Created by znwang on 2023/11/1.

//#pragma GCC optimize(3)

#include <stdio.h>

#define SUBJECTS 5
#define LEVELS 10
#define EXPAND 10
#define MAX 501

int level[LEVELS] = {0, 10, 15, 20, 25, 30, 35, 40, 45, 50};
int score[LEVELS + 1] = {0, 60, 65, 70, 75, 80, 85, 90, 95, 100, 101};

void generate_score(int i, int j, int k, int l, int m);

void print_result();

int record[MAX] = {0};

int main() {
    float gpa;
    scanf("%f", &gpa);
    int GPA = gpa * EXPAND;
    int sum = 5 * GPA;
    int i, j, k, l, m;

    for (i = 0; i < LEVELS; i++) {
        for (j = i; j < LEVELS; j++) {
            for (k = j; k < LEVELS; k++) {
                for (l = k; l < LEVELS; l++) {
                    for (m = l; m < LEVELS; m++) {
                        if (level[i] + level[j] + level[k] + level[l] + level[m] == sum) {
                            generate_score(i, j, k, l, m);
                        }
                    }
                }
            }
        }
    }
    print_result();
    return 0;
}

void generate_score(int i, int j, int k, int l, int m) {
    int min = score[i] + score[j] + score[k] + score[l] + score[m];
    int max = score[i + 1] + score[j + 1] + score[k + 1] + score[l + 1] + score[m + 1] - 5;

    for (; min <= max; min++) {
        record[min] = 1; // bitmap
    }
}

void print_result() {
    size_t i;

    for (i = 0; i < MAX; i++) {
        if (record[i] == 1) {
            printf ("%.1f ", i / 5.0);
        }
    }
}

//
// Created by znwang on 2023/11/1.

#pragma GCC optimize(3)
#include <stdio.h>

#define SUBJECTS 5
#define LEVELS 10
#define EXPAND 10
#define MAX 5000

int level[LEVELS] = {0, 10, 15, 20,25, 30, 35 ,40, 45, 50};
int score[LEVELS + 1] = {0, 60, 65, 70, 75, 80, 85, 90, 95, 100, -1};

void generate_ave_score(int i, int j, int k, int l, int m);
void print_result();
float record[MAX];
int main()
{
    float gpa;
    scanf("%f", &gpa);
    gpa *= EXPAND;
    int sum = (int)(5 * gpa);
    int i, j, k, l ,m;
    int cnt = 0;
    for (cnt = 0; cnt < MAX; cnt++) {
        record[cnt] = -1;
    }
    for(i = 0; i < LEVELS && level[i] <= (int)gpa; i++){
        for(j = i; j < LEVELS; j++){
            for(k = j; k < LEVELS; k++){
                for(l = k; l < LEVELS; l++){
                    for(m = l; m < LEVELS; m++){
                        if(level[i] + level[j] + level[k] + level[l] + level[m] == sum)
                            generate_ave_score(i, j, k, l, m);
                    }
                }
            }
        }
    }
    print_result();
    return 0;
}

void generate_ave_score(int i, int j, int k, int l, int m)
{
    int _i, _j, _k, _l, _m, cur = 0;
    float ave;
    //todo:this part is wrong
    for(_i = score[i]; _i == 100 || _i < score[i + 1];){
        for(_j = score[j]; _j == 100 || _j < score[j + 1];){
            for(_k = score[k]; _k == 100 || _k < score[k + 1];){
                for(_l = score[l]; _l == 100 || _l < score[l + 1];){
                    for(_m = score[m]; _m == 100 || _m < score[m + 1];){
                        ave = (float)(_i + _j + _k + _l + _m) / 5;
                        record[cur] = ave;
                        cur++;
                        if(_m != 100){
                            m++;
                        }else break;
                    }
                    if(_l != 100){
                        _l++;
                    }else break;
                }
                if(_k != 100){
                    _k++;
                }else break;
            }
            if(_j != 100){
                _j++;
            }else break;
        }
        if(_i != 100){
            _i++;
        }else break;
    }
}
void print_result()
{
    size_t i, j;
    for(i = 0; i < MAX - 1; i++){
        for(j = i + 1; j < MAX; j++){
            if(record[i] != -1 && record[j] != -1 && (record[j] - record[i]) < 0.00001){
                record[j] = -1;
            }
        }
    }
    for(i = 0; i < MAX; i++){
        if(record[i] != -1){
            printf("%.1f ", record[i]);
        }
    }
}

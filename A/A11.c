////
//// Created by znwang on 2023/11/1.
//#pragma GCC optimize(3,"Ofast","inline")
#include <stdio.h>
#define MAX 501

int score2gpa(int score);

int main(void)
{
    short table[MAX];
    float gpa;
    scanf("%f", &gpa);
    int GPA = (int)(gpa * 10);
    int a, b, c, d, e, i;
    for(i = 0; i < MAX; i++){
        table[i] = 0;
    }
    for(a = 0; a <= 100; a++){
        for(b = a; b <= 100; b++){
            for(c = b; c <= 100; c++){
                for(d = c; d <= 100; d++){
                    for(e = d; e <= 100; e++){
                        if(score2gpa(a) + score2gpa(b) + score2gpa(c) + score2gpa(d) + score2gpa(e) == GPA)
                            table[a + b + c + d + e] = 1;
                    }
                }
            }
        }
    }
    for(i = 0; i < MAX; i++){
        if(table[i] == 1)
        printf("%.1f ", i / 5.0);
    }
    return 0;
}

int score2gpa(int score)
{
    score /= 5;
    switch (score) {
        case 20:
            return 10;
        case 19:
            return 9;
        case 18:
            return 8;
        case 17:
            return 7;
        case 16:
            return 6;
        case 15:
            return 5;
        case 14:
            return 4;
        case 13:
            return 3;
        case 12:
            return 2;
        default:
            return 0;
    }
}


#pragma GCC optimize(3)
#include <stdio.h>

#define SUBJECTS 5
#define LEVELS 10
#define EXPAND 10
#define MAX 500

int level[LEVELS] = {0, 10, 15, 20,25, 30, 35 ,40, 45, 50};
int score[LEVELS + 1] = {0, 60, 65, 70, 75, 80, 85, 90, 95, 100, 101};

void generate_sum_score(int i, int j, int k, int l, int m);
void print_result();
int sum_record[MAX];
int main()
{
    float gpa;
    scanf("%f", &gpa);
    gpa *= EXPAND;
    int sum = (int)(5 * gpa);
    int i, j, k, l ,m;
    int cnt = 0;
    for (cnt = 0; cnt < MAX; cnt++) {
        sum_record[cnt] = -1;
    }
    for(i = 0; i < LEVELS && level[i] <= (int)gpa; i++){
        for(j = i; j < LEVELS; j++){
            for(k = j; k < LEVELS; k++){
                for(l = k; l < LEVELS; l++){
                    for(m = l; m < LEVELS; m++){
                        if(level[i] + level[j] + level[k] + level[l] + level[m] == sum)
                            generate_sum_score(i, j, k, l, m);
                    }
                }
            }
        }
    }
    print_result();
    return 0;
}

//void generate_sum_score(int i, int j, int k, int l, int m)
//{
//    int _i, _j, _k, _l, _m, cur = 0;
//    int sum;
////    for(_i = score[i + 1] - 1; _i >= score[i]; _i--){
////        for(_j = score[j + 1] - 1; _j >= score[j]; _j--){
////            for(_k = score[k + 1] - 1; _k >= score[k]; _k--){
////                for(_l = score[l + 1] - 1; _l >= score[l]; _l--){
////                    for(_m = score[i + 1] - 1; _m >= score[m]; _m--){
////                        sum = _i + _j + _k + _l + _m;
////                        sum_record[cur] = sum;
////                        cur++;
////                    }
////                }
////            }
////
////        }
////    }
//
//    for(_i = score[i]; _i == 100 || _i < score[i + 1];){
//        for(_j = score[j]; _j == 100 || _j < score[j + 1];){
//            for(_k = score[k]; _k == 100 || _k < score[k + 1];){
//                for(_l = score[l]; _l == 100 || _l < score[l + 1];){
//                    for(_m = score[m]; _m == 100 || _m < score[m + 1];){
//                        sum = _i + _j + _k + _l + _m;
//                        sum_record[cur] = sum;
//                        cur++;
//                        if(_m != 100 && m != 99){
//                            m++;
//                        }else break;
//                    }
//                    if(_l != 100 && _l != 99){
//                        _l++;
//                    }else break;
//                }
//                if(_k != 100 && _k != 99){
//                    _k++;
//                }else break;
//            }
//            if(_j != 100 && _j != 99){
//                _j++;
//            }else break;
//        }
//        if(_i != 100 && _i != 99){
//            _i++;
//        }else break;
//    }
//}
//
//void print_result()
//{
//    size_t i, j;
//    for(i = 0; i < MAX - 1; i++){
//        for(j = i + 1; j < MAX; j++){
//            if(sum_record[i] != -1 && sum_record[j] != -1 && sum_record[j] == sum_record[i]){
//                sum_record[j] = -1;
//            }
//        }
//    }
//    for(i = 0; i < MAX; i++){
//        float ave;
//        if(sum_record[i] != -1){
//            ave = (float )(sum_record[i]) / 5;
//            printf("%.1f ", ave);
//        }
//    }
//}

/*
 * A17
 * 分析一手5张牌的牌型，输出最好的牌型。
 * 牌有四种花色（Diamonds、Clubs、Hearts、Spades）和十三个等级（2、3、4、5、6、7、8、9、10、J、Q、K、A），A既可作为最大等级，也可作为最小等级。
 * 输入时，花色用首字母表示，等级用数字或字母表示（10用T表示）。若输入非法牌或重复牌则丢弃。若输入为0则结束程序。
 * 牌型从大到小有：
 * 同花顺 straight flush（同花色且等级顺序相连）
 * 四张 four of a kind（4张牌等级相同）
 * 葫芦 full house（3张牌等级相同，另2张牌也等级相同）
 * 同花 flush（5张牌花色相同）
 * 顺子 straight（5张牌等级顺序相连）
 * 三张 three of a kind（3张牌等级相同）
 * 两对 two pairs（存在两个对子）
 * 对子 pair（2张牌等级相同）
 * 其他
 */

#include <stdio.h>
#include <ctype.h>

#define true (1==1)
#define false !true

#define KINDS_OF_TYPES 4
#define KINDS_OF_GRADES 14
#define HAND_OF_CARDS 5

#define LITTLE_A 0
#define BIG_A 13

typedef int bool;
typedef struct Card {
    int type; // 0 ~ 3
    int grade; // 0 ~ 13
} CARD, *PCARD;

char card_types[] = {'D', 'C', 'H', 'S'};
char *card_types_display[] = {"Diamonds", "Clubs", "Hearts", "Spades"};

char card_grades[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
char *card_grades_display[] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};

int get_card_type(char);

int get_card_grade(char);

bool is_valid_type(char);

bool is_valid_grade(char);

bool is_duplicated_card(PCARD, int, CARD);

void sort_cards(PCARD);

void to_little_a_sort_cards(PCARD);

void to_big_a_sort_cards(PCARD);

void analyze_print_cards(PCARD);

// 1 同花顺 straight flush（同花色且等级顺序相连）
bool is_straight_flush(PCARD);

// 2 四张 four of a kind（4张牌等级相同）
bool is_four_of_a_kind(PCARD);

// 3 葫芦 full house（3张牌等级相同，另2张牌也等级相同）
bool is_full_house(PCARD);

// 4 同花 flush（5张牌花色相同）
bool is_flush(PCARD);

// 5 顺子 straight（5张牌等级顺序相连）
bool is_straight(PCARD);

// 6 三张 three of a kind（3张牌等级相同）
bool is_three_of_a_kind(PCARD);

// 7 两对 two pairs（存在两个对子）
bool is_two_pairs(PCARD);

// 8 对子 pair（2张牌等级相同）
bool is_pair(PCARD);

// Internal functions
bool check_straight_flush(PCARD);
bool check_straight(PCARD);

/*
 * Test data
 * 1.
 * D2 D3 D4 D5 D6
 * D2 D3 D4 D5 DA
 * DT DJ DQ DK DA
 * 2.
 * D9 C9 H9 S9 DA
 * 3.
 * D9 C9 H9 SA DA
 * 4.
 * D3 DJ DQ DK DA
 * 5.
 * D2 C3 H4 S5 D6
 * D2 C3 H4 S5 DA
 * DT CJ HQ SK DA
 * 6.
 * D9 C9 H9 ST DA
 * 7.
 * D9 C9 HT SA DA
 * 8.
 * D9 C9 H2 ST DA
 * 9.
 * D8 C9 H2 ST DA
 * 10.
 * A8 DH BO D8 C9 H2 ST DA
 */

int main() {

    CARD cards[HAND_OF_CARDS];
    int count = 0;

    while (true) {
        char type;
        char grade;

        char ch = getchar();

        if (EOF == ch || '0' == ch) {
            if (HAND_OF_CARDS == count) {
                analyze_print_cards(cards);
                count = 0;
            }
            break;
        }

        if (isalpha(ch) == false) {
            continue;
        }
        type = toupper(ch);
        ch = getchar();
        grade = toupper(ch);

        if (is_valid_type(type) && is_valid_grade(grade) && count < HAND_OF_CARDS) {
            CARD card = {get_card_type(type), get_card_grade(grade)};
            if (is_duplicated_card(cards, count, card) == false) {
                cards[count++] = card;
            }
        }
    }

    return 0;
}


int get_card_type(char type) {
    int i;
    for (i = 0; i < KINDS_OF_TYPES; i++) {
        if (type == card_types[i]) {
            return i;
        }
    }
    return i;
}

int get_card_grade(char grade) {
    int i;
    for (i = 1; i < KINDS_OF_GRADES; i++) {
        if (grade == card_grades[i]) {
            return i;
        }
    }
    return i;
}

bool is_valid_type(char type) {
    int i;
    for (i = 0; i < KINDS_OF_TYPES; i++) {
        if (type == card_types[i]) {
            return true;
        }
    }
    return false;
}

bool is_valid_grade(char grade) {
    int i;
    for (i = 1; i < KINDS_OF_GRADES; i++) {
        if (grade == card_grades[i]) {
            return true;
        }
    }
    return false;
}

bool is_duplicated_card(PCARD pCards, int size, CARD card) {
    int i;
    for (i = 0; i < size; i++) {
        if (card.type == pCards[i].type && card.grade == pCards[i].grade) {
            return true;
        }
    }
    return false;
}

/*
 * Select sort
 * */
void sort_cards(PCARD pCards) {
    int i, j, k;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        k = i;
        for (j = i + 1; j < HAND_OF_CARDS; j++) {
            if (pCards[k].grade > pCards[j].grade) {
                k = j;
            }
        }
        if (i < k) {
            CARD card = pCards[i];
            pCards[i] = pCards[k];
            pCards[k] = card;
        }
    }
}

void to_little_a_sort_cards(PCARD pCards) {
    bool flag = false;
    int i;
    for (i = 0; i < HAND_OF_CARDS; i++) {
        if (BIG_A == pCards[i].grade) {
            pCards[i].grade = LITTLE_A;
            flag = true;
        }
    }

    if (true == flag) {
        sort_cards(pCards);
    }
}

void to_big_a_sort_cards(PCARD pCards) {
    bool flag = false;
    int i;
    for (i = 0; i < HAND_OF_CARDS; i++) {
        if (LITTLE_A == pCards[i].grade) {
            pCards[i].grade = BIG_A;
            flag = true;
        }
    }

    if (true == flag) {
        sort_cards(pCards);
    }
}

void analyze_print_cards(PCARD pCards) {
    int i;
    bool flag = false;

    sort_cards(pCards);

    if (is_straight_flush(pCards)) {
        printf("%s", "Straight flush:");
    } else if (is_four_of_a_kind(pCards)) {
        printf("%s", "Four of a kind:");
    } else if (is_full_house(pCards)) {
        printf("%s", "Full house:");
    } else if (is_flush(pCards)) {
        printf("%s", "Flush:");
    } else if (is_straight(pCards)) {
        printf("%s", "Straight:");
    } else if (is_three_of_a_kind(pCards)) {
        printf("%s", "Three of a kind:");
    } else if (is_two_pairs(pCards)) {
        printf("%s", "Two pairs:");
    } else if (is_pair(pCards)) {
        printf("%s", "Pair:");
    } else {
        printf("%s", "Other:");
    }

    for (i = 0; i < HAND_OF_CARDS; i++) {
        printf(" %c%s", card_types[pCards[i].type], card_grades_display[pCards[i].grade]);
    }
    printf("\n");
}

bool is_straight_flush(PCARD pCards) {
    int i;
    bool flag = check_straight_flush(pCards);

    if (false == flag) {
        to_little_a_sort_cards(pCards);
        flag = check_straight_flush(pCards);
        to_big_a_sort_cards(pCards);
    }

    return flag;
}

bool check_straight_flush(PCARD pCards) {
    int i;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].type != pCards[i + 1].type || pCards[i].grade != (pCards[i + 1].grade - 1)) {
            return false;
        }
    }

    return true;
}

bool is_four_of_a_kind(PCARD pCards) {
    int i, count = 1;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].grade == pCards[i + 1].grade) {
            count++;
            if (4 == count) {
                return true;
            }
        } else {
            count = 1;
        }
    }
    return false;
}

bool is_full_house(PCARD pCards) {
    if ((pCards[0].grade == pCards[1].grade && pCards[0].grade == pCards[2].grade &&
         pCards[3].grade == pCards[4].grade) ||
        (pCards[0].grade == pCards[1].grade && pCards[2].grade == pCards[3].grade &&
         pCards[2].grade == pCards[4].grade)) {
        return true;
    }
    return false;
}

bool is_flush(PCARD pCards) {
    int i;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].type != pCards[i + 1].type) {
            return false;
        }
    }
    return true;
}

bool is_straight(PCARD pCards) {
    int i;
    bool flag = check_straight(pCards);

    if (false == flag) {
        to_little_a_sort_cards(pCards);
        flag = check_straight(pCards);
        to_big_a_sort_cards(pCards);
    }

    return flag;
}

bool check_straight(PCARD pCards) {
    int i;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].grade != (pCards[i + 1].grade - 1)) {
            return false;
        }
    }
    return true;
}

bool is_three_of_a_kind(PCARD pCards) {
    int i;
    for (i = 0; i < HAND_OF_CARDS - 2; i++) {
        if (pCards[i].grade == pCards[i + 1].grade && pCards[i].grade == pCards[i + 2].grade) {
            return true;
        }
    }
    return false;
}

bool is_two_pairs(PCARD pCards) {
    int i, count = 0;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].grade == pCards[i + 1].grade) {
            count++;
            if (2 == count) {
                return true;
            }
        }
    }
    return false;
}

bool is_pair(PCARD pCards) {
    int i, count = 0;
    for (i = 0; i < HAND_OF_CARDS - 1; i++) {
        if (pCards[i].grade == pCards[i + 1].grade) {
            count++;
            if (1 == count) {
                return true;
            }
        }
    }
    return false;
}

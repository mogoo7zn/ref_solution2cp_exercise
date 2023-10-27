#include <stdio.h>
#define TRUE (1==1)
#define FALSE !TRUE
#define WIDTH 3
#define ROWS_OF_CALENDAR 13
#define COLUMNS_OF_CALENDAR 28

int isLeapYear(int);
int firstDayOfMonth(int, int);
void printDay2Calendar(int, int);
void printNum2Calendar(int number, int row, int column);
void printCalendar(int month);

//how to make your output more agreeable


/*notation: when a string is printed in C, a "\0" is always added in the end automatically, so the number of column
should add one. moreover, it is correct if you manually add a "\0" in the end of each row*/
char gCalendar[ROWS_OF_CALENDAR][COLUMNS_OF_CALENDAR] = {
        "Sun Mon Tue Wed Thu Fri Sat\0",
        "                           \0",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           ",
        "                           "
};

//note:Month is used in many functions, so it is declared outside
int Month[13] = {0, 31, 28, 31, 30, 31, 30,
                 31, 31, 30, 31, 30, 31};

int main()
{
    /*print first line*/
    int judge, year, month, first_day;
    scanf("%d%d", &year, &month);

    //get to know the first day of the month
    judge = isLeapYear(year);
    if(judge == TRUE)
    {
        Month[2] = 29;
    }
    first_day = firstDayOfMonth(year, month);
    printDay2Calendar(month, first_day);
    printCalendar(month);
    return 0;
}

int isLeapYear(int year)
{
    if((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
    {
        return TRUE;
    }else
    {
        return FALSE;
    }
}

int firstDayOfMonth(int year, int monthInYear)
{
    //deviation = day of the first day in month
    int totalDay, i, deviation;
    totalDay = (year - 1) * 365 + (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;
    for(i = 0; i < monthInYear; i++)
    {
        totalDay += Month[i];
    }
    /*There might be some small stories behind 10, because a pope wiped off 10 days in history*/
    deviation = ((totalDay) % 7 + 1) % 7;
    return deviation;
}

void printDay2Calendar(int month, int first_day)
{
    //generate days
    int daysInMonth = Month[month];
    int row;
    int dayOfWeek, weekOfMonth;

    //essence: use d to determine dayInWeek and row, two birds with one stone
    for(int d = 1; d <=daysInMonth; d++)
    {
        dayOfWeek = (d + first_day - 1) % 7;
        weekOfMonth = (d + first_day -1) / 7 + 1;
        row = 2 * weekOfMonth;
        if ( d < 10)
        {
            gCalendar[row][(WIDTH + 1) * dayOfWeek + 1] = d + '0';
        }else{
            gCalendar[row][(WIDTH + 1) * dayOfWeek] = d / 10 + '0';
            gCalendar[row][(WIDTH + 1) * dayOfWeek + 1] = d % 10 + '0';
        }
    }
}

/*this function perform the tasks of shooting pixels of char(number) in the background
 * for the first task, we should create a mould for every number we want to print
 * next, with the existing base of days being print on the calendar, there is a judgement to be
 * done before actually shooting those pixels onto the canva
 * moreover, the location of the numbers are ascertained by pointer, namely,
 * three dimensions, one targets its location in num[], which means the number
 * you want to print. the other two dimensions represent the rows and columns
 * of the numbers we want to print*/
void printNum2Calendar(int number, int row, int column)
{
#define ROWS 5
#define COLUMNS 4

    char *zero[ROWS] = {
            "####\0",
            "#  #\0",
            "#  #\0",
            "#  #\0",
            "####\0"
    };
    char *one[ROWS] = {
            "   #\0",
            "   #\0",
            "   #\0",
            "   #\0",
            "   #\0"
    };
    char *two[ROWS] = {
            "####\0",
            "   #\0",
            "####\0",
            "#   \0",
            "####\0"
    };
    char *three[ROWS] = {
            "####\0",
            "   #\0",
            "####\0",
            "   #\0",
            "####\0"
    };
    char *four[ROWS] = {
            "#  #\0",
            "#  #\0",
            "####\0",
            "   #\0",
            "   #\0"
    };
    char *five[ROWS] = {
            "####\0",
            "#   \0",
            "####\0",
            "   #\0",
            "####\0"
    };
    char *six[ROWS] = {
            "####\0",
            "#   \0",
            "####\0",
            "#  #\0",
            "####\0"
    };
    char *seven[ROWS] = {
            "####\0",
            "   #\0",
            "   #\0",
            "   #\0",
            "   #\0"
    };
    char *eight[ROWS] = {
            "####\0",
            "#  #\0",
            "####\0",
            "#  #\0",
            "####\0"
    };
    char *nine[ROWS] = {
            "####\0",
            "#  #\0",
            "####\0",
            "   #\0",
            "####\0"
    };

    char **num[] = {zero, one, two, three, four, five, six, seven, eight, nine};
    int i, j;
    for(i = 0; i < ROWS; i++)
    {
        //it shan't be ROWS, since \0
        for(j = 0; j < COLUMNS; j++)
        {
            if(gCalendar[row + i][column + j] == ' ' && num[number][i][j] != ' ')
            {
                gCalendar[row + i][column + j] = num[number][i][j];
            }
        }
    }
}

void printCalendar(int month)
{
    //note: use /10 and %10 to ascertain the first and second place of the number
    printNum2Calendar(month / 10, 3, 7);
    printNum2Calendar(month % 10, 3, 15);

    int i;
    for(i = 0; i < ROWS_OF_CALENDAR; i++)
    {
        printf("%s\n", gCalendar[i]);
//        for(j = 0; j < COLUMNS_OF_CALENDAR; j++)
//        {
//            printf("%c", gCalendar[i][j]);
//        }
//        printf("\n");
    }
}

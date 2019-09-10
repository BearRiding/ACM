#include <stdio.h>

bool is_run(int year) {
    if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        return true;
    else
        return false;
}

int ym[13][2] = {
    {0, 0},   {31, 31}, {28, 29}, {31, 31}, {30, 30}, {31, 31}, {30, 30},
    {31, 31}, {31, 31}, {30, 30}, {31, 31}, {30, 30}, {31, 31},
};

int main() {
    int time[2];
    //    for(int *p = time; p < time + 1; p++){
    //        scanf("%d", p);
    //    }
    time[0] = 20171102;
    time[1] = 20200505;

    printf("%d  %d\n", time[0], time[1]);

    if (time[0] > time[1]) {
        int temp = time[1];
        time[1] = time[0];
        time[0] = temp;
    }

    int year, month, day;
    int year2;

    year2 = time[1] / 10000;

    year = time[0] / 10000;
    month = (time[0] / 100) % 100;
    day = time[0] % 100;
    printf("%d  %d  %d\n", year, month, day);

    int count = 1;

    while (year2 - year > 1) {
        if (is_run(year) && month < 3) {
            count += 366;
        } else {
            count += 365;
        }
        year++;
    }

    int isRun = is_run(year) ? 1 : 0;

    while (year * 10000 + month * 100 + day < time[1]) {
        day++;
        if (day > ym[month][isRun]) {
            day = 1;
            month++;
        }
        if (month > 12) {
            year++;
            month = 1;
            isRun = is_run(year) ? 1 : 0;
        }
        count++;
    }
    printf("%d\n", count);

    return 0;
}
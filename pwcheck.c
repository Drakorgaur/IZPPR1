#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>
#include <setjmp.h>
char passwords[2049][101];
int pass_counter;
bool firstLevel(char *p);
bool secondLevel(char *p);
bool thirdLevel(char *p);
bool fourthLevel(char *p);
bool firstSubLevel(char *p);
bool secondSubLevel(char *p);
bool thirdSubLevel(char *p);
bool fourthSubLevel(char *p);
bool compare(char* a, char* b);
void statistic(char* str);
int st_uniq = 0;
char ch_st_uniq[255] = "";
int st_min  = 101;
int st_max  = 0;
int divis = 0;
double st_avg = 0;
int recursion(int argc, char* argv[]);
int PARAM;
int LEVEL;
jmp_buf buf, err;

int main(int argc, char* argv[])
{
    int err1 = 0, counter = 0;
    err1 = setjmp(buf);
    if (err1 == 1) {
        printf("ERROR\n");
        printf("Look usage");
        longjmp(err, 2);
    }
    typedef bool (* Function) (char* pointer);
    Function security_level_checker[] = {&firstLevel, &secondLevel, &thirdLevel, &fourthLevel};

    char* key[] = {"-p", "-l"};
    for (int i = 1; i < argc; i++) {
        for(int sub_i = 0; sub_i < 2; sub_i++) {
            if (compare(argv[i], key[sub_i])) {
                if (sub_i == 0) {
                    PARAM = atoi(argv[i+1]);
                    if (!(0 < atoi(argv[i+1]) && atoi(argv[i+1]) <= 4)) {
                        printf("PARAM ");
                        longjmp(buf, 1);
                    }
                }
                if (sub_i == 1) {
                    LEVEL = atoi(argv[i+1]);
                    if (!(0 < atoi(argv[i+1]) && atoi(argv[i+1]) <= 4)) {
                        printf("LEVEL ");
                        longjmp(buf, 1);
                    }
                }
                break;
            }
            else {
                counter++;
                if (counter == argc + 1) {
                    PARAM = atoi(argv[2]);
                    LEVEL = atoi(argv[1]);
                }
            }
        }
    }

    char *stat = "--stats";
    bool stat_b = false;
    for (int i = 1; i < argc; i++) {
        if (compare(argv[i], stat)) {
            stat_b = true;
        }
    }
    {
    printf("\nLEVEL arg - %d\n", LEVEL);
    printf("PARAM arg - %d\n", PARAM);
    }
    char pass[101];
    char* pch;
    int sec_lvl = 0;
    counter = 0;
    scanf("%100s", pass);
    pch = pass;
    for (int level = 0; level < 4; level++)
    {
        if (security_level_checker[level](pch)) {
            printf("Security level %d: success\n", level + 1);
            sec_lvl++;
        } else
        {
            printf("Security level %d: fail\n\n", level + 1);
            break;
        }
    }
    if (sec_lvl >= LEVEL) {
        int cur = 0;
        for (cur = 0; pass[cur]; ++cur) {
            passwords[pass_counter][cur] = pass[cur];
        }
        pass_counter++;
    }
    printf("Final security level is: %d\n", sec_lvl);
    if (stat_b) {
        statistic(pass);
    }
    return recursion(argc, argv);

    setjmp(err);
    return 0;
}

int recursion(int argc, char* argv[])
{
    return main(argc, argv);
}

bool compare(char* a, char* b)
{
    while (*a != '\0' || *b != '\0') {
        if (*a == *b) {
            a++;
            b++;
        }
        else if ((*a == '\0' && *b != '\0')
                 || (*a != '\0' && *b == '\0')
                 || *a != *b) {
            return false;
        }
    }
    return true;
}

bool firstLevel(char* pointer)
{
    bool status[2] = {false, false};
    for (int i = 0;pointer[i]; i++) {
        if (status[0] == false && (97 <= pointer[i] && pointer[i] <= 122)) { status[0] = true; }
        if (status[1] == false && (65 <= pointer[i] && pointer[i] <= 90))  { status[1] = true; }
        if (status[0] == true && status[1] == true) { return true; }
    }
    return false;
}

bool secondLevel(char* pointer)
{
    int sub_sec_lvl = 0;
    typedef bool (* Function) (char* pointer);
    Function security_sublevel_checker[] = {&firstSubLevel, &secondSubLevel, &thirdSubLevel, &fourthSubLevel};

    for(int sub_level = 0; sub_level < 4; sub_level++) {
        if (security_sublevel_checker[sub_level](pointer)) { sub_sec_lvl++;}
    }
    if (sub_sec_lvl >= PARAM) { return true; }
    return false;
}

bool firstSubLevel(char* pointer)
{
    for (int i = 0; pointer[i]; i++) {
        if (97 <= pointer[i] && pointer[i] <= 122) { return true; }
    }
    return false;
}
bool secondSubLevel(char* pointer)
{
    for (int i = 0; pointer[i]; i++) {
        if (65 <= pointer[i] && pointer[i] <= 90) { return true; }
    }
    return false;
}
bool thirdSubLevel(char* pointer)
{
    for (int i = 0; pointer[i]; i++) {
        if (48 <= pointer[i] && pointer[i] <= 57) { return true; }
    }
    return false;
}
bool fourthSubLevel(char* pointer)
{
    for (int i = 0; pointer[i]; i++) {
        if (32 <= pointer[i] && pointer[i] <= 47 || pointer[i] >= 58 && pointer[i] <= 64 || pointer[i] >= 91 &&
        pointer[i] <= 96 || pointer[i] >= 123 && pointer[i] <= 126) { return true; }
    }
    return false;
}

bool thirdLevel(char* pointer)
{
    char letter[PARAM];
    int counter = 1;
    int i = 0;
    for (int z = 0; pointer[z]; z++) {
        letter[i] = pointer[i];
        i++;
        if (letter[i-1] == pointer[i])  {
            letter[i] = pointer[i];
            counter++;
            if (counter == PARAM) {
                return false;
            }
            continue;
        } else {
            counter = 1;
            memset(letter,0, PARAM);
        }
    }
    return true;
}
bool fourthLevel(char* pointer)
{
    int size = 0;
    while (pointer[size] != '\0') {
        size++;
    }

    char substr[PARAM + 1];
    char substr_temp[PARAM + 1];

    int cur = 0;
    for (int i = 0; i < size - PARAM; i++ ) {            // start loop to get substrings
        int temp_cur = cur;
        for(int z = temp_cur; z < PARAM + temp_cur; z++) {           // get substring that program will search for
            substr[z - temp_cur] = pointer[z];
        }
        for (int z = 0; z <= size - PARAM; z++) {        // start loop to get other substrings
            if (z == cur) { z++; }                              // exclude same substring as SUBSTR
            for(int sub_z = z; sub_z < PARAM + z; sub_z++) {     // get first substring
                substr_temp[sub_z - z] = pointer[sub_z];
            }
            int counter = 0;
            for (int d = 0; d < PARAM; d++) {                        // compare substrings
                if (substr[d] == substr_temp[d]) {
                    counter++;
                    if (counter == PARAM) {
                        return false;
                    }
                    continue;
                } else {
                    break;
                }
            }
        }
        cur++;
        memset(substr,0, PARAM);
        memset(substr_temp,0, PARAM);
    }
    return true;
}

void statistic(char* str)
{
    int uniq_size = 0;
    while (str[uniq_size] != '\0') {
        uniq_size++;
    }
    divis++;
    st_avg = (st_avg * (divis-1)+ uniq_size) / divis;
    uniq_size = 0;
    while (ch_st_uniq[uniq_size] != '\0') {
        uniq_size++;
    }
    int i;
    for (i = 0; str[i]; i++) {
        bool uniq = true;
        for(int sub_i = 0; sub_i <= uniq_size; sub_i++) {
            while (ch_st_uniq[uniq_size] != '\0') {
                uniq_size++;
            }
            if (str[i] == ch_st_uniq[sub_i]) { uniq = false; break;}
        }
        if (uniq) {
            ch_st_uniq[uniq_size] = str[i]; st_uniq++;
        }
    }
    if (st_min > i) { st_min = i; }
    if (st_max < i) { st_max = i; }
    for (int i = 0; i < pass_counter; i++) {
        printf("%s\n", passwords[i]);
    }
    printf("\n--------STATISTIC--------\n");
    printf("All uniq values: %s\n", ch_st_uniq);
    printf("Uniq chars: %d\n", st_uniq);
    printf("Min  chars: %d\n", st_min);
    printf("Max  chars: %d\n", st_max);
    printf("AVG  chars: %f\n", st_avg);
    printf("\n-------------------------\n");
}

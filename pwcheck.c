//
// Hello world, Let the Force lead you, while checking project.
//

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <setjmp.h>
typedef unsigned short bool;
#define true 1
#define false 0
bool firstLevel(char *p);
bool secondLevel(char *p);
bool thirdLevel(char *p);
bool fourthLevel(char *p);
bool firstSubLevel(char *p);
bool secondSubLevel(char *p);
bool thirdSubLevel(char *p);
bool fourthSubLevel(char *p);
bool compare(char* a, char* b);
void statistic(char* str, char (*passwords)[101], const int* pass_counter, int* divis, double* st_avg, char* ch_st_uniq,
               int* st_min, int* st_max, int* st_uniq);
int PARAM;
int LEVEL;
jmp_buf buf;

bool checkIfKeysExist(int argc, char** argv) {
    int counter = 0;

    char* key[] = {"-p", "-l"};
    for (int i = 1; i < argc; i++) {
        for(int sub_i = 0; sub_i < 2; sub_i++) {
            if (compare(argv[i], key[sub_i])) {
                if (sub_i == 0) {
                    PARAM = atoi(argv[i+1]);
                    if (!(0 < atoi(argv[i+1]) && atoi(argv[i+1]) <= 4)) {
                        printf("PARAM ERROR");
                        longjmp(buf, 1);
                    }
                }
                if (sub_i == 1) {
                    LEVEL = atoi(argv[i+1]);
                    if (!(0 < atoi(argv[i+1]) && atoi(argv[i+1]) <= 4)) {
                        printf("LEVEL ERROR");
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
}
bool checkIfStatisticKeyExists(int argc, char** argv) {

    char *stat = "--stats";

    printf("\nLEVEL arg - %d\n", LEVEL);
    printf("PARAM arg - %d\n", PARAM);

    for (int i = 1; i < argc; i++) {
        if (compare(argv[i], stat)) {
            return true;
        }
    }
    return false;
}
void checkSecurityLevel(char* pass, char (*passwords)[101], int* pass_counter) {
/* ---Setting up function pointer--- */
    typedef bool (* Function) (char* pointer);
    Function security_level_checker[] = {&firstLevel, &secondLevel, &thirdLevel, &fourthLevel};

    int sec_lvl = 0;

    for (int level = 0; level < 4; level++)
    {
        if (security_level_checker[level](pass)) {
            printf("Security level %d: success\n", level + 1);
            sec_lvl++;
        } else
        {
            printf("Security level %d: fail\n\n", level + 1);
            break;
        }
    }
    if (sec_lvl >= LEVEL) {
        passwords[*pass_counter];
        pass_counter++;
    }
    printf("Final security level is: %d\n", sec_lvl);
}

int main(int argc, char* argv[]) {
//  variables ----------------------
    char passwords[2049][101];
    char (*p_passwords)[101] = passwords;
    int pass_counter = 0;
    int st_uniq = 0;
    char ch_st_uniq[1025] = "";
    int st_min = 101;
    int st_max = 0;
    int divis = 1;
    double st_avg = 0;
    int* p_pass_counter = &pass_counter, *p_st_uniq = &st_uniq, *p_st_max = &st_max, *p_st_min = &st_min;
    int *p_divis = &divis;
    char *p_ch_st_uniq = ch_st_uniq;
    double *p_st_avg = &st_avg;

                                            /* ------ Looking for keys -------- */
    checkIfKeysExist(argc, argv);
                                            /* ------ Looking for stats ------- */
    bool stats = checkIfStatisticKeyExists(argc, argv);
                                            /* ---------- Check EOF ----------- */
    char pass[101];
    while (true) {
        fgets(pass, sizeof pass, stdin);
        if (!feof(stdin)) {
            printf(">>>>\t%s", pass);
                                            /* -------- Check Security -------- */
            checkSecurityLevel(pass, p_passwords, p_pass_counter);
                                            /* -------- Stats OutPut ---------- */
            if (stats) { statistic(pass, p_passwords, p_pass_counter, p_divis, p_st_avg, p_ch_st_uniq,
                                   p_st_min, p_st_max, p_st_uniq); }
                                            /* ---------- Recursion ----------- */
        } else { break; }
    }
                                            /* -------------- Exit ------------- */
    setjmp(buf);
    printf("Exit...");
    return 0;
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
bool thirdLevel(char* pointer)
{
    char buff = pointer[0];
    int  counter = 1;
    for (int i = 0; pointer[i]; i++) {
        buff = pointer[i];
        if (pointer[i] == pointer[i + 1]) {
            if (pointer[i] == buff) {
                counter++;
                if (counter >= PARAM) {
                    return false;
                }
            }
        } else {
            buff = pointer[i+1];
            counter = 1;
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

void statistic(char* str, char (*passwords)[101], const int* pass_counter, int* divis, double* st_avg, char* ch_st_uniq,
               int* st_min, int* st_max, int* st_uniq)
{
                                                                                /* -- Get length of Uniq chars -- */
    int uniq_size = 0;
    while (str[uniq_size] != '\0' && str[uniq_size] != '\n') {
        uniq_size++;
    }
    /* ------------------ */
                                                                                /* --------- Get Average --------- */
    *st_avg = ((*st_avg) * ((*divis)-1) + uniq_size) / (*divis);
    (*divis)++;
    uniq_size = 0;
    while (ch_st_uniq[uniq_size] != '\0') {
        uniq_size++;
    }
                                                                                /* --------- Check for New
                                                                                 * --------- uniq chars--------- */
    int i;
    for (i = 0; str[i]; i++) {
        bool uniq = true;
        for(int sub_i = 0; sub_i <= uniq_size; sub_i++) {
            while (ch_st_uniq[uniq_size] != '\0') {
                uniq_size++;
            }
            if (str[i] == ch_st_uniq[sub_i]) { uniq = false; break;}
        }
        if (uniq && str[i] != '\n') {
            ch_st_uniq[uniq_size] = str[i];
            (*st_uniq)++;
        }
    }
                                                                                /* -------- Compare passes to get
                                                                                 * -------- min  length---------- */
    if (*st_min > i) { *st_min = i - 1; }
    if (*st_max < i) { *st_max = i - 1; }
                                                                                /* -------- Output all secure
                                                                                 * -------- passwords ------------- */
    for (i = 0; i < *pass_counter; i++) {
        printf("%s", passwords[i]);
    }
    printf("--------STATISTIC--------\n");
    printf("Uniq chars: %d\n", (*st_uniq));
    printf("Min  chars: %d\n", (*st_min));
    printf("Max  chars: %d\n", (*st_max));
    printf("AVG  chars: %.1f\n", (*st_avg));
    printf("\n\n");
}

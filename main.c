#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

bool firstLevel(char *p);
bool secondLevel(char *p);
bool thirdLevel(char *p);
bool fourthLevel(char *p);
bool firstSubLevel(char *p);
bool secondSubLevel(char *p);
bool thirdSubLevel(char *p);
bool fourthSubLevel(char *p);
int PARAM;
int main(int argc, char* argv[]) {
    typedef bool (* Function) (char* pointer);
    Function security_level_checker[] = {&firstLevel, &secondLevel, &thirdLevel, &fourthLevel};
    {
    printf("Program start!\n");
    printf("LEVEL arg - %s\n", argv[1]);
    printf("PARAM arg - %s\n", argv[2]);
    }
    PARAM = atoi(argv[2]);
    bool end = true;
    while (end) {
        printf("%d\n", PARAM);
        char pass[101];
        char temp[101] = "";
        char* pch;
        int sec_lvl = 0;
        scanf("%100s", pass);
        printf("%s", pass);
        pch = pass;
        for (int level = 0; level < 4; level++) {
            if (security_level_checker[level](pch)) {
                printf("Security level %d: success\n", level + 1);
                sec_lvl++;
            } else
            {
                printf("Security level %d: fail\n", level + 1);
            };
        }
        int i = 0;
        while (pass[i]) {
            if(temp[i] == pass[i]) {end = false; break;};
        }
        while (pass[i]) {
            temp[i] = pass[i];
        }
        printf("Final security level is: %d", sec_lvl);
    }
    return 0;
}

bool firstLevel(char* pointer)
{
    bool status[2] = {false, false};
    for (int i = 0;pointer[i]; i++) {
        if (status[0] == false && (98 <= pointer[i] && pointer[i] <= 122)) { status[0] = true; }
        if (status[1] == false && (65 <= pointer[i] && pointer[i] <= 90))  { status[1] = true; }
        if (status[0] == true && status[1] == true) { return true; }
    }
    printf("Password must obtain at least 1 capital and 1 lowercase letter\n");
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
        if (98 <= pointer[i] && pointer[i] <= 122) { return true; }
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
        if (32 <= pointer[i] && pointer[i] <= 126) { return true; }
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
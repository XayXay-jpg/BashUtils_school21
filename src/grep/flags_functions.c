#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <regex.h>

#include "s21_grep.h"


void flag_e(char *regular, char *line){
if (regular == NULL || line == NULL) return;

    regex_t regex;
    int reti = regcomp(&regex, regular, 0);
    if (reti) {
        return;
    }

    reti = regexec(&regex, line, 0, NULL, 0);
    if (!reti) {
        printf("%s\n", line);
    }

    regfree(&regex);
}

void flag_i(char*, char*) {}
void flag_v(char*, char*) {}
void flag_c(char*, char*) {}
void flag_l(char*, char*) {}
void flag_n(char*, char*) {}
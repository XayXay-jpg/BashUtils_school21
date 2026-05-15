#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <regex.h>

#include "s21_grep.h"

void flag_e(char *regular, FILE *f, char *filename){
    (void)filename;
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, 0)) return;

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, f) != -1) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }
    free(line);
    regfree(&regex);
}

void flag_i(char *regular, FILE *f, char *filename){
    (void)filename;
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, REG_ICASE)) return;

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, f) != -1) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }
    free(line);
    regfree(&regex);
}

void flag_v(char *regular, FILE *f, char *filename){
    (void)filename;
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, 0)) return;

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, f) != -1) {
        if (regexec(&regex, line, 0, NULL, 0)) {
            printf("%s", line);
        }
    }
    free(line);
    regfree(&regex);
}

void flag_c(char *regular, FILE *f, char *filename) {
    (void)filename;
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, 0)) return;

    char *line = NULL;
    size_t size = 0;
    int count = 0;
    while (getline(&line, &size, f) != -1) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            count++;
        }
    }
    printf("%d\n", count);
    
    free(line);
    regfree(&regex);
}

void flag_l(char *regular, FILE *f, char *filename) {
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, 0)) return;

    char *line = NULL;
    size_t size = 0;
    while (getline(&line, &size, f) != -1) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            printf("%s\n", filename);
            break;
        }
    }
    free(line);
    regfree(&regex);
}

void flag_n(char *regular, FILE *f, char *filename) {
    (void)filename;
    if (regular == NULL || f == NULL) return;
    regex_t regex;
    if (regcomp(&regex, regular, 0)) return;

    char *line = NULL;
    size_t size = 0;
    int line_num = 1;
    while (getline(&line, &size, f) != -1) {
        if (!regexec(&regex, line, 0, NULL, 0)) {
            printf("%d:%s", line_num, line);
        }
        line_num++;
    }
    free(line);
    regfree(&regex);
}
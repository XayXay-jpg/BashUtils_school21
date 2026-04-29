#include <stdio.h>
#include <stdlib.h>  
#include <string.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include "s21_grep.h"


void flag_e(char *regular, char *line){
    if (!regular || !line) {
        fprintf(stderr, "Error: NULL pointer passed to flag_e\n");
        return;
    }

    const char *text = line;
    const char *pattern = regular;

    pcre2_code *re;
    pcre2_match_data *match_data;
    int errorcode;
    PCRE2_SIZE erroroffset;
    PCRE2_SIZE start = 0;
    int rc;

    re = pcre2_compile((PCRE2_SPTR)pattern, PCRE2_ZERO_TERMINATED, 0,
                       &errorcode, &erroroffset, NULL);
    if (!re) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(errorcode, buffer, sizeof(buffer));
        fprintf(stderr, "PCRE2 compilation failed at offset %d: %s\n", (int)erroroffset, buffer);
        exit(EXIT_FAILURE);
    }

    match_data = pcre2_match_data_create_from_pattern(re, NULL);
    if (!match_data) {
        fprintf(stderr, "Failed to allocate match data\n");
        pcre2_code_free(re);
        exit(EXIT_FAILURE);
    }

    while ((rc = pcre2_match(re, (PCRE2_SPTR)text, strlen(text),
                             start, 0, match_data, NULL)) >= 0) {
        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
        PCRE2_SIZE start_pos = ovector[0];
        PCRE2_SIZE end_pos = ovector[1];

        for (PCRE2_SIZE i = start_pos; i < end_pos; i++) {
            putchar(text[i]);
        }
        putchar('\n');

        start = end_pos;
        if (start_pos == end_pos) start++; 
    }

    
    if (rc < 0 && rc != PCRE2_ERROR_NOMATCH) {
        PCRE2_UCHAR buffer[256];
        pcre2_get_error_message(rc, buffer, sizeof(buffer));
        fprintf(stderr, "PCRE2 match error: %s\n", buffer);
    }

    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
}

void flag_i(char*, char*) {}
void flag_v(char*, char*) {}
void flag_c(char*, char*) {}
void flag_l(char*, char*) {}
void flag_n(char*, char*) {}
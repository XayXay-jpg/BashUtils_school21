#include <stdio.h>
#include <string.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

#include "s21_grep.h"


void flag_e(char *regular, char *line){

    // Исходная строка со служебными символами
    const char *text = line;
    // Регулярное выражение: последовательности букв (кириллица + латиница)
    const char *pattern = regular;

    pcre2_code *re;
    pcre2_match_data *match_data;
    int errorcode;
    PCRE2_SIZE erroroffset;
    PCRE2_SIZE start = 0;
    int rc;

    // Компиляция
    re = pcre2_compile((PCRE2_SPTR)pattern, PCRE2_ZERO_TERMINATED, 0,
                       &errorcode, &erroroffset, NULL);
    if (!re) {
        fprintf(stderr, "Ошибка компиляции\n");
        exit(EXIT_FAILURE);
    }

    // Структура для хранения позиций совпадений
    match_data = pcre2_match_data_create_from_pattern(re, NULL);

    // Поиск всех совпадений
    while ((rc = pcre2_match(re, (PCRE2_SPTR)text, strlen(text),
                             start, 0, match_data, NULL)) >= 0) {
        PCRE2_SIZE *ovector = pcre2_get_ovector_pointer(match_data);
        PCRE2_SIZE start_pos = ovector[0];
        PCRE2_SIZE end_pos = ovector[1];

        // Выводим найденное слово
        for (PCRE2_SIZE i = start_pos; i < end_pos; i++) {
            putchar(text[i]);
        }
        putchar('\n');

        // Сдвигаем стартовую позицию для следующего поиска
        start = end_pos;
        if (start_pos == end_pos) start++; // защита от пустых совпадений
    }

    // Освобождение ресурсов
    pcre2_match_data_free(match_data);
    pcre2_code_free(re);
};

void flag_i(char *regular, char *line){};

void flag_v(char *regular, char *line){};

void flag_c(char *regular, char *line){};

void flag_l(char *regular, char *line){};

void flag_n(char *regular, char *line){};
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

int main(int argc, char *argv[]) {
    // Программа всегда вызывается с флагом: ожидаем 3 аргумента
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -<flag> pattern\n", argv[0]);
        return 1;
    }

    char *line = NULL;
    size_t size = 0;
    ssize_t len;

    functions flags[] = {
        {'e', flag_e},
        {'i', flag_i},
        {'v', flag_v},
        {'c', flag_c},
        {'l', flag_l},
        {'n', flag_n},
    };

    args arguments = checkFlags(argv);

    int num_flags = sizeof(flags) / sizeof(flags[0]);
    int idx = foundFunc(arguments.flag, flags, num_flags);
    if (idx == -1) {
        fprintf(stderr, "Unknown flag '%c'\n", arguments.flag);
        return 1;
    }

    // Читаем все строки из stdin и обрабатываем каждую выбранной функцией
    while ((len = getline(&line, &size, stdin)) != -1) {
        flags[idx].function(arguments.string, line);
    }

    free(line);
    return 0;
}

args checkFlags(char *argv[]) {
    args result = {0, NULL};
    if (strlen(argv[1]) == 2) {
        result.flag = argv[1][1];
        result.string = argv[2];
    } else {
        result.string = argv[1];
    }
    return result;
}

int foundFunc(char flag, functions flags[], int size) {
    int res = -1;
    for (int i = 0; i < size; i++) {
        if (flag == flags[i].flag) {
            res = i;
            break;
        }
    }
    return res;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

int main(int argc, char *argv[]){

    char *line = NULL;
    size_t size = 0;
    ssize_t len = getline(&line, &size, stdin);

    functions flags[] = {
        {'e', flag_e},
        {'i', flag_i},
        {'v', flag_v},
        {'c', flag_c},
        {'l', flag_l},
        {'n', flag_n},
    };

    args arguments = checkFlags(argv);

    flags[foundFunc(arguments.flag, flags)].function(arguments.string, line);

    return 0;
}

args checkFlags(char *argv[]){

    args result = {NULL, NULL};

    if (strlen(argv[1]) == 2) {
        result.flag = argv[1][1];
        result.string = argv[2];
    } else {
        result.string = argv[1];
    }

    return result;
};

int foundFunc(char flag, functions flags[]){ 

    int res = NULL;

    for(int i = 0; i < sizeof(flags) / sizeof(flags[0]); i++){
        if (flag == flags[i].flag) res = i;
    }

    return res;
};

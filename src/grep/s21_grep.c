#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

int main(int argc, char *argv[]){

    functions flags[] = {
        {NULL, none_flag},
        {'e', flag_e},
        {'i', flag_i},
        {'v', flag_v},
        {'c', flag_c},
        {'l', flag_l},
        {'n', flag_n},
    };

    args arguments = checkFlags(argv);

    flags[foundFunc(arguments.flag, flags)].function(arguments.string);

    return 0;
}

args checkFlags(char *argv[]){

    args result = {NULL, NULL};

    if (strlen(argv[1]) == 2) {
        result.flag = argv[1][2];
        result.string = argv[2];
    } else {
        result.string = argv[1];
    }

    return result;
};

int foundFunc(char flag, functions flags[]){ 

    int res;

    for(int i; i < 7; i++){
        if (flag == flags[i].flag) res = i;
    }

    return res;
};

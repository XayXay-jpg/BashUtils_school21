#include <stdio.h>

//structs

typedef struct{
    char flag;
    char *string;
}args;

typedef struct{
    char flag;
    void (*function)(char *regular);
}functions;


//functions

args checkFlags(char *argv[]);

int foundFunc(char flag, functions flags[]);

void none_flag(char *regular);

void flag_e(char *regular);

void flag_i(char *regular);

void flag_v(char *regular);

void flag_c(char *regular);

void flag_l(char *regular);

void flag_n(char *regular);

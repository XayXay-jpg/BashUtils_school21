#include <stdio.h>

//structs

typedef struct{
    char flag;
    char *string;
}args;

typedef struct{
    char flag;
    void (*function)(char *regular, char *line);
}functions;

//functions

args checkFlags(char *argv[]);

int foundFunc(char flag, functions flags[], int size);

void flag_e(char *regular, char *line);

void flag_i(char *regular, char *line);

void flag_v(char *regular, char *line);

void flag_c(char *regular, char *line);

void flag_l(char *regular, char *line);

void flag_n(char *regular, char *line);
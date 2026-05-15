#include <stdio.h>

//structs

typedef struct{
    char flag;
    void (*function)(char *regular, FILE *file, char *filename);
}functions;

//functions

int foundFunc(char flag, functions flags[], int size);

void flag_e(char *regular, FILE *file, char *filename);

void flag_i(char *regular, FILE *file, char *filename);

void flag_v(char *regular, FILE *file, char *filename);

void flag_c(char *regular, FILE *file, char *filename);

void flag_l(char *regular, FILE *file, char *filename);

void flag_n(char *regular, FILE *file, char *filename);
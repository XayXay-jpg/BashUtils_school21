#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_file_simple(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%s", line);
    }
    fclose(file);
}

void print_file_with_numbers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    int line_number = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        printf("%d %s", ++line_number, line);
    }
    fclose(file);
}

void print_file_with_nonempty_numbers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    int line_number = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (line[0] != '\n') {
            printf("%d %s", ++line_number, line);
        } else {
            printf("%s", line);
        }
    }
    fclose(file);
}

void print_file_with_e_markers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    char new_line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        int src = 0, dst = 0;
        while (line[src] != '\0') {
            if (line[src] == '\r') {
                new_line[dst++] = '^';
                new_line[dst++] = 'M';
                src++;
            } else if (line[src] == '\n') {
                new_line[dst++] = '$';
                new_line[dst++] = '\n';
                src++;
            } else {
                new_line[dst++] = line[src++];
            }
        }
        new_line[dst] = '\0';
        printf("%s", new_line);
    }
    fclose(file);
}

void print_file_squeeze_blank(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    int is_empty = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        if (!is_empty || line[0] != '\n') {
            printf("%s", line);
        }
        is_empty = (line[0] == '\n');
    }
    fclose(file);
}

void print_file_with_t_markers(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("n/a");
        return;
    }
    
    char line[1024];
    char new_line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        int src = 0, dst = 0;
        while (line[src] != '\0') {
            if (line[src] == '\t') {
                new_line[dst++] = '^';
                new_line[dst++] = 'I';
                src++;
            } else {
                new_line[dst++] = line[src++];
            }
        }
        new_line[dst] = '\0';
        printf("%s", new_line);
    }
    fclose(file);
}

int main(int argc, char *argv[]) {
    // Проверка количества аргументов
    if (argc == 2) {
        // Без флага - просто выводим содержимое файла
        print_file_simple(argv[1]);
    } 
    else if (argc == 3 && argv[1][0] == '-') {
        // С флагом
        switch(argv[1][1]) {
            case 'b':
                print_file_with_nonempty_numbers(argv[2]);
                break;
            case 'e':
                print_file_with_e_markers(argv[2]);
                break;
            case 'n':
                print_file_with_numbers(argv[2]);
                break;
            case 's':
                print_file_squeeze_blank(argv[2]);
                break;
            case 't':
                print_file_with_t_markers(argv[2]);
                break;
            default:
                printf("n/a");
                break;
        }
    } 
    else {
        printf("n/a");
    }
    
    return 0;
}
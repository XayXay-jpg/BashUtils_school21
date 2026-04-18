#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){

    if (argc == 2 || (argv[1][0] == '-' && argc == 3)){
        
    FILE *file;
    char line[1024];
    char new_line[1024];
    int line_number = 0;
    int is_empty = 0;

        switch(argv[1][1]){
            case 'b': 
                file = fopen(argv[2], "r");
                if (file == NULL) {printf("n/a"); break;}
                while (fgets(line, sizeof(line), file) != NULL) {
                    ++line_number;
                    if (line[0] != '\n') printf("%d %s", line_number, line); 
                    else printf("%s", line);
                }
                fclose(file);
                break;
            case 'e': 
                file = fopen(argv[2], "r");
                if (file == NULL) {
                    printf("n/a");
                    break;
                }
                while (fgets(line, sizeof(line), file) != NULL) {
                    int src = 0, dst = 0;
                    while (line[src] != '\0') {
                        if (line[src] == '\r') {
                            new_line[dst++] = '^';
                            new_line[dst++] = 'M';
                            src++;          // только перемещаемся, не добавляем '\r'
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
                break;
            case 'n': 
                file = fopen(argv[2], "r");
                if (file == NULL) {printf("n/a"); break;}
                while (fgets(line, sizeof(line), file) != NULL) {
                    printf("%d %s", ++line_number, line); 
                }
                fclose(file);
                break;
            case 's': 
                file = fopen(argv[2], "r");
                if (file == NULL) {printf("n/a"); break;}
                while (fgets(line, sizeof(line), file) != NULL) {
                    if (!is_empty || line[0] != '\n') printf("%s", line); 
                    is_empty = line[0] == '\n';
                }
                fclose(file);
                break;
            case 't':
                file = fopen(argv[2], "r");
                if (file == NULL) {
                    printf("n/a");
                    break;
                }
                while (fgets(line, sizeof(line), file) != NULL) {
                    int src = 0;
                    int dst = 0;
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
                break;
            default:
                file = fopen(argv[1], "r");
                if (file == NULL) {printf("n/a"); break;}
                while (fgets(line, sizeof(line), file) != NULL) {
                    printf("%s", line); 
                }
                fclose(file);
                break;
        }
    }else printf("n/a");
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_grep.h"

int main(int argc, char *argv[]) {
  if (argc < 3) {
    fprintf(stderr, "n/a\n");
    return 1;
  }

  char flag = 0;
  char *pattern = NULL;
  int files_start = argc;

  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-' && flag == 0) {
      flag = argv[i][1];
    } else if (pattern == NULL) {
      pattern = argv[i];
    } else {
      files_start = i;
      break;
    }
  }

  if (pattern == NULL) {
    fprintf(stderr, "n/a\n");
    return 1;
  }

  functions flags[] = {
      {'e', flag_e}, {'i', flag_i}, {'v', flag_v},
      {'c', flag_c}, {'l', flag_l}, {'n', flag_n},
  };

  int num_flags = sizeof(flags) / sizeof(flags[0]);
  int idx = foundFunc(flag, flags, num_flags);
  if (idx == -1) {
    fprintf(stderr, "n/a\n");
    return 1;
  }

  if (files_start == argc) {
    flags[idx].function(pattern, stdin, "(standard input)");
  } else {
    for (int i = files_start; i < argc; i++) {
      FILE *f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "n/a\n");
        continue;
      }
      flags[idx].function(pattern, f, argv[i]);
      fclose(f);
    }
  }

  return 0;
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
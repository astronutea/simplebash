#include "s21_cat.h"

const struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                      {"number", no_argument, 0, 'n'},
                                      {"squeeze-blank", no_argument, 0, 's'},
                                      {0, 0, 0, 0}};

int check_flags(int argc, char* argv[], Flags* flags) {
  int status_code = OK;
  int option, option_index = 0;

  while ((option = getopt_long(argc, argv, "beEnstTv", long_options,
                               &option_index)) != -1 &&
         status_code == OK) {
    switch (option) {
      case 'b':
        flags->b = true;
        flags->n = false;
        break;
      case 'e':
        flags->e = true;
        flags->v = true;
        break;
      case 'E':
        flags->e = true;
        break;
      case 'n':
        flags->n = !flags->b;
        break;
      case 's':
        flags->s = true;
        break;
      case 't':
        flags->t = true;
        flags->v = true;
        break;
      case 'T':
        flags->t = true;
        break;
      case 'v':
        flags->v = true;
        break;
      default:
        status_code = ERROR;
        break;
    }
  }

  if (status_code == ERROR) {
    fprintf(stderr, "Unknown flag entered\n");
  }

  return status_code;
}

void cat(FILE* file, const Flags flags) {
  int symbol = 0, prev_symbol = '\n';
  int blank_lines = 0, lines_count = 0;

  while ((symbol = fgetc(file)) != EOF) {
    if (symbol == '\n' && prev_symbol == '\n') {
      blank_lines++;
    } else {
      blank_lines = 0;
    }

    if (flags.s && blank_lines > 1) continue;

    if (prev_symbol == '\n' && (flags.n || (flags.b && symbol != '\n')))
      printf("%6d\t", ++lines_count);

    if (flags.t && symbol == '\t') {
      printf("^");
      symbol += 64;
    }

    if (flags.e && symbol == '\n') printf("$");

    if (flags.v && symbol != '\t' && symbol != '\n') {
      if (symbol > 127) {
        printf("M-");
        symbol -= 128;
      }

      if (symbol < 32 || symbol == 127) {
        printf("^");
        if (symbol == 127) symbol = symbol - 128 + 64;
        else symbol = symbol + 64;
      }
    }

    printf("%c", symbol);
    prev_symbol = symbol;
  }
}
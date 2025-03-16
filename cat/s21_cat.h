#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define OK 0
#define ERROR 1

typedef struct {
  bool b;
  bool e;
  bool n;
  bool s;
  bool t;
  bool v;
} Flags;

extern const struct option long_options[];

int check_flags(int argc, char* argv[], Flags* flags);

void cat(FILE* file, const Flags flags);

#endif  // S21_CAT_H

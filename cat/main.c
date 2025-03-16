#include "s21_cat.h"

int main(int argc, char* argv[]) {
  Flags flags = {false};
  int status_code = check_flags(argc, argv, &flags);

  if (status_code == OK) {
    for (int i = optind; i < argc; i++) {
      FILE* file = fopen(argv[i], "r");
      if (file != NULL) {
        cat(file, flags);
        fclose(file);
      } else {
        fprintf(stderr, "Could not open the file: %s\n", argv[i]);
      }
    }
  }

  return status_code;
}
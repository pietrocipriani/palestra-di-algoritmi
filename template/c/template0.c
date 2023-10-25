#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE * const in = fopen("input.txt", "r");
  FILE * const out = fopen("output.txt", "w");

  // TODO: codice

  fclose(in); fclose(out);
}

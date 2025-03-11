#include <stdio.h>
#include "mylib.h"

int main(int argc, char *argv[]) {

  if (argc < 3) {
    fprintf(stderr, "Not enough arguments\n");
    return -1;
  }

  FILE *file1 = fopen(argv[1], "r");
  if (file1 == NULL) {
    fprintf(stderr, "Error opening file for reading\n");
    return -1;
  }
  FILE *file2 = fopen(argv[2], "w");
  if (file1 == NULL) {
    fprintf(stderr, "Error opening file for writing\n");
    fclose(file1);
    return -1;
  }

  int ch;
  while ((ch = fgetc(file1)) != EOF)
    if (ch == '\n')
      break;

  processor p;

  while (10 == fscanf(file1,
                      "%[^:]:%[^:]:%d:%d:%f to %f GHz:%[^:]:%d nm:%d MB:%d W\n",
                      p.Name, p.Codename, &p.Cores, &p.Threads, &p.minClock,
                      &p.maxClock, p.Socket, &p.Process, &p.L3_Cache, &p.TDP)) {
    fwrite(&p, sizeof(processor), 1, file2);
  }

  fclose(file1);
  fclose(file2);
}
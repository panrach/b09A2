#include <stdio.h>
#include "record.h"
#include <string.h>
#define RECORD_SIZE 32

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Need filename.\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) {
    perror("fopen");
    return 1;
  }

  // read-print loop
  record rec;
  fseek(f, 0, SEEK_SET);
  
  while ((fread(&rec, 1, RECORD_SIZE, f)) > 0) {
    printf("%.*s has %hu sunspots\n", rec.name_len, rec.name, rec.sunspots);
  }

  fclose(f);
  return 0;
}

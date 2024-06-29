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
  size_t bytes_read;
  char entry[RECORD_SIZE];

  fseek(f, 0, SEEK_SET);
  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    if (rec.name_len >= NAME_LEN_MAX) {
      rec.name_len = NAME_LEN_MAX - 1; // ensure null-termination
    }

    char _name[NAME_LEN_MAX];
    memcpy(_name, rec.name, rec.name_len);
    _name[rec.name_len] = '\0';

    printf("%s has %hu sunspots\n", _name, rec.sunspots);
  }

  fclose(f);
  return 0;
}

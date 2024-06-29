#include <stdio.h>
#include "record.h"
#include "record.c"

int main(int argc, char **argv)
{
  if (argc < 2) {
    fprintf(stderr, "Need filename.\n");
    return 1;
  }
  FILE *f = fopen(argv[1], "r+b");
  if (f == NULL) {
    perror("fopen");
    return 1;
  }

  // Get Dennis Ritchie sunspots
  unsigned short y;
  // if (get_sunspots(f, "Dennis Ritchie", &y)) {
  //   printf("Ritchie has %hu sunspots\n", y);
  // } else {
  //   printf("Ritchie not found\n");
  // }

  char name[NAME_LEN_MAX + 1] = "Rachel2";
  // Add a new record.
  // set_sunspots(f, name, 10101);
  if (get_sunspots(f, name, &y)) {
    printf("%s has %hu sunspots\n", name, y);
  } else {
    printf("%s not found\n", name);
  }

  fclose(f);
  return 0;
}
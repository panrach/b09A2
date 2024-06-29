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

  // Add a new record.
  unsigned short w;
  // set_sunspots(f, "William Henry Gates MCXXXVIII", 31338);

  if (get_sunspots(f, "William Henry Gates MCXXXVIII", &w)) {
    printf("Will has %hu sunspots\n", w);
  } else {
    printf("Will not found\n");
  }

  // // Change Archimedes's sunspots
  // set_sunspots(f, "Archimedes", 3000);

  fclose(f);
  return 0;
}
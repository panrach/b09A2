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

  // Add a new record.
  set_sunspots(f, "William Henry Gates MCXXXVIII", 31337);

  // Change Archimedes's sunspots
  set_sunspots(f, "Archimedes", 3000);

  fclose(f);
  return 0;
}
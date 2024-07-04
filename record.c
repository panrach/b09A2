#include <stdio.h>
#include <string.h>
#include "record.h"

#define RECORD_SIZE 32

void set_sunspots(FILE *f, const char *name, unsigned short sunspots)
{
  record rec;
  size_t bytes_read;
  char entry[RECORD_SIZE];

  fseek(f, 0, SEEK_SET);

  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    char temp_name[NAME_LEN_MAX + 1];
    memcpy(temp_name, rec.name, rec.name_len);
    temp_name[rec.name_len] = '\0';

    if (strcmp(temp_name, name) == 0) {
      rec.sunspots = sunspots;
      fseek(f, -RECORD_SIZE, SEEK_CUR);
      fwrite(&rec, RECORD_SIZE, 1, f);
      return;
    }
  }
  // not found
  size_t name_length = strlen(name);

  // Copy the name to the record
  memcpy(rec.name, name, name_length);
  
  // Set the name length and sunspots
  rec.name_len = name_length;
  rec.sunspots = sunspots;

  // Write the new record to the file
  fwrite(&rec, RECORD_SIZE, 1, f);
  return;
}

int get_sunspots(FILE *f, const char *name, unsigned short *psunspots)
{
  size_t bytes_read;
  char entry[RECORD_SIZE];

  fseek(f, 0, SEEK_SET);

  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    char temp_name[NAME_LEN_MAX + 1];
    memcpy(temp_name, rec.name, rec.name_len);
    temp_name[rec.name_len] = '\0';
    if (strcmp(temp_name, name) == 0) {
      *psunspots = rec.sunspots;
      return 1;
    }
  }
  return 0;
}

#include <stdio.h>
#include <string.h>
#include "record.h"

#define RECORD_SIZE 32

/*
Overwrite the sunspots field of name
If multiple records have the same name: change 1st
If not found: add a new record at the end
Must start seeking at the beginning
*/
void set_sunspots(FILE *f, const char *name, unsigned short sunspots)
{
  record rec;
  size_t bytes_read;
  char entry[RECORD_SIZE];

  fseek(f, 0, SEEK_SET);


  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    char _name[NAME_LEN_MAX + 1];
    memcpy(_name, rec.name, rec.name_len);
    _name[rec.name_len] = '\0';

    if (strcmp(_name, name) == 0) {
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
  name = rec.name;
  rec.name[name_length] = '\0'; // Null-terminate the string

  // Set the name length and sunspots
  rec.name_len = name_length;
  rec.sunspots = sunspots;

  // Write the new record to the file
  fwrite(&rec, RECORD_SIZE, 1, f);
  return;
}

/*
Get the sunspots field from the record that has the given name.
If found: store answer at psunspots address
If not found: return 0
If multiple records with same name: return 1st
File position can be anywhere. Must start seeking at beginning
*/

int get_sunspots(FILE *f, const char *name, unsigned short *psunspots)
{
  size_t bytes_read;
  char entry[RECORD_SIZE];

  fseek(f, 0, SEEK_SET);

  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    char _name[NAME_LEN_MAX + 1];
    memcpy(_name, rec.name, rec.name_len);
    _name[rec.name_len] = '\0';
    if (strcmp(_name, name) == 0) {
      *psunspots = rec.sunspots;
      return 1;
    }
  }
  return 0;
}
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
  fseek(f, 0, SEEK_SET);
  record rec;
  size_t bytes_read;
  char entry[RECORD_SIZE];

  while ((bytes_read = fread(entry, 1, RECORD_SIZE, f)) > 0) {
    record rec;
    memcpy(&rec, entry, sizeof(record)); // copy the data to the record

    if (rec.name_len >= NAME_LEN_MAX) {
      rec.name_len = NAME_LEN_MAX - 1; // ensure null-termination
    }
    char _name[NAME_LEN_MAX];
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

  // for null terminating
  if (name_length >= NAME_LEN_MAX) {
    name_length = NAME_LEN_MAX - 1;
  }

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

    if (rec.name_len >= NAME_LEN_MAX) {
      rec.name_len = NAME_LEN_MAX - 1; // ensure null-termination
    }

    char _name[NAME_LEN_MAX];
    memcpy(_name, rec.name, rec.name_len);
    _name[rec.name_len] = '\0';
    if (strcmp(_name, name) == 0) {
      *psunspots = rec.sunspots;
      return 1;
    }
  }
  return 0;
}

/*
00000000  0e 44 65 6e 6e 69 73 20  52 69 74 63 68 69 65 2d  |.Dennis Ritchie-|
00000010  2d 2d 2d 2d 2d 2d 2d 2d  2d 2d 2d 2d 2d 2d 86 07  |--------------..|
00000020  0a 41 72 63 68 69 6d 65  64 65 73 2d 2d 2d 2d 2d  |.Archimedes-----|
00000030  2d 2d 2d 2d 2d 2d 2d 2d  2d 2d 2d 2d 2d 2d 22 01  |--------------".|
00000040  0b 41 6c 61 6e 20 54 75  72 69 6e 67 2d 2d 2d 2d  |.Alan Turing----|
00000050  2d 2d 2d 2d 2d 2d 2d 2d  2d 2d 2d 2d 2d 2d 60 ea  |--------------`.|
00000060

- Leftmost column tells the current position
- 2d tells you you're done calculating sunspots

ie 
Dennis Ritchie
07 + 86 = 0786 sunspots in hex
return the integer representation

1 function for getting to the name
1 function treating one line "as an array"
*/
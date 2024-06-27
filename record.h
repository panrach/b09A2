#ifndef _RECORD_H
#define _RECORD_H

#include <stdio.h>

#define NAME_LEN_MAX 29

typedef struct record {
  unsigned char name_len;        // length of name
  char name[NAME_LEN_MAX];       // name; NOT nul-terminated! use name_len above
  unsigned short sunspots;       // 2 bytes on x86-64
} record;
// record size conspires to be 32 bytes on x86-64 :)

int get_sunspots(FILE *f, const char *name, unsigned short *psunspots);
// In the file, get the sunspots field of the record that has given name.
//
// If found, store the answer at the psunspots address, and return 1 (C
// true).
//
// If not found, return 0 (C false).
//
// If multiple records have the same name, just use the 1st one.
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.

void set_sunspots(FILE *f, const char *name, unsigned short sunspots);
// In the file, change (overwrite) the sunspots field of the record that has the
// given name.
//
// If multiple records have the same name, just change the 1st one.
//
// If no record has the name, add a new record at the end.
//
// File position before this may be anywhere. Do your own "seek to the
// beginning" before you search.

#endif  // #ifndef _RECORD_H

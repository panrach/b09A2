#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "record.h"
#include "record.c"

/*
    1.1: empty file
    1.2: normal file
    1.3: normal file but doesn't exist
*/
void test_get()
{
    FILE *f = fopen("empty.dat", "r+b");
    unsigned short y;

    // 1.1
    printf("1.1: %s\n", get_sunspots(f, "janani", &y) == 0 ? "PASSED" : "FAILED");
    fclose(f);

    f = fopen("sample.dat", "r+b");

    // 1.2
    assert(get_sunspots(f, "Alan Turing", &y) == 1);
    printf("1.2: %s\n", y == 60000 ? "PASSED" : "FAILED");

    // 1.3
    printf("1.3: %s\n", get_sunspots(f, "alysa", &y) == 0 ? "PASSED" : "FAILED");

    fclose(f);
    return;
}

// count the number of entries
int count_entries(FILE *f) {
    fseek(f, 0, SEEK_END); // Seek to the end of the file
    long file_size = ftell(f); // Get the current position (which is the file size)
    fseek(f, 0, SEEK_SET); // Rewind to the beginning of the file

    int num_entries = file_size / RECORD_SIZE;
    return num_entries;
}

/*
    ** get_sunspots MUST work first **
    2.1: First (normal) entry to an empty file
    2.2: Adding name of length max
    2.3: Update name that's already in there
    2.4: add an entry with 0 sunspots
    2.5: add an entry with 65535 (max) sunspots
    2.6: update a name of length max with 65535 (max) sunspots
    2.7: add a name of length 0
    2.8: update a name of length 0
*/
void test_set()
{
    unsigned short y;

    FILE *f = fopen("empty.dat", "r+b");

    // 2.1
    set_sunspots(f, "Alysa", 5);
    get_sunspots(f, "Alysa", &y);
    assert(count_entries(f) == 1);
    printf("2.1: %s\n", y ==  5 ? "PASSED" : "FAILED");

    // 2.2
    set_sunspots(f, "11111111111111111111111111112", 10);
    get_sunspots(f, "11111111111111111111111111112", &y);
    assert(count_entries(f) == 2);
    printf("2.2: %s\n", y ==  10 ? "PASSED" : "FAILED");

    // 2.3
    set_sunspots(f, "Alysa", 0);
    get_sunspots(f, "Alysa", &y);
    assert(count_entries(f) == 2);
    printf("2.3: %s\n", y ==  0 ? "PASSED" : "FAILED");

    // 2.4
    set_sunspots(f, "Poor", 0);
    get_sunspots(f, "Alysa", &y);
    assert(count_entries(f) == 3);
    printf("2.4: %s\n", y ==  0 ? "PASSED" : "FAILED");

    // 2.5
    set_sunspots(f, "Rich", 65535);
    get_sunspots(f, "Rich", &y);
    assert(count_entries(f) == 4);
    printf("2.5: %s\n", y ==  65535 ? "PASSED" : "FAILED");

    // 2.6
    set_sunspots(f, "", 100);
    get_sunspots(f, "", &y);
    assert(count_entries(f) == 5);
    printf("2.6: %s\n", y ==  100 ? "PASSED" : "FAILED");

    // 2.7
    set_sunspots(f, "Rich", 100);
    get_sunspots(f, "Rich", &y);
    assert(count_entries(f) == 5);
    printf("2.7: %s\n", y ==  100 ? "PASSED" : "FAILED");

    // 2.8
    set_sunspots(f, "", 200);
    get_sunspots(f, "", &y);
    assert(count_entries(f) == 5);
    printf("2.8: %s\n", y ==  200 ? "PASSED" : "FAILED");

    fclose(f);

    return;
}

// check how many records do not have the correct length
int length() {
    int num_invalid = 0;
    record rec;
    FILE *f = fopen("empty.dat", "r+b");

    fseek(f, 0, SEEK_SET);

    while (fread(&rec, 1, RECORD_SIZE, f) == RECORD_SIZE) {
        char temp_name[NAME_LEN_MAX + 1];
        memcpy(temp_name, rec.name, rec.name_len);
        temp_name[rec.name_len] = '\0';
        if (strlen(temp_name) != rec.name_len) {
            printf("%.*s has length %ld and is supposed to have length %u\n", rec.name_len, rec.name, strlen(temp_name), rec.name_len);
            num_invalid++;
        }
    }

    fclose(f);
    return num_invalid;
}
// 3.1
void test_invalid_length() {
    // empty.dat should not be empty anymore
    // this should be run after test_set
    printf("3.1: %s\n", length() == 0 ? "PASSED" : "FAILED");
    return;
}

int main()
{
    // empty.dat should be empty
    test_get();
    // empty.dat should be empty
    test_set();
    // empty.dat should no longer be empty
    test_invalid_length();

    return 0;
}
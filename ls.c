/**
 * ls command
 *
 * TODO:
 *      - Add options
 *      - Sort output better, ignore case
 *      - Handle path argument
 */

#include "dbg.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Default path to open as a directory
 */

const char* DEFAULT_PATH = ".";

/**
 * Free the given directory entries
 *
 * ARGS:
 *      count = The number of entries to free
 *      entries = The entries
 */

void free_entries(int count, struct dirent** entries)
{
    int i = 0;

    for(i = 0; i < count; i++)
    {
        free(entries[i]);
    }

    free(entries);
}

/**
 * Filter dot entries, passed to scandir's filter argument
 *
 * ARGS:
 *      entry = The directory entry
 *
 * RETURNS:
 *      0 if entry begins with a dot, 1 otherwise
 */

int filter_dot(const struct dirent* entry)
{
    check(entry, "Cannot filter null entry");

    return entry->d_name[0] != '.';

error:
    return 0;
}

int main(int argc, char* argv[])
{
    struct dirent** entries = NULL;
    int rc = 0;
    int i = 0;

    rc = scandir(DEFAULT_PATH, &entries, filter_dot, alphasort);
    check(rc >= 0, "Unable to open directory: %s", DEFAULT_PATH);

    for(i = 0; i < rc; i++)
    {
        printf("%s\n", entries[i]->d_name);
    }

    free_entries(rc, entries);

    return 0;

error:
    if(rc > 0 && entries)
    {
        free_entries(rc, entries);
    }

    return 1;
}

/**
 * ls command
 *
 * TODO:
 *      - Add options
 *      - Handle path argument
 */

#include "dbg.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
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

/**
 * Compare two entries, passed to scandir's compare argument
 * Uses case-insensitive string comparison
 *
 * ARGS:
 *      e1 = The first entry
 *      e2 = The second entry
 *
 * RETURNS:
 *      compare result
 */

int sort_nocase(const struct dirent** e1, const struct dirent** e2)
{
    check(e1 && *e1, "First compare entry is null");
    check(e2 && *e2, "Second compare entry is null");

    return strcasecmp((*e1)->d_name, (*e2)->d_name);

error:
    return 0;
}

int main(int argc, char* argv[])
{
    struct dirent** entries = NULL;
    int rc = 0;
    int i = 0;

    rc = scandir(DEFAULT_PATH, &entries, filter_dot, sort_nocase);
    check(rc >= 0, "Unable to open directory: %s", DEFAULT_PATH);

    for(i = 0; i < rc; i++)
    {
        printf("%s  ", entries[i]->d_name);
    }

    printf("\n");
    free_entries(rc, entries);

    return 0;

error:
    if(rc > 0 && entries)
    {
        free_entries(rc, entries);
    }

    return 1;
}

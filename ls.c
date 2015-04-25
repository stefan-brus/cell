/**
 * ls command
 *
 * TODO:
 *      - Format output better
 */

#include "dbg.h"
#include <dirent.h>
#include <stdbool.h>
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
 * Print the given entries
 *
 * Args:
 *      count = The number of entries
 *      entries = The entries
 */

void print_entries(int count, struct dirent** entries)
{
    int i = 0;

    check(entries, "Entries are null");
    check(count >= 0, "No entries to print");

    for(i = 0; i < count; i++)
    {
        printf("%s  ", entries[i]->d_name);
    }

    printf("\n");

error:
    return;
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

/**
 * Read and print the entries in the given path
 *
 * Args:
 *      path = The path
 *      a = -a command line option, whether or not to skip dot entries
 *
 * Returns:
 *      The number of read entries
 */

int read_print_path(const char* path, bool a)
{
    struct dirent** entries = NULL;
    int (*filter_fn)(const struct dirent*) = NULL;
    int rc = 0;

    filter_fn = a ? NULL : filter_dot;

    rc = scandir(path, &entries, filter_fn, sort_nocase);
    check(rc >= 0, "Unable to open directory: %s", path);
    check(entries, "Entries are null in directory: %s", path);
    print_entries(rc, entries);
    free_entries(rc, entries);

    return rc;

error:
    if(rc > 0 && entries)
    {
        free_entries(rc, entries);
    }

    return -1;
}

/**
 * Read the command line options from argv
 * Write command line options into the output arguments
 *
 * Args:
 *      argc = argument count
 *      argv = argument vector
 *      a = output, whether or not 'a' was set
 *
 * TODO: Generalize and make this a vararg function
 */

void read_opts(int argc, char* argv[], bool* a)
{
    int opt = 0;

    while((opt = getopt(argc, argv, "a")) != -1)
    {
        switch(opt)
        {
            case 'a':
                *a = true;
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    int rc = 0;
    int i = 0;
    bool a = false;

    read_opts(argc, argv, &a);

    if(argc == 1 || optind >= argc)
    {
        rc = read_print_path(DEFAULT_PATH, a);
        check(rc >= 0, "Unable to open path: %s", DEFAULT_PATH);
    }
    else if(argc == 2 || (argc == 3 && optind == 2))
    {
        rc = read_print_path(argv[optind], a);
        check(rc >= 0, "Unable to open path: %s", argv[optind]);
    }
    else
    {
        for(i = optind; i < argc; i++)
        {
            printf("%s:\n", argv[i]);
            rc = read_print_path(argv[i], a);
            check(rc >= 0, "Unable to open path: %s", argv[i]);
            printf("\n");
        }
    }

    return 0;

error:
    return 1;
}

/**
 * ls command
 *
 * TODO:
 *      - Add options
 *      - Sort output
 *      - Handle path argument
 */

#include "dbg.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    DIR* d = NULL;
    struct dirent* dir = NULL;

    d = opendir(".");
    check(d, "Unable to open directory: %s", ".");

    while((dir = readdir(d)))
    {
        printf("%s\n", dir->d_name);
    }

    return 0;

error:
    if(d)
    {
        closedir(d);
    }

    return 1;
}

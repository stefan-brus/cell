/**
 * cd command
 *
 * Currently only demonstrates its ability to change the dir for this program.
 *
 * TODO: Make this useful
 */

#include "dbg.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/**
 * Default directory to switch to if no argument is given
 */

const char* DEFAULT_DIR = "/home/stefan";

/**
 * Size of buffer to store current dir name in
 */

const size_t CD_BUF_SIZE = 4096;

/**
 * Print the usage of this command
 */

static void print_usage()
{
    printf("USAGE:\n");
    printf("cd [PATH]\n");
    printf("If no PATH is given, the target dir will be %s\n", DEFAULT_DIR);
}

int main(int argc, char* argv[])
{
    const char* path = NULL;
    char cur_dir[CD_BUF_SIZE];
    FILE* dir = NULL;
    int fd = 0;
    int rc = 0;

    switch(argc)
    {
        case 1:
            path = (char*)DEFAULT_DIR;
            break;
        case 2:
            path = argv[1];
            break;
        default:
            print_usage();
            goto error;
    }

    dir = fopen(path, "r");
    check(dir, "Unable to open directory: %s", path);

    fd = fileno(dir);
    check(fd, "Unable to get file descriptor of directory: %s", path);

    rc = fchdir(fd);
    check(rc == 0, "Unable to change to directory: %s", path);

    check(getcwd(cur_dir, CD_BUF_SIZE), "Unable to get current directory name");
    printf("Current dir name: %s\n", cur_dir);

    fclose(dir);

    return 0;

error:
    if(dir)
    {
        fclose(dir);
    }

    return 1;
}

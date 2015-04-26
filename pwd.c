/**
 * pwd command
 */

#include "dbg.h"
#include <stdio.h>
#include <unistd.h>

/**
 * Size of buffer to store current dir name in
 */

static const size_t CD_BUF_SIZE = 4096;

int main(int argc, char* argv[])
{
    char cd_buf[CD_BUF_SIZE];

    check(getcwd(cd_buf, CD_BUF_SIZE), "Unable to get current directory name");
    printf("%s\n", cd_buf);

    return 0;

error:
    return 1;
}

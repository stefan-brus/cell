/**
 * cat command
 */

#include "dbg.h"
#include <stdio.h>

/**
 * Echo characters to stdout from the given file until EOF
 *
 * Args:
 *      f = The file
 */

void echo(FILE* f)
{
    int c;

    check(f, "Can't cat unopened file.");

    while((c = fgetc(f)) != EOF)
    {
        fputc(c, stdout);
    }

error:
    return;
}

int main(int argc, char* argv[])
{
    FILE *f = NULL;
    int i = 0;

    if(argc == 1)
    {
        echo(stdin);
    }
    else
    {
        for(i = 1; i < argc; i++)
        {
            f = fopen(argv[i], "r");
            check(f, "Error opening file: %s", argv[i]);
            echo(f);
            fclose(f);
        }
    }

    return 0;

error:
    if(f)
    {
        fclose(f);
    }

    return 1;
}

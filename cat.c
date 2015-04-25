/**
 * cat command
 */

#include "dbg.h"
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

/**
 * Echo characters to stdout from the given file until EOF
 *
 * Args:
 *      f = The file
 *      lines = Whether or not to print line numbers
 */

static void echo(FILE* f, bool lines)
{
    int c = 0;
    int line = 1;
    bool print_line = true;

    check(f, "Can't cat unopened file.");

    while((c = fgetc(f)) != EOF)
    {
        if(lines && print_line)
        {
            printf("%d: ", line);
            print_line = false;
        }

        fputc(c, stdout);

        if(c == '\n')
        {
            line++;
            print_line = true;
        }
    }

error:
    return;
}

/**
 * Read the command line options from argv
 * Write command line options into the output arguments
 *
 * Args:
 *      argc = argument count
 *      argv = argument vector
 *      n = output, whether or not 'n' was set
 *
 * TODO: Generalize and make this a vararg function
 */

static void read_opts(int argc, char* argv[], bool* n)
{
    int opt = 0;

    while((opt = getopt(argc, argv, "n")) != -1)
    {
        switch(opt)
        {
            case 'n':
                *n = true;
                break;
            default:
                break;
        }
    }
}

int main(int argc, char* argv[])
{
    FILE *f = NULL;
    int i = 0;
    bool n = false;

    read_opts(argc, argv, &n);

    if(argc == 1 || optind >= argc)
    {
        echo(stdin, n);
    }
    else
    {
        for(i = optind; i < argc; i++)
        {
            f = fopen(argv[i], "r");
            check(f, "Error opening file: %s", argv[i]);
            echo(f, n);
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

/*==============================================================================
This tool returns an error code that indicates whether one file is newer than
another.
==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

char usage[] =
"ftimecomp: Determine if one file is newer than another.\n"
"usage:     ftimecomp <file1> <file2>\n"
"version:   v1.0.1\n"
"\n"
"    This tool returns 0 if file1 is newer than file2, otherwise it will\n"
"    return 1.\n\n";


time_t GetModTime (const char *toolname, const char *filename);



int main (int argc, char *argv[])
{
    if (argc != 3)
    {
        fputs (usage, stdout);
        return 255;
    }

    time_t time1 = GetModTime (argv[0], argv[1]);
    time_t time2 = GetModTime (argv[0], argv[2]);

    return (time1 > time2) ? 0 : 1;
}



time_t GetModTime (const char *toolname, const char *filename)
{
    struct _stat stat;

    if (0 == _stat(filename, &stat))
        return stat.st_mtime;

    fprintf (stderr, "%s: Couldn't get status of \"%s\".\n",
             toolname, filename);

    exit (255);
}

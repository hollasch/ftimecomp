/*==============================================================================
This tool returns an error code that indicates whether one file is newer than
another.
==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

static const char usage[] =
"ftimecomp: Compare the modification times of two files.\n"
"version:   v2.0.0, https://github.com/hollasch/ftimecomp/\n"
"usage:     ftimecomp <file1> <file2>\n"
"\n"
"    This tool examines the modification times of file1 and file2. It returns 1\n"
"    if file1 is newer than file2, 2 if file2 is newer than file1, and 0 if both\n"
"    files have the same modification times.\n";



void errorExit (const char *message) {
    // Print error message and exit.
    fprintf (stderr, "ftimecomp: %s\n", message);
    exit (255);
}


time_t GetModTime (const char *filename) {

    // This function returns the modification time 

    struct _stat stat;

    if (0 == _stat(filename, &stat))
        return stat.st_mtime;

    char errMessage[1024];
    sprintf_s (errMessage, "Couldn't get status of \"%s\".", filename);
    errorExit (errMessage);

    return 0;
}


int main (int argc, char *argv[]) {

    if (argc != 3)
        errorExit (usage);

    time_t time1 = GetModTime (argv[1]);
    time_t time2 = GetModTime (argv[2]);

    if (time1 < time2)
        return 2;
    else if (time2 < time1)
        return 1;
    else
        return 0;
}

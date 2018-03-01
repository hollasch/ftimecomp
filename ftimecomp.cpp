/*==============================================================================
This tool returns an error code that indicates whether one file is newer than
another.
==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>

static const char usage[] =
"ftimecomp: Compare the modification times of two files.\n"
"version:   v2.1.0-beta, https://github.com/hollasch/ftimecomp/\n"
"usage:     ftimecomp [-h|--help] [-m|--handle-missing] <file1> <file2>\n"
"\n"
"    This tool examines the modification times of file1 and file2. It returns 1\n"
"    if file1 is newer than file2, 2 if file2 is newer than file1, and 0 if both\n"
"    files have the same modification times.\n"
"\n"
"    -h, --help\n"
"        Print help information.\n"
"\n"
"    -m, --handle-missing\n"
"        With this switch, a missing file is considered to be older than any\n"
"        existing file. If both files are missing, they compare the same.\n"
;

static char *fileName1;                    // Name of first file to compare
static char *fileName2;                    // Name of second file to compare
static auto  handleMissingFiles = false;   // If true, missing file appears maximally old


bool strEqualIgnoreCase (const char *a, const char *b) {
    // This function returns true if both strings compare as equal, ignoring case.

    if (!a || !b)
        return a == b;

    while (*a && *b && tolower(*a) == tolower(*b)) {
        ++a;
        ++b;
    }

    return (*a == 0) && (*b == 0);
}



void errorExit (const char *message) {
    // Print error message and exit. If the message is null, then print usage information.

    if (!message) {
        fprintf (stderr, usage);
    } else {
        fprintf (stderr, "ftimecomp: %s\n", message);
    }
    exit (255);
}


time_t GetModTime (const char *filename) {
    // This function returns the modification time of the given file. If the global
    // handleMissingFiles flag is set, then missing files return a time of 0.

    struct _stat stat;

    if (0 == _stat(filename, &stat))
        return stat.st_mtime;

    if (handleMissingFiles)
        return 0;

    char errMessage[1024];
    sprintf_s (errMessage, "Couldn't get status of \"%s\".", filename);
    errorExit (errMessage);

    return 0;
}


void processOptions (int argc, char *argv[]) {
    // Process the command-line options.

    auto fileCount = 0;        // Count of filenames given so far.
    char errMessage[1024];     // Buffer for error messages.

    for (auto argi = 1;  argi < argc;  ++argi) {

        // Handle file names (non-switches).
        if ((argv[argi][0] != '-') && (argv[argi][0] != '/')) {
            ++fileCount;
            if (fileCount == 1)
                fileName1 = argv[argi];
            else if (fileCount == 2)
                fileName2 = argv[argi];
            continue;
        }

        auto option = argv[argi] + 1;    // Option keyword

        // Parse options by keyword.
        if (  strEqualIgnoreCase(option, "?")
           || strEqualIgnoreCase(option, "h")
           || strEqualIgnoreCase(option, "-help")
           ) {
            errorExit (usage);
        } else if (strEqualIgnoreCase(option, "-handle-missing")) {
            handleMissingFiles = true;
        } else {
            sprintf_s (errMessage, "Unrecognized command option (%s).", argv[argi]);
            errorExit (errMessage);
        }
    }

    // Ensure that we got at least two files to compare.
    if (fileCount < 2) {
        errorExit ("Expected two file names.");
    }
}


int main (int argc, char *argv[]) {

    processOptions (argc, argv);

    time_t time1 = GetModTime (fileName1);
    time_t time2 = GetModTime (fileName2);

    if (time1 > time2)    // File 1 is newer
        return 1;

    if (time2 > time1)    // File 2 is newer
        return 2;

    return 0;             // Both files have the same modification time
}

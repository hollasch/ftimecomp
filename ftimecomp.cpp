/*==============================================================================
This tool returns an error code that indicates whether one file is newer than
another.
==============================================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <sys/stat.h>


const auto version = "ftimecomp 2.2.0-alpha.5 | 2021-04-22 | https://github.com/hollasch/ftimecomp";

const char usage[] = R"(
ftimecomp: compare the modification times of two files.
usage    : ftimecomp [-m|--missing-ok] [-n|--print-newer] [-o|--print-older]
                     [-h|--help] [--version]
                     <file1> <file2>

    This tool examines the modification times of file1 and file2. It returns 1
    if file1 is newer than file2, 2 if file2 is newer than file1, and 0 if both
    files have the same modification times.

    --help, -h
        Print help information.

    --missing-ok, -m
        Missing items are ok, and are considered older than existing ones.

    --print-newer, -n
        Print the newer of the two files. Cannot be used with --print-older.

    --print-older, -o
        Print the older of the two files. Cannot be used with --print-newer.

    --version
        Print version information.
)";


//--------------------------------------------------------------------------------------------------
struct Params {
    char *fileName1;               // Name of first file to compare
    char *fileName2;               // Name of second file to compare
    bool  missingIsOld { false };  // If true, missing file appears maximally old
    bool  printNewer   { false };  // True => print newer of the two files
    bool  printOlder   { false };  // True => print older of the two files
};


//--------------------------------------------------------------------------------------------------
bool strEqualIgnoreCase (const char *a, const char *b) {
    // This function returns true if both strings compare as equal, ignoring case. Note that this
    // is not a great implementation, since we should really be using foldcase for best language
    // tolerance. However, we're just using it for command option parsing, so it's ok for this use.

    if (!a || !b) return a == b;

    while (*a && *b && toupper(*a) == toupper(*b)) {
        ++a;
        ++b;
    }

    return (*a == 0) && (*b == 0);
}


//--------------------------------------------------------------------------------------------------
void errorExit (const char *message, bool printUsage = false) {
    // Print error message and optionally the usage information, and exit. This routine always
    // prints usage information if the message is null. If there was an error message, this
    // exits the program with an exit code of 255, otherwise it exits with a zero exit code.

    if (message)
        fprintf (stderr, "%sftimecomp: Error: %s\n", (printUsage ? "\n" : ""), message);

    if (!message || printUsage) {
        puts (usage);
        puts (version);
    }

    exit (message ? 255 : 0);
}


//--------------------------------------------------------------------------------------------------
time_t GetModTime (const char *filename, const Params& params) {
    // This function returns the modification time of the given file. If the global
    // handleMissingFiles flag is set, then missing files return a time of 0.

    struct _stat stat;

    if (0 == _stat(filename, &stat))
        return stat.st_mtime;

    if (params.missingIsOld)
        return 0;

    char errMessage[1024];
    sprintf_s (errMessage, "Couldn't get status of \"%s\".", filename);
    errorExit (errMessage);

    return 0;
}


//--------------------------------------------------------------------------------------------------
void processParameters (int argc, char *argv[], Params& params) {
    // Process the command-line options.

    auto fileCount = 0;        // Count of filenames given so far.
    char errMessage[1024];     // Buffer for error messages.

    for (auto argi = 1;  argi < argc;  ++argi) {

        auto c0 = argv[argi][0];
        auto c1 = argv[argi][1];

        // Handle Windows "/?" or "/H" or "/h" options.
        if (c0 == '/' && (c1 == '?' || c1 == 'h' || c1 == 'H'))
            errorExit (nullptr, usage);

        if (c0 != '-') {
            // Handle file names (non-switches).
            ++fileCount;
            if (fileCount == 1)
                params.fileName1 = argv[argi];
            else if (fileCount == 2)
                params.fileName2 = argv[argi];
            continue;
        } else if (c1 != '-') {
            // Single-dash options
            switch (toupper(c1)) {
                case '?':
                case 'H':
                    errorExit (nullptr, usage);
                    break;

                case 'M':
                    params.missingIsOld = true;
                    break;

                case 'N':
                    params.printNewer = true;
                    break;

                case 'O':
                    params.printOlder = true;
                    break;

                default:
                    sprintf_s (errMessage, "Unrecognized command option (%s).", argv[argi]);
                    errorExit (errMessage, true);
                    break;
            }
        } else {
            // Double-dash options

            auto option = argv[argi] + 2;
            if (strEqualIgnoreCase(option, "help"))
                errorExit (nullptr, usage);
            else if (strEqualIgnoreCase(option, "missing-ok"))
                params.missingIsOld = true;
            else if (strEqualIgnoreCase(option, "print-newer"))
                params.printNewer = true;
            else if (strEqualIgnoreCase(option, "print-older"))
                params.printOlder = true;
            else if (strEqualIgnoreCase(option, "version")) {
                puts(version);
                exit(0);
            } else {
                sprintf_s (errMessage, "Unrecognized command option (%s).", argv[argi]);
                errorExit (errMessage, true);
            }
        }
    }

    // Ensure that we got at exactly two files to compare.
    if (fileCount != 2)
        errorExit ("Expected exactly two file names.", true);

    if (params.printNewer && params.printOlder)
        errorExit ("Cannot specify both --print-newer and --print-older.", true);
}


//--------------------------------------------------------------------------------------------------
int main (int argc, char *argv[])
{
    Params params;
    processParameters (argc, argv, params);

    time_t time1 = GetModTime (params.fileName1, params);
    time_t time2 = GetModTime (params.fileName2, params);

    char* printName { nullptr };
    int   retCode = (time1 == time2) ? 0 : ((time1 > time2) ? 1 : 2);

    if (retCode == 1) {
        // File 1 is newer
        printName = params.printNewer ? params.fileName1 : (params.printOlder ? params.fileName2 : nullptr);
    } else if (retCode == 2) {
        // File 2 is newer
        printName = params.printNewer ? params.fileName2 : (params.printOlder ? params.fileName1 : nullptr);
    }

    if (printName) puts(printName);

    return retCode;
}

ftimecomp
====================================================================================================

A file modification time comparison tool for the Windows command line.

```
ftimecomp: ftimecomp: Compare the modification times of two files.
version:   v2.1.0-beta, https://github.com/hollasch/ftimecomp/
usage:     ftimecomp [-h|--help] [-m|--handle-missing] <file1> <file2>

    This tool examines the modification times of file1 and file2. It returns 1
    if file1 is newer than file2, 2 if file2 is newer than file1, and 0 if both
    files have the same modification times.

    -h, --help
        Print help information.

    -m, --handle-missing
        With this switch, a missing file is considered to be older than any
        existing file. If both files are missing, they compare the same.
```

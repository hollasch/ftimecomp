ftimecomp
====================================================================================================

A file modification time comparison tool for the Windows command line.

```
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

ftimecomp 2.2.0-alpha.5 | 2021-04-22 | https://github.com/hollasch/ftimecomp
```

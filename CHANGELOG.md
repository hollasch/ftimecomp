`ftimecomp` — A file modification time comparison tool for the Windows command line
===================================================================================

## v2.1.0-beta  (*In Progress*)
  - New `--handle-missing` option.
  - Supports `-h`, `--help`, `-?`, and `/?` switches to print usage information.
  - Unicode support in progress.

## v2.0.0  (2017-04-17)
  - Converted to Visual Studio project from original makefile
  - Now returns 1 if file1 newer, 2 if file2 newer, else 0 if same timestamp
  - First release on GitHub

## v1.0.0  (2003-07-24)
  - Original version
  - Returns 0 if file1 is newer than file2, otherwise 1

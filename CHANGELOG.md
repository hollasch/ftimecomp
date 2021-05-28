CHANGE LOG - `ftimecomp`
================================================================================

--------------------------------------------------------------------------------
# v2.2.0  (In Progress)

Among other things, converted the project build to use CMake.

### Added
  - `--version` command option

### Changed
  - Reformatted help output, fixed some typos

--------------------------------------------------------------------------------
# v2.1.1  (2018-06-24)

### Changed
  - Usage information now prints to stdout instead of stderr.


--------------------------------------------------------------------------------
# v2.1.0  (2018-06-10)

### Added
  - New `-m/--missing-ok` option.
  - New `-n/--print-newer` option.
  - New `-o/--print-older` option.
  - Supports `-h`, `--help`, `-?`, and `/?` switches to print usage information.


--------------------------------------------------------------------------------
# v2.0.0  (2017-04-17)

### Added
  - Now returns 1 if file1 newer, 2 if file2 newer, else 0 if same timestamp

### Changed
  - Converted to Visual Studio project from original makefile
  - First release on GitHub


--------------------------------------------------------------------------------
# v1.0.0  (2003-07-24)

### Added
  - Original version
  - Returns 0 if file1 is newer than file2, otherwise 1

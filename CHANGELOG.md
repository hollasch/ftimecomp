CHANGE LOG - `ftimecomp`
===================================================================================

Unreleased  (In Progress)
----------------------------------------------------------------------------------------------------
### Added
  - New `-m/--missing-ok` option.
  - New `-n/--print-newer` option.
  - New `-o/--print-older` option.
  - Supports `-h`, `--help`, `-?`, and `/?` switches to print usage information.


v2.0.0  (2017-04-17)
----------------------------------------------------------------------------------------------------
### Added
  - Now returns 1 if file1 newer, 2 if file2 newer, else 0 if same timestamp

### Changed
  - Converted to Visual Studio project from original makefile
  - First release on GitHub


v1.0.0  (2003-07-24)
----------------------------------------------------------------------------------------------------
### Added
  - Original version
  - Returns 0 if file1 is newer than file2, otherwise 1

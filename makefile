
ccopts = /Ox /W4 /nologo

help::
	@echo Make Targets:
	@echo.
	@echo all ......... ftimecomp + test
	@echo ftimecomp ... Make ftimecomp.exe
	@echo clean ....... Delete intermediate files
	@echo clobber ..... Delete all generated files
	@echo fresh ....... Clobber + all
	@echo.

all: ftimecomp

ftimecomp: ftimecomp.exe

ftimecomp.exe: ftimecomp.cpp
	cl $(ccopts) ftimecomp.cpp

clean:
	del 2>nul *.obj

clobber: clean
        del 2>nul *.exe

fresh: clobber all

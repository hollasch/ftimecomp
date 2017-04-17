
ccopts = /Ox /W4 /nologo

help::
	@echo Make Targets:
	@echo.
	@echo all ....... newer + test
	@echo newer ..... Make newer.exe
	@echo clean ..... Delete intermediate files
	@echo clobber ... Delete all generated files
	@echo fresh ..... Clobber + all
	@echo.

all: newer

newer: newer.exe

newer.exe: newer.cpp
	cl $(ccopts) newer.cpp

clean:
	del 2>nul *.obj

clobber: clean
        del 2>nul *.exe

fresh: clobber all

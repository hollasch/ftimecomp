!include public.mk

shareloc=\\TKFilToolbox\tools\22254

share: all clean
	-rmdir /s /q $(shareloc)
	mkdir $(shareloc)
	copy newer.*      $(shareloc)
	copy public.mk    $(shareloc)\makefile

help::
	@echo share ..... Propagate to toolbox sharepoint

#
#             LUFA Library
#     Copyright (C) Dean Camera, 2012.
#
#  dean [at] fourwalledcubicle [dot] com
#           www.lufa-lib.org
#

# Makefile to build the LUFA library, projects and demos.

# Call with "make all" to rebuild everything, "make clean" to clean everything,
# "make clean_list" to remove all intermediatary files but preserve any binaries,
# "make doxygen" to document everything with Doxygen (if installed) and
# "make clean_doxygen" to remove generated Doxygen documentation from everything.

all:
%:
	@echo Executing \"make $@\" on all LUFA library elements.
	@echo
	$(MAKE) -C LUFA $@ 
	$(MAKE) -C Demos $@
	$(MAKE) -C Projects $@
	$(MAKE) -C Bootloaders $@
	@echo
	@echo LUFA \"make $@\" operation complete.
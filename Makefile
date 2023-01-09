# Makefile to build class 'testing' for Pure Data.
# Needs Makefile.pdlibbuilder as helper makefile for platform-dependent build
# settings and rules.

# library name
PDDIR = /Users/roryjones/Desktop/ComputerMusic/Pd-0.53-0.app/Contents/Resources
lib.name = externals.howto.myTest

# input source file (class name == source file basename)
class.sources = arp.c

# all extra files to be included in binary distribution of the library
datafiles =

# include Makefile.pdlibbuilder from submodule directory 'pd-lib-builder'
PDLIBBUILDER_DIR=../pd-lib-builder/
include $(PDLIBBUILDER_DIR)/Makefile.pdlibbuilder

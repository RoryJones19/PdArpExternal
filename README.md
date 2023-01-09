# PdArpExternal
Simple C external for a Pure Data arpeggiator object.

Source code is written in C, in file arp.c

Object code included in arp.o

Included my own Makefile which worked on my Mac (Intel 64bit).

Simple PD patch included to display arp functionality, takes midi input in one inlet, and requires one creation argument to select scale and arp pattern.

Better instructions for writing Makefile can be found here: https://github.com/pure-data/pd-lib-builder and information regarding system dependant naming convention can be found here: https://github.com/pure-data/externals-howto#library

Used external masterdoc for reference point almost exclusively https://github.com/pure-data/externals-howto.

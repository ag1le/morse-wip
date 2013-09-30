AUTOMAKE_OPTIONS = subdir-objects
ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
LIBS =  -lm
AM_CFLAGS = -ggdb

bin_PROGRAMS = morse
morse_SOURCES = src/autocr.c	src/initl.c   src/likhd.c  src/path.c\
				src/spdtr.c   src/trelis.c\
				src/bpfdet.c  src/inputl.c  src/model.c  \
				src/probp.c   src/sprob.c   src/trprob.c\
				src/kalfil.c  src/morse.c  src/proces.c  src/savep.c   \
				src/stats.c   src/xtrans.c\
				src/noise.c  src/ptrans.c src/transl.c
				
#				src/simsgi.c src/key.c  src/rcvr.c      

#dist_noinst_SCRIPTS = autogen.sh

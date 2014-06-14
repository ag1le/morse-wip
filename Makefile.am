SUBDIRS = src
GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always)
CFLAGS= -Wall -pedantic -DVERSION=\"$(GIT_VERSION)\"
CXXFLAGS = -DVERSION=\"$(GIT_VERSION)\"

#bin_PROGRAMS = bmorse

#AM_CXXFLAGS = $(INTI_CFLAGS)

#bmorse_SOURCES =   src/fftfilt.cxx  src/kalfil.cxx  src/model.cxx  src/probp.cxx\
#				   src/savep.cxx   src/sprob.cxx   src/trelis.cxx  src/xtrans.cxx \
#				   src/bmorse.cxx  src/fft.cxx src src/misc.cxx  src/initl.cxx src/noise.cxx\
#				   src/proces.cxx   src/trprob.cxx\
#				   src/likhd.cxx   src/path.cxx\
#				   src/ptrans.cxx  src/spdtr.cxx   src/transl.cxx  src/window.cxx 
				   
LIBS =  -lm -lsndfile -lfftw3


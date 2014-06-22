GIT_VERSION := $(shell git describe --abbrev=4 --dirty --always)
bin_PROGRAMS = bmorse
CFLAGS= -Wall -pedantic -DGVERSION=\"$(GIT_VERSION)\" 
CXXFLAGS = -DGVERSION=\"$(GIT_VERSION)\" -std=c++0x

#AM_CXXFLAGS = -I$(src)

bmorse_SOURCES =   fftfilt.cxx  kalfil.cxx  model.cxx  probp.cxx\
				   savep.cxx   sprob.cxx   trelis.cxx  xtrans.cxx \
				   bmorse.cxx  fft.cxx misc.cxx initl.cxx     noise.cxx\
				   proces.cxx  trprob.cxx\
				   likhd.cxx   path.cxx\
				   ptrans.cxx  spdtr.cxx   transl.cxx  window.cxx\
				   bmorse.h  complex.h  config.h  fftfilt.h  fft.h  misc.h  window.h

				   
				   
LIBS =  -lm -lsndfile -lfftw3


// ----------------------------------------------------------------------------
// morse.h --  morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Morse.  

// Morse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Morse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Morse.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

typedef long int integer;
typedef unsigned long int uinteger;
typedef float real;
typedef double doublereal;
typedef int ftnlen;

extern int rcvr_(real *, real *);
extern int noise_(double, real *, real *);
extern  int initl_(void);
extern  int stats_(real *, real *, real *, integer *, real *, real *, real *, real *, integer *);
extern  int bpfdet_(real *, real *);
extern  int simsgi_(real *, real *);
extern int proces_(real *z, real *rn, integer *xhat, real *px, integer *elmhat, real *spdhat, integer *imax, real *pmax);
extern  int inputl_(void);
extern int transl_(int *ltr);
extern int trelis_(integer *isave, integer *pathsv, integer *lambda, integer *imax, integer *ipmax);


extern int probp_(real *, real *, integer *, real *);
extern int  sprob_(real *, integer *, integer *, real *, integer *, real *, real *);
extern int trprob_(integer *, integer *, real *, integer *, real *);
extern int savep_(real *, integer *, integer *, integer *, integer *, real *, integer *, integer *, real *, integer *, integer *, real *);
extern int likhd_(real *, real *, integer *, integer *, real *, integer *, real *, real *);
extern int path_(integer *, integer *, real *, integer *, integer *, real *, integer *);
extern doublereal spdtr_(integer *, integer *, integer *, integer *);

#define FSAMPLE 4000.0			// Sampling Frequency  FLDIGI=8000   MORSE.M =4000
#define DECIMATE  20			// Decimation     FLDIGI=40    MORSE.M=20 
#define SAMPLEDURATION  (1000. * DECIMATE) / FSAMPLE	// 1000*DECIMATE / FSAMPLE SHOULD BE  5 msec
#define NDELAY  200				// 200 SAMPLES * 5 msec = 1000 msec decoding delay 

#define TRUE 	1 
#define FALSE 	0 
typedef struct
{	int print_variables ;
	int print_symbols; 
	int process_textfile;
	int print_text;
	int print_xplot;
	int width, speclen ;
	double sample_duration; 
	double sample_rate; 
} PARAMS ;

extern PARAMS params;


/* Common Block Declarations */
struct BLKSPD {
    real rtrans[10]	/* was [5][2] */;
    integer mempr[36]	/* was [6][6] */;
} blkspd;

struct BLKRAT {
    integer memdel[36]	/* was [6][6] */;
} blkrat;

struct BLKLAM {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam;


struct BLKS {
    integer isx[6];
} blks;

struct BLKELM {
    real elemtr[96]	/* was [16][6] */;
} blkelm;

struct BLKMEM {
    integer memfcn[2400]	/* was [400][6] */;
} blkmem;


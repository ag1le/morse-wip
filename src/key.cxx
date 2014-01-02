// ----------------------------------------------------------------------------
// key.c --  bayesian morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Bayesian Morse code decoder   

// bmorse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bmorse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bmorse.  If not, see <http://www.gnu.org/licenses/>.
// ---------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Common Block Declarations */

struct blkend_1_ {
    integer iend;
};

#define blkend_1 (*(struct blkend_1_ *) &blkend_)

struct {
    real tau;
} blk1_;

#define blk1_1 blk1_

struct {
    real dmean, xdur, esep[6], edev[6];
} blk6_;

#define blk6_1 blk6_

struct {
    integer itext[200];
} blktxt_;

#define blktxt_1 blktxt_

/* Initialized data */

struct {
    integer e_1;
    } blkend_ = { 0 };


/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int key_(real *dur, real *x)
{
    /* Initialized data */

    static integer ltr = 1;
    static integer nelm = 0;
    static integer n = 0;
    static integer nltr = 1;
    static integer morse[400]  =  {
		1,3,2,0,0,0,0,0,0,0, 2,3,1,3,1,3,1,0,0,0, 2,3,1,3,2,3,1,0,0,0, 2,3,1,3,1,0,0,0,0,0,	// ABCD
		1,0,0,0,0,0,0,0,0,0, 1,3,1,3,2,3,1,0,0,0, 2,3,2,3,1,0,0,0,0,0, 1,3,1,3,1,3,1,0,0,0, // EFGH
		1,3,1,0,0,0,0,0,0,0, 1,3,2,3,2,3,2,0,0,0, 2,3,1,3,2,0,0,0,0,0, 1,3,2,3,1,3,1,0,0,0, // IJKL
		2,3,2,0,0,0,0,0,0,0, 2,3,1,0,0,0,0,0,0,0, 2,3,2,3,2,0,0,0,0,0, 1,3,2,3,2,3,1,0,0,0, // MNOP
		2,3,2,3,1,3,2,0,0,0, 1,3,2,3,1,0,0,0,0,0, 1,3,1,3,1,0,0,0,0,0, 2,0,0,0,0,0,0,0,0,0, // QRST
		1,3,1,3,2,0,0,0,0,0, 1,3,1,3,1,3,2,0,0,0, 1,3,2,3,2,0,0,0,0,0, 2,3,1,3,1,3,2,0,0,0, // UVWX
		2,3,1,3,2,3,2,0,0,0, 2,3,2,3,1,3,1,0,0,0, 1,3,2,3,2,3,2,3,2,0, 1,3,1,3,2,3,2,3,2,0, // YZ12
		1,3,1,3,1,3,2,3,2,0, 1,3,1,3,1,3,1,3,2,0, 1,3,1,3,1,3,1,3,1,0, 2,3,1,3,1,3,1,3,1,0, // 3456
		2,3,2,3,1,3,1,3,1,0, 2,3,2,3,2,3,1,3,1,0, 2,3,2,3,2,3,2,3,1,0, 2,3,2,3,2,3,2,3,2,0, // 7890
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 };


	// 6 morse symbols:  1=dot(.) 2=dash(-) 3=element space(^)  4=char space (~) 5=word space(W) 6=pause(P)
	    
    static integer ielm = 1;
    static struct {
	char e_1[24];
	integer e_2;
	} equiv_22 = { {'.', ' ', ' ', ' ', '-', ' ', ' ', ' ', '^', ' ', ' ',
		 ' ', 'C', ' ', ' ', ' ', 'W', ' ', ' ', ' ', 'P', ' ', ' ', 
		' '}, 0 };

#define isymbl ((integer *)&equiv_22)


    /* Format strings */
    static char fmt_90[] = "(1x,\002END OF RUN; INPUT DATA WAS:\002)";
    static char fmt_105[] = "(/,1x,50a1)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(), do_fio(integer *, char *, ftnlen), 
	    s_rsfe(cilist *), e_rsfe();

    /* Local variables */
    static integer k, l;
    static real y;
    static integer k1, k2;
    static real xm, beta, wait;
    static integer iout[500];
    static real xsigm;

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 6, 0, fmt_90, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_105, 0 };
    static cilist io___18 = { 0, 5, 0, fmt_105, 0 };


/* 	CHARACTER(500) IOUT */
/* 	CHARACTER*500 IOUT */
/* 	CHARACTER*6 ISYMBL */
/* 	CHARACTER(LEN=6), PARAMETER :: ISYMBL = '.-^CWP' */
/* 	REPLACE WITH THIS: CHARACTER(LEN=6), PARAMETER :: ISYMBL = '.-^CWP' */
    beta = (float)1e3 * blk1_1.tau * *dur;
    if (beta < blk6_1.xdur) {
	goto L200;
    }
    ++nelm;
    ielm = morse[nelm + ltr * 10 - 11];
    if (ielm != 0) {
	goto L100;
    }
    nelm = 0;
/* 	Y=RAND(IK) */
    ielm = 4;
    if (y > (float).9) {
	ielm = 5;
    }
    if (y <= (float).9 && y > (float).3) {
	ielm = 6;
    }
/* 	Y=RAND(IK) */
/* 	Y=35*(Y-0.001)+1. */
/* 	IY=Y */
/* 	LTR=IY+1 */
    ++ltr;
    if (ltr >= 38) {
	ltr = 1;
    }
    goto L100;
    ++nltr;
    ltr = blktxt_1.itext[nltr - 1];
    if (ltr == 0) {
	ielm = 4;
    }
    if (ltr == 37) {
	ielm = 5;
    }
    if (ltr == 38) {
	ielm = 6;
    }
    ++nltr;
    ltr = blktxt_1.itext[nltr - 1];
L100:
    ++n;
/* 	IOUTP(N:N+1) = ISYMBL(IELM:IELM+1) */
    iout[n - 1] = isymbl[ielm - 1];
    if (n < 300) {
	goto L110;
    }
    n = 0;
    nltr = 0;
    blkend_1.iend = 1;
    s_wsfe(&io___12);
    e_wsfe();
    for (k = 1; k <= 10; ++k) {
	k1 = (k - 1) * 50 + 1;
	k2 = k * 50;
	s_wsfe(&io___16);
	i__1 = k2;
	for (l = k1; l <= i__1; ++l) {
	    do_fio(&c__1, (char *)&iout[l - 1], (ftnlen)sizeof(integer));
	}
	e_wsfe();
/* L10: */
    }
    s_rsfe(&io___18);
    do_fio(&c__1, (char *)&wait, (ftnlen)sizeof(real));
    e_rsfe();
L110:
    xm = blk6_1.esep[ielm - 1] * blk6_1.dmean;
    xsigm = blk6_1.edev[ielm - 1] * blk6_1.dmean;
/* 	Y=RAND(IK) */
/* 	Y=2.*(Y-.5) */
/* 	XDUR=XM+Y+XSIGM */
    blk6_1.xdur = xm + xsigm;
    if (blk6_1.xdur < (float)20.) {
	blk6_1.xdur = (float)20.;
    }
/* 	MARK x=1  SPACE x=0 */
    *x = (float)1.;
    if (ielm >= 3) {
	*x = (float)0.;
    }
L200:
/* 	PRINT 300, NELM, LTR, IELM, XM, BETA, XDUR */
/* 300	FORMAT('KEY: ',3(I3,2X),3(F8.2,2X)) */
    return 0;
} /* key_ */

#undef isymbl


#ifdef __cplusplus
	}
#endif

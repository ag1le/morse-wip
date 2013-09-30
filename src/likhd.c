/* likhd.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

//#include "f2c.h"
#include "morse.h"

/* Common Block Declarations */

struct {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam_;

#define blklam_1 blklam_

struct {
    integer isx[6];
} blks_;

#define blks_1 blks_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int likhd_(real *z, real *rn, integer *ip, integer *lambda,
	 real *dur, integer *ilrate, real *p, real *lkhd)
{
 
    /* Local variables */
    static integer i, j, k, n;
    static real pin;
    static integer ilx, ixs;
    static real lkhdj;
    static integer kelem;
    extern /* Subroutine */ int kalfil_(real *, integer *, real *, integer *, 
	    integer *, integer *, integer *, integer *, real *, integer *, 
	    real *, real *);
    static integer israte;



/* 	THIS SUBROUTINE CALCULATES,FOR EACH PATH */
/* 	EXTENSION TO STATE N, THE LIKELIHOOD OF THAT */
/* 	TRANSITION GIVEN THE MEASUREMENTZ. IT USES */
/* 	AN ARRAY OF LINEAR (KALMAN) FILTERS TO DO SO. */

/* 	VARIABLES: */
/* 	Z- 	INPUT MEASUREMENT */
/* 	RN-	INPUT NOISE POWER ESTIMATE */
/* 	IP-	INPUT SAVED PATH IDENTITY */
/* 	LAMBDA-	INPUT SAVED LTR STATE IDENTITY */
/* 	DUR-	INPUT SAVED DURATION OF ELEMENT ON PATH IP */
/* 	ILRATE-	INPUT SAVED DATA RATE (SPEED) */
/* 	P-	INPUT TRANSITION PROBABILITIES */
/* 	LKHD-	OUTPUT COMPUTED LIKELIHOODS FOR EACH TRANS */

/*  SUBROUTINES USED: */
/* 	KALFIL-KALMAN FILTER FOR EACH NEW PATH */

/*   OBTAIN SAVED KEYSTATE: */
    /* Parameter adjustments */
    --lkhd;
    p -= 26;

    /* Function Body */
    if (*lambda == 0) {
	goto L200;
    }
    kelem = blklam_1.ilami[blklam_1.ielmst[*lambda - 1] - 1];
    ilx = blklam_1.ilamx[kelem - 1];
/* 	FOR EACH STATE: */
    for (k = 1; k <= 6; ++k) {
		for (i = 1; i <= 5; ++i) {
/* 	OBTAIN KEYSTATE, RATE STATE, STATE N, NEW NODE: */
			ixs = blks_1.isx[k - 1];
			israte = i;
			n = (i - 1) * 6 + k;
			j = (*ip - 1) * 30 + n;
			pin = p[*ip + n * 25];
/* 	COMPUTE AND STORE LIKELIHOOD: */
			kalfil_(z, ip, rn, &ilx, &ixs, &kelem, &j, &israte, dur, ilrate,&pin, &lkhdj);
			lkhd[j] = lkhdj;
			goto L100;
			if (pin <= 1e-6f) {
			goto L100;
			}
L100:
			;
		}
    }
L200:
    return 0;
} /* likhd_ */


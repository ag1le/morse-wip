/* trprob.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam_;

#define blklam_1 blklam_

/* Subroutine */ int trprob_(integer *ip, integer *lambda, real *dur, integer 
	*ilrate, real *p)
{
    static integer i__, k, n;
    static real pin[30];
    static integer kelm;
    static real psum, ptrx;
    static integer ielem, irate;
    extern /* Subroutine */ int ptrans_(integer *, integer *, integer *, 
	    integer *, real *, real *, real *, integer *);
    extern doublereal xtrans_(integer *, real *, integer *);


/* 		THIS SUBROUTINE COMPUTES THE TRANSITION PROBABILITY */
/* 		FROM SAVED PATH IP TO EACH STATE N AND STORES THE */
/* 		RESULT IN P(IP, N). */

/* 		VARIABLES: */
/* 		IP - 	INPUT SAVED PATH IDENTITY */
/* 		LAMBDA 	INPUT SAVED LTR STATE IDENTITY */
/* 		DUR - 	INPUT SAVED ELEMENT DURATION */
/* 		ILPATE 	INPUT SAVED DATA RATE IDENTITY */
/* 		P - 	OUTPUT TRANSITION PROBABILITY MATRIX */

/* 		THE FOLLOWING FUNCTION SUBROUTINES ARE USED: */
/* 		XTRANS 	RETURNS THE KEYSTATE TRANSITION PROBABILITY */
/* 	               	CONDITIONED ON ELEMENT TYPE AND DATA RATE */
/* 		PTRANS	RETURNS THE PATH-CONDITIONAL STATE TRANSITION PROB */
/* 	LOOK UP ELEMENT TYPE FOR LTR STATE LAMBDA: */
    /* Parameter adjustments */
    p -= 26;

    /* Function Body */
    if (*lambda != 0) {
	goto L20;
    }
    for (n = 1; n <= 30; ++n) {
	p[*ip + n * 25] = 0.f;
/* L10: */
    }
    goto L200;
L20:
    ielem = blklam_1.ilami[blklam_1.ielmst[*lambda - 1] - 1];
/* 	COMPUTE KEYSTATE TRANSITION PROBABILITY: */
    ptrx = xtrans_(&ielem, dur, ilrate);
/* 	FOR EACH STATE, COMPUTE STATE TRANSITION PROBABILITY: */
    psum = 0.f;
    for (k = 1; k <= 6; ++k) {
	for (i__ = 1; i__ <= 5; ++i__) {
	    n = (i__ - 1) * 6 + k;
	    kelm = k;
	    irate = i__;
	    ptrans_(&kelm, &irate, lambda, ilrate, &ptrx, &psum, pin, &n);
/* L100: */
	}
    }
    for (n = 1; n <= 30; ++n) {
	p[*ip + n * 25] = pin[n - 1] / psum;
/* L300: */
    }
L200:
    return 0;
} /* trprob_ */


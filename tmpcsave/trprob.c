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
#include "common.h"
#include <stdio.h>

//#define DEBUG 1 

/* Common Block Declarations */


int trprob_(integer ip, integer *lambda, real *dur, integer *ilrate, real p[][25])
{
    static integer i, k, n;
    static real pin[30];
    static integer kelm;
    static real psum, ptrx;
    static integer ielem, irate;
    extern int ptrans_(integer *, integer *, integer *, integer *, real *, real *, real *, integer *);
    extern doublereal xtrans_(integer *, real , integer *);


/* 		THIS SUBROUTINE COMPUTES THE TRANSITION PROBABILITY */
/* 		FROM SAVED PATH IP TO EACH STATE N AND STORES THE */
/* 		RESULT IN P(IP, N). */

/* 		VARIABLES: */
/* 		IP - 		INPUT SAVED PATH IDENTITY */
/* 		LAMBDA - 	INPUT SAVED LTR STATE IDENTITY */
/* 		DUR - 		INPUT SAVED ELEMENT DURATION */
/* 		ILPATE - 	INPUT SAVED DATA RATE IDENTITY */
/* 		P - 		OUTPUT TRANSITION PROBABILITY MATRIX */

/* 		THE FOLLOWING FUNCTION SUBROUTINES ARE USED: */
/* 		XTRANS - 	RETURNS THE KEYSTATE TRANSITION PROBABILITY */
/* 	              	 CONDITIONED ON ELEMENT TYPE AND DATA RATE */
/* 		PTRANS - 	RETURNS THE PATH-CONDITIONAL STATE TRANSITION PROB */

/* 	LOOK UP ELEMENT TYPE FOR LTR STATE LAMBDA: */

    if (*lambda == 0) {
		for (n = 0; n < 30; ++n) {
			p[n][ip] = 0.f;
		}
#ifdef DEBUG
printf("\nTRPROB: lambda:%d", *lambda);
#endif 
		return 0;
    }
    ielem = blklam.ilami[blklam.ielmst[*lambda - 1] - 1];

/* 	COMPUTE KEYSTATE TRANSITION PROBABILITY: */

    ptrx = xtrans_(&ielem, *dur, ilrate);

/* 	FOR EACH STATE, COMPUTE STATE TRANSITION PROBABILITY: */
    psum = 0.f;
    for (k = 0; k < 6; ++k) {		// ELEMENT STATE
		for (i = 0; i < 5; ++i) { 	// DATA RATE STATE 
			n = i*6 + k;
		    ptrans_(&k, &i, lambda, ilrate, &ptrx, &psum, pin, &n);
		}
    }
    for (n = 0; n < 30; ++n) {
		p[n][ip] = pin[n] / psum;
#ifdef DEBUG
printf("\nTRPROB: p[%2d][%2d]:%f pin[%2d]:%f psum:%f lambda:%d", n,ip, p[n][ip], n, pin[n], psum, *lambda);
#endif 
    }

L200:
    return 0;
} /* trprob_ */


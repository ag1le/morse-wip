/* probp.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Subroutine */ int probp_(real *p, real *pin, integer *isave, real *lkhd)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j, n, ni;
    static real pmax, psav[750], psum;


/* 		PROBP COMPUTES THE POSTERIOR PROBABILITY OF EACH NEW PATH */

/* 		VARIABLES: */
/* 		P-		INPUT: SAVED PROBS OF PRIOR PATHS */
/* 		OUTPUT:	COMPUTED POSTERIOR PROBS OF NEW PATHS */
/* 		PIN-		INPUT TRANSISTION PROBABILITIES */
/* 		LKHD-		INPUT LIKELIHOODS OF EACH TRANSTION */
/* 		PSUM-		NORMALIZING CONSTANT (SUM OF P(J)) */

    /* Parameter adjustments */
    --lkhd;
    pin -= 26;
    --p;

    /* Function Body */
    pmax = (float)0.;
    psum = (float)0.;
/* 	FOR EACH SAVED PATH, EACH TRANSITION: */
    i__1 = *isave;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (n = 1; n <= 30; ++n) {
/* 		COMPUTE IDENTITY OF NEW PATH: */
	    j = (i__ - 1) * 30 + n;
/*      PRODUCT OF PROBS, ADD TO PSUM */
	    psav[j - 1] = p[i__] * pin[i__ + n * 25] * lkhd[j];
	    psum += psav[j - 1];
	    if (psav[j - 1] <= pmax) {
		goto L100;
	    }
	    pmax = psav[j - 1];
L100:
	    ;
	}
    }
/* 	NORMALIZE TO GET PROBABILITIES; SAVE: */
    ni = *isave * 30;
    i__1 = ni;
    for (j = 1; j <= i__1; ++j) {
	p[j] = psav[j - 1] / psum;
/* 	PRINT 50, J, P(J), PSAV(J), PMAX */
/* 50	FORMAT('PROBP:',I3,3(2x,F8.3)) */
/* L200: */
    }
    return 0;
} /* probp_ */

#ifdef __cplusplus
	}
#endif

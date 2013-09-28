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

#include "f2c.h"

/* Subroutine */ int probp_(real *p, real *pin, integer *isave, real *lkhd)
{
    /* System generated locals */
    integer i1;

    /* Local variables */
    static integer i, j, n, ni;
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
    pmax = 0.f;
    psum = 0.f;
/* 	FOR EACH SAVED PATH, EACH TRANSITION: */
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		for (n = 1; n <= 30; ++n) {
	/* 		COMPUTE IDENTITY OF NEW PATH: */
			j = (i - 1) * 30 + n;
	/*      PRODUCT OF PROBS, ADD TO PSUM */
			psav[j - 1] = p[i] * pin[i + n * 25] * lkhd[j];
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
    i1 = ni;
    for (j = 1; j <= i1; ++j) {
		p[j] = psav[j - 1] / psum;
	}
    return 0;
} /* probp_ */


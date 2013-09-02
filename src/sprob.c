/* sprob.f -- translated by f2c (version 20100827).
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

/* Subroutine */ int sprob_(real *p, integer *isave, integer *ilrsav, real *
	pelm, integer *khat, real *spdhat, real *px)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j, k, m, n;
    static real pselem[6];


/*    SPROB COMPUTES THE POSTERIOR PROBS OF THE ELEMENT */
/*    STATES, DATA RATE STATES, AND KEYSTATES BY SUMMING */
/*    OVER THE APPROPRIETE PATHS. */

/*    VARIABLE: */
/*    P-		INPUT PATH PROBABILITIES */
/*    ISAVE- 	NUMBER OF PATHS SAVED */
/*    PSELEM-	OUTPUT ELEMENT PROB */
/*    SPDHAT-	OUTPUT SPEED ESTIMATE (DATA RATE WPM) */
/*    PX- 	OUTPUT KEYSTATE PROBABILITY */

/* 	INITIALIZE: */
    /* Parameter adjustments */
    --ilrsav;
    --p;

    /* Function Body */
    *spdhat = 0.f;
    *px = 0.f;
/* 	FOR EACH STATE EXTENSION OF PATH M: */
/* 	OBTAIN ELEMENT STATE PROBS,KEYSTATE PROBS,SPEED EST: */
    for (k = 1; k <= 6; ++k) {
	pselem[k - 1] = 0.f;
	for (i__ = 1; i__ <= 5; ++i__) {
	    n = (i__ - 1) * 6 + k;
	    i__1 = *isave;
	    for (m = 1; m <= i__1; ++m) {
		j = (m - 1) * 30 + n;
		pselem[k - 1] += p[j];
		*spdhat += ilrsav[j] * p[j];
		if (k > 2) {
		    goto L100;
		}
		*px += p[j];
L100:
		;
	    }
	}
    }
    *pelm = 0.f;
    for (k = 1; k <= 6; ++k) {
	if (pselem[k - 1] < *pelm) {
	    goto L200;
	}
	*pelm = pselem[k - 1];
	*khat = k;
L200:
	;
    }
    return 0;
} /* sprob_ */

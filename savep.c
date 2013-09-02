/* savep.f -- translated by f2c (version 20100827).
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

/* Common Block Declarations */

struct {
    real ykkip[25], pkkip[25], ykksv[750], pkksv[750];
} blksv1_;

#define blksv1_1 blksv1_

/* Subroutine */ int savep_(real *p, integer *pathsv, integer *isave, integer 
	*imax, integer *lamsav, real *dursav, integer *ilrsav, integer *
	lambda, real *dur, integer *ilrate, integer *sort, real *pmax)
{
    /* Initialized data */

    static real popt = (float).9;

    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, j, k, n, ip, jsav, nsav;
    static real psav[25], psum;
    static integer iconv[25], ipsav, isavm1, nplus1;


/* 	THIS SUBROUTINE PERFORMS THE ALGORITM TO SAVE */
/* 	THE PATHS WITH HIGHEST POSTERIOR PROBABILITY. */
/* 	IT WILL SAVE A MINIMUM OF 7 PATHS (ONE FOR EACH */
/* 	ELEMENT STATE AND ONE ADDITIONAL NODE), AND */
/* 	A MAXIMUM OF 25 PATHS.  WITHIN THESE LIMITS, IT */
/* 	SAVED ONLY ENOUGH TO MAKE THE TOTAL SAVED PROBABILITY */
/* 	EQUAL TO POPT. */


/* 	ADDITIONALLY, IT RESORTS THE LAMBDA,DUR,AND ILRATE */
/* 	ARRAYS TO CORRESPOND TO THE SAVED NODES. */


/* 	VARIABLES: */
/* 		P-	INPUT PROBABILITY ARRAY OF NEW NODES */
/* 		PATHSV-	OUTPUT ARRAY OF THE PREVIOUS NODES TO */
/* 			WHICH THE SAVED NODES ARE CONNECTED. */
/* 		ISAVE-	INPUT: NO. OF PREVIOUS NODES SAVED */

/* 			OUPUT: NO. OF NODES SAVED AT CURRENT STAGE */
/* 		IMAX-	INDEX OF HIGHEST PROBABILITY NODE */
/* 		LAMSAV-	INPUT ARRAY OF LTR STATES AT EACH NEW NODE */
/* 		DURSAV-	INPUT ARRAY OF SAVED DURATIONS */
/* 		ILRSAV-	INPUT ARRAY OF SAVED RATES */
/* 		LAMBDA-	OUTPUT ARRAY OF SAVED LTR STATES, SORTED */

/* 			ACCORDING TO PROBABILITY */
/* 		DUR-	OUTPUT ARRAY OF SORTED DURATIONS */
/* 		ILRATE-	OUTPUT ARRAY OF SORTED RATES */


    /* Parameter adjustments */
    --sort;
    --ilrate;
    --dur;
    --lambda;
    --ilrsav;
    --dursav;
    --lamsav;
    --pathsv;
    --p;

    /* Function Body */
    nsav = 0;
    psum = (float)0.;
/* 	SELECT SIX HIGHEST PROB ELEMENT STATE NODES: */
    for (k = 1; k <= 6; ++k) {
	*pmax = (float)0.;
	i__1 = *isave;
	for (ip = 1; ip <= i__1; ++ip) {
	    for (i__ = 1; i__ <= 5; ++i__) {
		j = (ip - 1) * 30 + (i__ - 1) * 6 + k;
		if (p[j] < *pmax) {
		    goto L100;
		}
		*pmax = p[j];
		jsav = j;
		ipsav = ip;
L100:
		;
	    }
	}
/* 	IF FOLLOWING TWO LINES COMMENTED OUT WE GET NSAV = 7 */
	if (*pmax >= (float)1e-6) {
	    goto L150;
	}
	goto L200;
L150:
	++nsav;
	psum += *pmax;
	psav[nsav - 1] = *pmax;
	pathsv[nsav] = ipsav;
	sort[nsav] = jsav;
L200:
	;
    }
/* 	SELECT ENOUGH ADDITIONAL NODES TO MAKE TOTAL */
/* 	PROBABILITY SAVED EQUAL TO POPT, OR A MAX OF 25: */
L520:
    *pmax = (float)0.;
    i__1 = *isave;
    for (ip = 1; ip <= i__1; ++ip) {
	for (n = 1; n <= 30; ++n) {
	    j = (ip - 1) * 30 + n;
	    i__2 = nsav;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		if (j == sort[i__]) {
		    goto L500;
		}
/* L510: */
	    }
	    if (p[j] <= *pmax) {
		goto L500;
	    }
	    *pmax = p[j];
	    jsav = j;
	    ipsav = ip;
L500:
	    ;
	}
    }
    psum += *pmax;
    ++nsav;
    psav[nsav - 1] = *pmax;
    pathsv[nsav] = ipsav;
    sort[nsav] = jsav;
    if (psum >= popt) {
	goto L600;
    }
    if (nsav >= 25) {
	goto L600;
    }
    goto L520;
/* 	NEW ISAVE EQUALS NO. OF NODES SAVED: */
L600:
    *isave = nsav;
/* 	SORT THE SAVED ARRAYS TO OBTAIN THE ARRAYS */
/* 	TO BE USED FOR THE NEXT ITERATION: */
    i__1 = *isave;
    for (i__ = 1; i__ <= i__1; ++i__) {
	p[i__] = psav[i__ - 1] / psum;
	lambda[i__] = lamsav[sort[i__]];
	dur[i__] = dursav[sort[i__]];
	ilrate[i__] = ilrsav[sort[i__]];
	blksv1_1.ykkip[i__ - 1] = blksv1_1.ykksv[sort[i__] - 1];
	blksv1_1.pkkip[i__ - 1] = blksv1_1.pkksv[sort[i__] - 1];
/* 	PRINT 650, I, ILRATE(I), SORT(I), LAMBDA(I), P(I), DUR(I), */
/*     &YKKIP(I), PKKIP(I) */
/* 650	FORMAT('SAVEP:',4(I4,1X), 4(F10.4,1X)) */
/* L700: */
    }
    i__1 = *isave;
    for (i__ = 1; i__ <= i__1; ++i__) {
	iconv[i__ - 1] = 1;
/* L790: */
    }
    isavm1 = *isave - 1;
    i__1 = isavm1;
    for (n = 1; n <= i__1; ++n) {
	if (iconv[n - 1] == 0) {
	    goto L800;
	}
	nplus1 = n + 1;
	i__2 = *isave;
	for (k = nplus1; k <= i__2; ++k) {
	    if (iconv[k - 1] == 0) {
		goto L810;
	    }
	    if (ilrate[k] != ilrate[n]) {
		goto L810;
	    }
	    if (dur[k] != dur[n]) {
		goto L810;
	    }
	    if (lambda[k] != lambda[n]) {
		goto L810;
	    }
	    iconv[k - 1] = 0;
L810:
	    ;
	}
L800:
	;
    }
    psum = (float)0.;
    n = 1;
    i__1 = *isave;
    for (i__ = 2; i__ <= i__1; ++i__) {
	if (iconv[i__ - 1] == 0) {
	    goto L900;
	}
	++n;
	lambda[n] = lambda[i__];
	dur[n] = dur[i__];
	ilrate[n] = ilrate[i__];
	blksv1_1.ykkip[n - 1] = blksv1_1.ykkip[i__ - 1];
	blksv1_1.pkkip[n - 1] = blksv1_1.pkkip[i__ - 1];
	pathsv[n] = pathsv[i__];
	sort[n] = sort[i__];
	p[n] = p[i__];
	psum += p[n];
L900:
	;
    }
/* 	ALSO OBTAIN HIGHEST PROBABILITY NODE: */
    *isave = n;
    *pmax = (float)0.;
    i__1 = *isave;
    for (i__ = 1; i__ <= i__1; ++i__) {
	p[i__] /= psum;
	if (p[i__] <= *pmax) {
	    goto L950;
	}
	*pmax = p[i__];
	*imax = i__;
L950:
	;
    }
    return 0;
} /* savep_ */

#ifdef __cplusplus
	}
#endif

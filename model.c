/* model.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static doublereal c_b5 = 10.;

/* Subroutine */ int model_(real *dur, integer *ielm, integer *ilr, integer *
	isr, integer *ixs, real *phi, real *qa, real *hz)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static real r1, bauds, xsamp;


/* 	THIS SUBROUTINE COMPUTES THE PARAMETERS OF THE */
/* 	OBSERVATION STATE TRANSITION MATRIX PHI, THE */
/* 	MEASUREMENT MATRIX, AND THE COVARIANCES. */

/* 	VARIABLES: */
/* 		DUR-	INPUT ELEMENT DURATION */
/* 		IELM-	INPUT ELEMENT TYPE */
/* 		ILR-	INPUT SAVED RATE */
/* 		ISR-	INPUT RATE OF NEW STATE */
/* 		IXS-	INPUT KEYSTATE OF NEW STATE */

/* 		PHI-	OUTPUT STATE TRANSITION MATRIX ENTRY FOR */
/* 			SIGNAL AMPLITUDE STATE */
/* 		QA-	OUTPUT COVARIANCE FOR AMPLITUDE STATE */
/* 		HZ-	OUTPUT MEASUREMENT MATRIX VALUE */

/* 	COMPUTE MEASUREMENT COEFFICIENT: */
    *hz = (real) (*ixs);
/* 	COMPUTE PHI AND AMPLITUDE STATE VARIANCE (Q): */
    r1 = (float)1200. / *ilr;
    bauds = *dur / r1;
    if (bauds >= (float)14.) {
	bauds = (float)14.;
    }
    if (*ielm >= 3) {
	goto L100;
    }
    *qa = (float)1e-4;
    *phi = (float)1.;
    goto L300;
L100:
    if (*ixs == 0) {
	goto L200;
    }
    *phi = (float)1.;
    *qa = exp((bauds - (float)14.) * (float).6) * (float).15;
    *qa += bauds * (float).01 * exp(((float)1. - bauds) * (float).2);
    goto L300;
L200:
    xsamp = r1 * (float)22.4;
    d__1 = (doublereal) (-2 / xsamp);
    *phi = pow_dd(&c_b5, &d__1);
    if (bauds >= (float)14.) {
	*phi = (float)1.;
    }
    *qa = (float)0.;
L300:
    return 0;
} /* model_ */

#ifdef __cplusplus
	}
#endif

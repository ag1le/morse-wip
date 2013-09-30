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

//#include "f2c.h"
#include <math.h>
#include "morse.h"




/* Table of constant values */

static doublereal c_b5 = 10.;

/* Subroutine */ int model_(real *dur, integer *ielm, integer *ilr, integer *
	isr, integer *ixs, real *phi, real *qa, real *hz)
{
    /* System generated locals */
    doublereal d1;

    /* Builtin functions */
  //  double exp(doublereal), pow_dd(doublereal *, doublereal *);

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
    r1 = 1200.f / *ilr;
    bauds = *dur / r1;
    if (bauds >= 14.f) {
	bauds = 14.f;
    }
    if (*ielm >= 3) {
	goto L100;
    }
    *qa = 1e-4f;
    *phi = 1.f;
    goto L300;
L100:
    if (*ixs == 0) {
	goto L200;
    }
    *phi = 1.f;
    *qa = exp((bauds - 14.f) * .6f) * .15f;
    *qa += bauds * .01f * exp((1.f - bauds) * .2f);
    goto L300;
L200:
    xsamp = r1 * 22.4f;
    d1 = (doublereal) (-2 / xsamp);
//    *phi = pow_dd(&c_b5, &d1);
    *phi = pow(10.0, d1);
    if (bauds >= 14.f) {
	*phi = 1.f;
    }
    *qa = 0.f;
L300:
    return 0;
} /* model_ */


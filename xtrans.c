/* xtrans.f -- translated by f2c (version 20100827).
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

doublereal xtrans_(integer *ielem, real *d0, integer *irate)
{
    /* Initialized data */

    static integer kimap[6] = { 1,3,1,3,7,14 };
    static real aparm[3] = { (float)3.,(float)1.5,(float)1. };

    /* System generated locals */
    real ret_val;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static real b0, b1, p0, p1, alpha;
    static integer mscale;
    static real rscale;

/* 	THIS FUNCTION IMPLEMENTS THE CALCULATION OF KEYSTATE */
/* 	TRANSITION PROBABILITY, CONDITIONED ON ELEMENT TYPE, */
/* 	CURRENT DURATION, AND DATA RATE. */
/* 	VARIABLES: */
/* 	IELEM- 	INPUT CURRENT ELEMENT TYPE */
/* 	D0- 	INPUT CURRENT ELEMENT DURATION */
/* 	IRATE - INPUT CURRENT DATA RATE */

/* 	TABLES IN COMMON CONTAIN DENSITY PARMS FOR EACH ELEMENT TYPE, DATA RATE. */

/* 	SCALE DURATION AND OBTAIN DENSITY PARAMETER: */

    mscale = kimap[(0 + (0 + (*ielem - 1 << 2))) / 4];
    rscale = (float)1200. / *irate;
    b0 = *d0 / (mscale * rscale);
    b1 = (*d0 + (float)5.) / (mscale * rscale);
    if (*ielem == 6) {
	goto L20;
    }
    if (*ielem == 5) {
	goto L10;
    }
    alpha = mscale * aparm[0];
    goto L100;
L10:
    alpha = aparm[1] * (float)7.;
    goto L100;
L20:
    alpha = aparm[2] * (float)14.;
L100:
    if (b1 <= (float)1.) {
	goto L200;
    }
    if (b0 < (float)1. && b1 > (float)1.) {
	goto L300;
    }
    ret_val = exp(-alpha * (b1 - b0));
    goto L400;
L200:
    p1 = (float)1. - exp(alpha * (b1 - (float)1.)) * (float).5;
    p0 = (float)1. - exp(alpha * (b0 - (float)1.)) * (float).5;
    ret_val = p1 / p0;
    goto L400;
L300:
    p1 = exp(-alpha * (b1 - (float)1.)) * (float)-.5;
    p0 = (float)1. - exp(alpha * (b0 - (float)1.)) * (float).5;
    ret_val = p1 / p0;
L400:
    return ret_val;
} /* xtrans_ */

#ifdef __cplusplus
	}
#endif

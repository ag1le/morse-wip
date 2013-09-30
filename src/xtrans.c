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


//#include "f2c.h"
#include "morse.h"

doublereal xtrans_(integer *ielem, real *d0, integer *irate)
{
    /* Initialized data */

    static integer kimap[6] = { 1,3,1,3,7,14 };
    static real aparm[3] = { 3.f,1.5f,1.f };

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
    rscale = 1200.f / *irate;
    b0 = *d0 / (mscale * rscale);
    b1 = (*d0 + 5.f) / (mscale * rscale);
    
    switch (*ielem) {
    case 6:
	    alpha = aparm[2] * 14.f;
	    break;
    case 5:
	    alpha = aparm[1] * 7.f;    
	    break;
    default:
	    alpha = mscale * aparm[0];
    }

    if (b1 <= 1.f) {
		p1 = 1.f - exp(alpha * (b1 - 1.f)) * .5f;
		p0 = 1.f - exp(alpha * (b0 - 1.f)) * .5f;
		ret_val = p1 / p0;
	    return ret_val;
    }
    if (b0 < 1.f && b1 > 1.f) {
		p1 = exp(-alpha * (b1 - 1.f)) * -.5f;
		p0 = 1.f - exp(alpha * (b0 - 1.f)) * .5f;
		ret_val = p1 / p0;
	    return ret_val;
    }

    ret_val = exp(-alpha * (b1 - b0));
    return ret_val;
} /* xtrans_ */


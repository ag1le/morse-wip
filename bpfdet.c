/* bpfdet.f -- translated by f2c (version 20100827).
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

/* Subroutine */ int bpfdet_(real *zin, real *z__)
{
    /* Initialized data */

    static real a[4] = { (float)3.0051e-5,(float)2.9507982,(float)2.90396345,(
	    float)-.953135172 };
    static real ck1 = (float)1.37158;
    static real ck2 = (float).9409;
    static real cg = (float).015;
    static real c1 = (float)1.2726;
    static real c2 = (float).81;
    static real c__ = (float).19;

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static real w1, w2, w3, x3, x2, x1, y3, y2, y1, y0, z3, z2, z1, zbpf, 
	    xdet;


/*       THIS SUBROUTINE IMPLEMENTS THE BANDPASS FILTER AND */
/*       ENVELOPE DETECTOR FUNCTIONS. THE BPF IS A SIMPLE CASCADE */
/*       OF TWO 2-POLE DIGITAL RESONATORS AT A CENTER FREQ OF */
/*       1000 HZ. THE LPF OF THE ENVELOPE DETECTOR IS A */
/*       THREE - POLE CHEBYSCHEV 100 HZ LPF. */


/* 	OFF IS TWO 2 - POLE RESONATORS : */
    w3 = w2;
    w2 = w1;
    w1 = c1 * w2 - c2 * w3 + c__ * *zin;
    x3 = x2;
    x2 = x1;
    x1 = ck1 * x2 - ck2 * x3 + cg * w1;
    zbpf = x1;
/* 	ENVELOPE DETECTOR (SQUARE-LAW): */
/* 		sQUARE- */
/* Computing 2nd power */
    r__1 = zbpf;
    xdet = sqrt(r__1 * r__1);
/* 	LOW-PASS FILTER- */
    y3 = y2;
    y2 = y1;
    y1 = y0;
    y0 = xdet * a[0];
    z3 = z2;
    z2 = z1;
    z1 = *z__;
    *z__ = y0 + (y1 + y2) * (float)3. + y3;
    *z__ = *z__ + a[1] * z1 - a[2] * z2 - a[3] * 23;
/* L200: */
    return 0;
} /* bpfdet_ */

#ifdef __cplusplus
	}
#endif

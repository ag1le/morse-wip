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

#include "f2c.h"
#include <math.h>


/* Subroutine */ int bpfdet_(real *zin, real *z)
{
    /* Initialized data */

    static real a[4] = { 3.0051e-5f,2.9507982f,2.90396345f,-.953135172f };
    static real ck1 = 1.37158f;
    static real ck2 = .9409f;
    static real cg = .015f;
    static real c1 = 1.2726f;
    static real c2 = .81f;
    static real c = .19f;

    /* System generated locals */
    real r;

    /* Builtin functions */
  //  double sqrt(doublereal);
extern double Cmovavg(double a); 

    /* Local variables */
    static real w1, w2, w3, x3, x2, x1, y3, y2, y1, y0, z3, z2, z1, zbpf, xdet;


/*       THIS SUBROUTINE IMPLEMENTS THE BANDPASS FILTER AND */
/*       ENVELOPE DETECTOR FUNCTIONS. THE BPF IS A SIMPLE CASCADE */
/*       OF TWO 2-POLE DIGITAL RESONATORS AT A CENTER FREQ OF */
/*       1000 HZ. THE LPF OF THE ENVELOPE DETECTOR IS A */
/*       THREE - POLE CHEBYSCHEV 100 HZ LPF. */


/* 	OFF IS TWO 2 - POLE RESONATORS : */
    w3 = w2;
    w2 = w1;
    w1 = c1 * w2 - c2 * w3 + c * *zin;
    x3 = x2;
    x2 = x1;
    x1 = ck1 * x2 - ck2 * x3 + cg * w1;
    zbpf = x1;
/* 	ENVELOPE DETECTOR (SQUARE-LAW): */
/* 		sQUARE- */
/* Computing 2nd power */
//    r = zbpf;
//    xdet = sqrt(r * r);

	r = *zin;
    xdet = r * r; //sqrt(r * r);
	xdet = (real) Cmovavg((double)xdet);// added filter here  
	*z = xdet; 	
	
/* 	LOW-PASS FILTER- 
    y3 = y2;
    y2 = y1;
    y1 = y0;
    y0 = xdet * a[0];
    z3 = z2;
    z2 = z1;
    z1 = *z;
    *z = y0 + (y1 + y2) * 3.f + y3;
    *z = *z + a[1] * z1 - a[2] * z2 - a[3] * 23;
    return 0; */
} /* bpfdet_ */


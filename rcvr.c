/* rcvr.f -- translated by f2c (version 20100827).
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
    real tau;
} blk1_;

#define blk1_1 blk1_

struct {
    real wc;
} blk2_;

#define blk2_1 blk2_

/* Table of constant values */

static real c_b2 = (float)6.28319;

/* Subroutine */ int rcvr_(real *zin, real *zout)
{
    /* Initialized data */

    static real theta = (float)0.;
    static real thetlo = (float)0.;

    /* Builtin functions */
    double r_mod(real *, real *), cos(doublereal), sin(doublereal);

    /* Local variables */
    static real zi, zq, zilp, zqlp;


/*       THIS SUBROUTINE CONVERTS THE INPUT SIGNAL AT */
/*       RADIAN FREQ  WC TO 1000 Hz. */


    theta += blk2_1.wc * blk1_1.tau;
    theta = r_mod(&theta, &c_b2);
    zi = *zin * cos(theta);
    zq = *zin * sin(theta);
    zilp += (zi - zilp) * (float).07;
    zqlp += (zq - zqlp) * (float).07;
    thetlo += blk1_1.tau * (float)6283.2;
    thetlo = r_mod(&thetlo, &c_b2);
    *zout = zilp * cos(thetlo) + zqlp * sin(thetlo);
    return 0;
} /* rcvr_ */

#ifdef __cplusplus
	}
#endif

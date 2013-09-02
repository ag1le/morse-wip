/* simsgi.f -- translated by f2c (version 20100827).
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
#include "common.h"



/* Table of constant values */

static integer c__1 = 1;
static real c_b3 = 0.f;
static real c_b6 = 6.28319f;

/* Subroutine */ int simsgi_(real *x, real *sig)
{
    /* Initialized data */

    static real xlast = 1.f;
    static real beta = 1.f;
    static real amp = 1.f;
    static real bfade = 0.f;
    static real theta = 1.f;
    static real phi = 1.f;

    /* Builtin functions */
    double exp(doublereal), r_mod(real *, real *), sin(doublereal);

    /* Local variables */
    static real w;
    static integer nc;
    static real tk, zn;
    extern /* Subroutine */ int key_(real *, real *);
    static real dur, ampb, tdur;
	extern double randn(real mean, real sigma);
    static real wchrp, phisgm;

    dur = beta;
    key_(&dur, x);
    beta = beta * (1.f - *x - xlast + *x * 2.f * xlast) + 1.f;
    tk = *x * (1.f - xlast);
    xlast = *x;
    w = randn(c_b3, blk2.asigma);
    amp += tk * w;
    if (amp < .01f) {
	amp = .01f;
    }

    w = randn(c_b3, blk2.bsigma);
    bfade = blk2.gamma * bfade + w;
    ampb = amp + bfade;
    if (ampb < .001f) {
	bfade = .001f - amp;
    }
    ampb = amp + bfade;

    tdur = blk1.tau * 1e3f * beta;
    wchrp = *x * blk2.wchirp * exp(-tdur / blk2.tchirp);
    theta += (nc + wchrp) * blk1.tau;
    theta = r_mod(&theta, &c_b6);

    w = randn(c_b3, phisgm);
    phi += tk * w;
    phi = r_mod(&phi, &c_b6);
    *sig = *x * ampb * sin(theta + phi);
    zn = randn(c_b3, blk2.rsigm);
    return 0;
} /* simsgi_ */


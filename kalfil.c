/* kalfil.f -- translated by f2c (version 20100827).
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
/* Common Block Declarations */

struct blksv1_1_ {
    real ykkip[25], pkkip[25], ykksv[750], pkksv[750];
};

#define blksv1_1 (*(struct blksv1_1_ *) &blksv1_)

/* Initialized data */

struct {
    real e_1[50];
    integer fill_2[1500];
    } blksv1_ = { .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, 
	    .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, 
	    .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, 
	    .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f };


/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int kalfil_(real *z__, integer *ip, real *rn, integer *ilx, 
	integer *ixs, integer *kelem, integer *jnode, integer *israte, real *
	dur, integer *ilrate, real *pin, real *lkhdj)
{
    /* Initialized data */

    static real pinmin = 1e-4f;

    /* Format strings */
    static char fmt_3[] = "(1x,\002KALFIL:\002,i3,2x,12(f9.3,1x))";

    /* System generated locals */
    real r__1;

    /* Builtin functions */
    //double exp(doublereal), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static real a, g, qa, hz, pz, zr, phi, pkk, ykk, expa, pest;
    extern /* Subroutine */ int model_(real *, integer *, integer *, integer *
	    , integer *, real *, real *, real *);
    static real ppred, ypred, pzinv;

    /* Fortran I/O blocks */
    static cilist io___16 = { 0, 6, 0, fmt_3, 0 };



/*   THIS SUBROUTINE COMPUTES THE ARRAY OF KALMAN FILTER */
/*   RECURSIONS USED TO DETERMINE THE LIKELIHOODS. */

/*   VARIABLES: */
/*       Z -	INPUT MEASUREMENT */
/*       IP -	INPUT PATH IDENTITY */
/*       RN -	INPUT NOISE POWER ESTIMATE */
/*       ILX -	INPUT SAVED KEYSTATE ON PATH IP */
/*       IXS -	INPUT KEYSTAT OF NEW NODE */
/*       KELEM -	INPUT ELEM STATE OF NEW NODE */
/*       ISRATE 	INPUT SPEED STATE OF NEW NODE */
/*       DUR - 	INPUT CURRENT DURATION OF ELEMENT ON IP */
/*       ILRATE 	INPUT SPEED STATE ON PATH IP */
/*       PIN - 	TRANS PROB FROM PATH IP TO NODE N */
/*       LKHDJ - OUTPUT CALCULATED LIKELIHOOD VALUE */

/*   SUBROUTINES USED */
/*       MODEL - OBTAINS THE SIGNAL-STATE-DEPENDENT LINEAR */
/*       	MODEL FOR THE KALMAN FILTER RECURSIONS */

/*   IF TRANSITION PROBABILITY IS VERY SMALL, DON'T */
/*   BOTHER WITH LIKELIHOOD CALCULATION: */

    if (*pin > pinmin) {
	goto L100;
    }
    *lkhdj = 0.f;
    goto L400;

/*   OBTAIN STATE-DEPENDENT MODEL PARAMETERS: */

L100:
    model_(dur, kelem, ilrate, israte, ixs, &phi, &qa, &hz);

/* 	GET PREVIOUS ESTIMATES FOR PATH IP */

    ykk = blksv1_1.ykkip[*ip - 1];
    pkk = blksv1_1.pkkip[*ip - 1];

/*  IMPLEMENT KALMAN FILTER FOR THIS TRANSITION */

    ypred = phi * ykk;
    ppred = phi * pkk * phi + qa;
    pz = hz * ppred + *rn;
    pzinv = 1.f / pz;
    g = ppred * hz * pzinv;
    pest = (1.f - g * hz) * ppred;
    zr = *z__ - hz * ypred;
    blksv1_1.ykksv[*jnode - 1] = ypred + g * zr;
    blksv1_1.pkksv[*jnode - 1] = pest;
    if (blksv1_1.ykksv[*jnode - 1] <= .01f) {
	blksv1_1.ykksv[*jnode - 1] = .01f;
    }
/* Computing 2nd power */
    r__1 = zr;
    a = pzinv * .5f * (r__1 * r__1);
    if (a <= 1e3f) {
	goto L200;
    }
    *lkhdj = 0.f;
    goto L400;
L200:
    expa = exp(-a);
    *lkhdj = 1.f / sqrt(pz) * exp(-a);
    goto L400;
    s_wsfe(&io___16);
    do_fio(&c__1, (char *)&(*ip), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&hz, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&qa, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&phi, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&pz, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&zr, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&g, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&pest, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&ykk, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&blksv1_1.ykksv[*jnode - 1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&a, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*lkhdj), (ftnlen)sizeof(real));
    e_wsfe();
L400:
    return 0;
} /* kalfil_ */


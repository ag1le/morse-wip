/* likhd.f -- translated by f2c (version 20100827).
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

/* Common Block Declarations */

struct {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam_;

#define blklam_1 blklam_

struct {
    integer isx[6];
} blks_;

#define blks_1 blks_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int likhd_(real *z__, real *rn, integer *ip, integer *lambda,
	 real *dur, integer *ilrate, real *p, real *lkhd)
{
    /* Format strings */
    static char fmt_110[] = "(1x,\002LIKHD:\002,i2,1x,i2,1x,f5.3,2x,i3,3(2x,"
	    "i2),4(3x,f8.3))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j, k, n;
    static real pin;
    static integer ilx, ixs;
    static real lkhdj;
    static integer kelem;
    extern /* Subroutine */ int kalfil_(real *, integer *, real *, integer *, 
	    integer *, integer *, integer *, integer *, real *, integer *, 
	    real *, real *);
    static integer israte;

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 6, 0, fmt_110, 0 };



/* 	THIS SUBROUTINE CALCULATES,FOR EACH PATH */
/* 	EXTENSION TO STATE N, THE LIKELIHOOD OF THAT */
/* 	TRANSITION GIVEN THE MEASUREMENTZ. IT USES */
/* 	AN ARRAY OF LINEAR (KALMAN) FILTERS TO DO SO. */

/* 	VARIABLES: */
/* 	Z- 	INPUT MEASUREMENT */
/* 	RN-	INPUT NOISE POWER ESTIMATE */
/* 	IP-	INPUT SAVED PATH IDENTITY */
/* 	LAMBDA-	INPUT SAVED LTR STATE IDENTITY */
/* 	DUR-	INPUT SAVED DURATION OF ELEMENT ON PATH IP */
/* 	ILRATE-	INPUT SAVED DATA RATE (SPEED) */
/* 	P-	INPUT TRANSITION PROBABILITIES */
/* 	LKHD-	OUTPUT COMPUTED LIKELIHOODS FOR EACH TRANS */

/*  SUBROUTINES USED: */
/* 	KALFIL-KALMAN FILTER FOR EACH NEW PATH */

/*   OBTAIN SAVED KEYSTATE: */
    /* Parameter adjustments */
    --lkhd;
    p -= 26;

    /* Function Body */
    if (*lambda == 0) {
	goto L200;
    }
    kelem = blklam_1.ilami[blklam_1.ielmst[*lambda - 1] - 1];
    ilx = blklam_1.ilamx[kelem - 1];
/* 	FOR EACH STATE: */
    for (k = 1; k <= 6; ++k) {
	for (i__ = 1; i__ <= 5; ++i__) {
/* 	OBTAIN KEYSTATE, RATE STATE, STATE N, NEW NODE: */
	    ixs = blks_1.isx[k - 1];
	    israte = i__;
	    n = (i__ - 1) * 6 + k;
	    j = (*ip - 1) * 30 + n;
	    pin = p[*ip + n * 25];
/* 	COMPUTE AND STORE LIKELIHOOD: */
	    kalfil_(z__, ip, rn, &ilx, &ixs, &kelem, &j, &israte, dur, ilrate,
		     &pin, &lkhdj);
	    lkhd[j] = lkhdj;
	    goto L100;
	    if (pin <= 1e-6f) {
		goto L100;
	    }
	    s_wsfe(&io___11);
	    do_fio(&c__1, (char *)&(*ip), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*lambda), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*ilrate), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*dur), (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&pin, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&lkhdj, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&(*rn), (ftnlen)sizeof(real));
	    e_wsfe();
/* 	2 F8.4,2X,F8.4) */
L100:
	    ;
	}
    }
L200:
    return 0;
} /* likhd_ */


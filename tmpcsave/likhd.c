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
#include "common.h"
#include <stdio.h>

//#define DEBUG 1


int likhd_(real *z, real *rn, integer ip, integer *lambda, real *dur, integer *ilrate, real p[][25], real lkhd[][25])
{

    /* Local variables */
    static integer i, j, k, n;
    static real pin;
    static integer ilx, ixs;
    static real lkhdj;
    static integer kelem;
    extern int kalfil_(real *, integer , real *, integer *,integer *, integer *, integer *, integer *, real *, integer *, real *, real *);
    static integer israte;


/* 	THIS SUBROUTINE CALCULATES,FOR EACH PATH */
/* 	EXTENSION TO STATE N, THE LIKELIHOOD OF THAT */
/* 	TRANSITION GIVEN THE MEASUREMENTZ. IT USES */
/* 	AN ARRAY OF LINEAR (KALMAN) FILTERS TO DO SO. */

/* 	VARIABLES: */
/* 	Z- INPUT MEASUREMENT */
/* 	BN-INPUT NOISE POWER ESTIMATE */
/* 	IP-INPUT SAVED PATH IDENTITY */
/* 	LAMBDA-INPUT SAVED LTR STATE IDENTITY */
/* 	DUR-INPUT SAVED DURATION OF ELEMENT ON PATH IP */
/* 	ILRATE-INPUT SAVED DATA RATE (SPEED) */
/* 	P-INPUT TRANSITION PROSABILITIES */
/* 	SBHD-OUTPUT COMPUTED LIKELIHOODS FOR EACH TRANS */

/*  SUBRODTINES USED: */
/* 	KALFIL-KALMAN FILTER FOR EACH NEW PATH */

/*   OBTAIN SAVED KEYSTATE: */

    /* Function Body */
    if (*lambda == 0) {
	goto L200;
    }
    kelem = blklam.ilami[blklam.ielmst[*lambda - 1] - 1];
    ilx = blklam.ilamx[kelem - 1];
/* 	FOR EACH STATE: */
    for (k = 0; k < 6; ++k) {
		for (i = 0; i < 5; ++i) {
/* 	OBTAIN KEYSTATE, RATE STATE, STATE N, NEW NODE: */
//		    n = (i - 1) * 6 + k;
//		    j = (ip ) * 30 + n;

		    ixs = blks.isx[k];
		    israte = i;
		    n = i * 6 + k;
	    	j = ip  * 30 + n;
		    pin = p[n][ip];
/* 	COMPUTE AND STORE LIKELIHOOD: */
		    kalfil_(z, ip, rn, &ilx, &ixs, &kelem, &j, &israte, dur, ilrate,&pin, &lkhdj);
		    lkhd[n][ip] = lkhdj;

#ifdef DEBUG
printf("\nLIKHD: p[%2d][%2d]:%f z:%f lambda:%2d k:%d ilrate:%d israte:%d dur:%f pin:%f lkhdj[%3d][%3d]:%f rn:%f ip:%d n:%d i:%d k:%d",n,ip,p[n][ip],*z,*lambda,k, *ilrate,israte,*dur,pin,n,ip, lkhd[n][ip],*rn, ip, n, i, k);
#endif 
		    goto L100;
		    if (pin <= 1e-6f) {
				goto L100;
		    }
L100:
	    	;
		}
    }
L200:
    return 0;
} /* likhd_ */


/* ptrans.f -- translated by f2c (version 20100827).
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



int ptrans_(integer *kelem, integer *irate, integer *lambda, integer *ilrate, real *ptrx, real *psum, real *pin, integer *n)
{
    static real pelem, prate;
    extern doublereal spdtr_(integer *, integer *, integer *, integer *);

/* 	THIS FUNCTION SUBROUTINE RETURNS THE PATH CONDITIONAL TRANSITION */
/* 	PROBABILITIES TO EACH ALLOWABLE STATE N. */
/* 	VARIABLES: */
/* 	KELEM-      INPUT CURRENT ELEMENT STATE */
/* 	IRATE-      INPUT CURRENT DATA RATE STATE */
/* 	LAMBDA-     INPUT IDENTITY OF CURRENT LTR STATE */
/* 	PTRX-       INPUT KEYSTATE TRANSITION PROBABILITY */
/* 	ELEMTR-     ELEMENT TRANSITION PROBABILITY MATRIX */

/* 	FUNCTION SUBROTINE USED: */
/* 	SPDTR-      RETURNS DATA RATE TRANSITION PROGS,CONDITIONED ON CURRENT SPACE TYPE. */

/* 	IF THE SAVED ELEMENT AND THE ELEMENT OF THE STATE N */
/* 	TO WHICH THE PATH IS BEING EXTENDED ARE THE SAME, */
/*  THEN THE STATE TRANS PROB IS SIMPLY KEYSTATE TRANS PROB: */

    if (*kelem != blklam.ilami[blklam.ielmst[*lambda - 1] - 1]) {
		goto L100;
    }
    pin[*n] = *ptrx;
    if (*irate != 2) {
		pin[*n] = 0.f;
    }
    goto L200;

/* 	OTHERWISE: */
/* 	OBTAIN ELEM TRANS PROBS TABLE: */

L100:
    pelem = blkelm.elemtr[*kelem][blklam.ielmst[*lambda - 1]];
/* 	NEXT COMPUTE ELEM-CONDITIONAL SPEED TRANS PROB: */
// 								  iselm= next state  ilelm=current state
    prate = spdtr_(irate, ilrate, kelem, &blklam.ilami[blklam.ielmst[*lambda - 1] - 1]);
/* 	TRANS IS THE PRODUCT: */
  	pin[*n] = (1.f - *ptrx) * pelem * prate;
L200:
    *psum += pin[*n];
#ifdef DEBUG
printf("\nPTRANS: psum:%f pin[%2d]:%f pelem[%d][%d]:%f prate:%f ptrx:%f lambda:%d irate:%d", *psum, *n, pin[*n], *kelem, blklam.ielmst[*lambda - 1],  pelem,prate,*ptrx, *lambda, *irate);
#endif
    return 0;
} /* ptrans_ */


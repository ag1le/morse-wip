/* trelis.f -- translated by f2c (version 20100827).
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

#define DEBUG 1

/* Common Block Declarations */

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int trelis_(integer *isave, integer *pathsv, integer *lambda, integer *imax)
{
    /* Initialized data */

	static int init = 0; 

    static real pthtrl[200][25];
    static integer lmdsav[200][25]; 
    static integer n = 0;
    static integer ndelay = 200;
    static integer ipnod[25] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    static integer ncall = 0;
    static integer nmax = 0;
    static integer mmax = 0;


    /* Local variables */
    static integer i, i1, k, k0, kd, ip, ieq, ltr, ndel;
    static real wait;
    static integer isavg, ipmax;
    static real xsavg, xmmax, xnmax;
    static integer ltrsv[200], ndlavg;
    static real xdlavg;
    static integer ndelst;
    extern /* Subroutine */ int transl_(integer *);


	if (init == 0) {
		init = 1; 
		for (i = 0; i < 200; i++) {
			for (k=0;k<25;k++){
				pthtrl[i][k] = 5.f;
				lmdsav[i][k] = 5; 
			}
		}
			
	}

/*    THIS SUBROUTINE STORES THE SAVED NODES AT EACH */
/*    STAGE AND FORMS THE TREE OF SAVED PATHS LINKING */
/*    THE NODES. DECODING IS ACCOMPLISHED BY FINDING */
/*    THE CONVERGENT PATH IF IT OCCURS WITHIN A MAXIMUM */
/*    DELAY SET BY THE PARAMETER NDELAY. IF CONVERGENCE */
/*    TO A SINGLE PATH DOES NOT OCCURS, THEN DECODING IS */
/*    DONE BY READING THE LETTER ON THE PATH WITH HIGHEST */
/*    PROBABILITY */
    /* Parameter adjustments */
//    --lambda;
//    --pathsv;

    /* Function Body */
/* 	KEEP AVERAGE OF ISAVE, NDEL FOR DATA ANALYSIS: */
  
	++ncall;
    if (blkend.iend != 1) {
		goto L10;
    }
    isavg = xsavg;
    ndlavg = xdlavg;
    blkend.iend = 0;
#ifdef DEBUG
printf("\nAVG NO OF PATHS SAVED: %d %d", isavg, ndlavg);
printf("\nPERCENT OF TIME PATHS = 25: %f %f", xmmax, xnmax);
printf("\nPERCENT OF TIME DELAY = 200:");
#endif

L10:
    xsavg = (xsavg * (ncall - 1) + *isave) / ncall;
    xdlavg = (xdlavg * (ncall - 1) + ndel) / ncall;
    if (ndel != ndelay) {
		goto L20;
    }
    ++nmax;
    xnmax = (real) nmax;
    xnmax /= ncall;

L20:
    if (*isave != 25) {
		goto L30;
    }
    ++mmax;
    xmmax = (real) mmax;
    xmmax /= ncall;

L30:
/* 	STORE PATHSV AND CORRESPONDING LAMBDA IN THE TRELLIS USING A CIRCULAR BUFFER OF LENGTH NDELAY : */
    ++n;
    if (n == ndelay + 1) {
		n = 1;
    }
    i1 = *isave;
    for (i = 0; i <*isave; ++i) {
		pthtrl[n][i] = (real) pathsv[i];
		lmdsav[n][i] = lambda[i];
#ifdef DEBUG
	printf("\nTRELIS: n:%d pthtrl[%d][%d]:%f lmdsav[%d][%d]:%d",n, n,i,pthtrl[n][i], n,i,lmdsav[n][i]);
#endif
    }
/* 	PERFORM DYNAMIC PROGRAM ROUTINE TO FIND CONVERGENT PATH: */
    k = 0;
    for (i = 0; i < *isave; ++i) {
		ipnod[i] = i;
    }
L190:
    ++k;
    if (k == ndelay) {
		goto L700;
    }
    for (ip = 0; ip < *isave; ++ip) {
		i = n - k + 1;
		if (i <= 0) {
			i = ndelay + i;
		}
		ipnod[ip] = pthtrl[ipnod[ip]][i];
		if (ip == *imax) {
			ipmax = ipnod[ip];
		}
    }
/* 	IF ALL NODES ARE EQUAL,THEN PATHS CONVERGE: */
    for (ieq = 1; ieq <= *isave; ++ieq) {
		if (ipnod[0] != ipnod[ieq]) {
			goto L190;
		}
    }
/* 	PATHS CONVERGE; SET NDEL: */
    ndel = k + 1;

/* 	IF POINT OF CONVERGENCE IS SAME AS IT WAS ON */
/* 	LAST CALL, THEN NO NEED TO RE-DECODE SAME NODE: */
    if (ndel == ndelst + 1) {
		goto L800;
    }
/* 	IF POINT OF CONVERGENCE OCCURS AT SAME DELAY AS LAST CALL, THEN TRANSLATE: */
    if (ndel != ndelst) {
		goto L350;
    }
    i = n - ndel + 1;
    if (i <= 0) {
		i = ndelay + 1;
    }
    ltr = lmdsav[ipnod[0]][i];
#ifdef DEBUG
printf("\nTRELIS: IF POINT OF CONVERGENCE OCCURS AT SAME DELAY AS LAST CALL, THEN TRANSLATE:");
#endif
    transl_(&ltr);
    goto L800;
/* 	OTHERWISE,POINT OF CONVERGENCE HAS OCCURED */
/* 	EARLIER ON THIS CALL, SO NEED TO TRANSLATE */
/* 	EVERYTHING ON THE CONVERGENT PATH FROM */
/* 	PREVIOUS POINT OF CONVERGENCE TO THIS POINT: */
L350:
    k0 = 0;
    ip = ipnod[0];
    i1 = ndelst;
    for (k = ndel; k <= i1; ++k) {
		++kd;
		i = n - k + 1;
		if (i <= 0) {
			i = ndelay + i;
		}
		ltrsv[kd - 1] = lmdsav[ip][i];
		ip = pthtrl[ip][i];
    }
/* 	REVERSE ORDER OF DECODED LETTERS, SINCE THEY */
/* 	WERE OBTAINED FROM THE TRELLIS IN REVERSE; */
/* 	TRANSLATE EACH: */
    i1 = kd;
    for (i = 1; i <= i1; ++i) {
		ltr = ltrsv[kd - i];
#ifdef DEBUG
	printf("\nTRELIS: REVERSE ORDER OF DECODED LETTERS -  TRANSLATE EACH:");
#endif
		transl_(&ltr);
	/* L500: */
    }
    goto L800;
L700:
/* 	PATHS HAVE NOT CONVERGED AT MAXIMUM ALLOWABLE */
/* 	DELAY, SO TRANSLATE WHAT IS ON HIGHEST */
/* 	PROBABILITY PATH: */
    ndel = ndelay;
    i = n - ndelay + 1;
    if (i <= 0) {
		i = ndelay + i;
    }
    ltr = lmdsav[ipmax][i];
#ifdef DEBUG
printf("\nTRELIS: PATHS HAVE NOT CONVERGED AT MAXIMUM ALLOWABLE DELAY SO TRANSLATE:");
#endif
    transl_(&ltr);
/* 	PRUNE AWAY NODES WHICH ARE NOT ON THIS PATH: */
    for (k = 0; k < *isave; ++k) {
		if (ipnod[k] == ipmax) {
			goto L750;
		}
		lambda[k] = 0;
	L750:
		;
    }
L800:
    ndelst = ndel;
    return 0;
} /* trelis_ */


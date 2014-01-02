// ----------------------------------------------------------------------------
// trelis.c --  bayesian morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Bayesian Morse code decoder   

// bmorse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bmorse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bmorse.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <stdio.h> 
#include "bmorse.h"

//#define DEBUG 1


int trelis_(integer *isave, integer *pathsv, integer *lambda, integer *imax, integer *ipmax)
{
    /* Initialized data */

    static integer lmdsav[25*NDELAY];	/* was [200][25] */ 
    static integer n = 0;
    static integer ndelay = NDELAY;
    static integer ipnod[25] = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    static integer ncall = 0;
    static integer nmax = 0;
    static integer mmax = 0;
    static integer ltrsv[NDELAY] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	    0,0,0,0,0,0,0,0,0,0,0,0,0 };
    static integer kd = 0;
    static integer ndelst = 0;
    static integer pthtrl[25*NDELAY];	/* was [200][25] */
    static integer iend = 0;


    /* System generated locals */
    integer i1;

    /* Local variables */
    static int i, k, ip, ieq, ltr, ndel, retstat;
    static char wait[1];
    static int isavg, init=0;
    static real xsavg, xmmax, xnmax;
    static int ndlavg;
    static real xdlavg;
    static char *chrp; 

/*    THIS SUBROUTINE STORES THE SAVED NODES AT EACH */
/*    STAGE AND FORMS THE TREE OF SAVED PATHS LINKING */
/*    THE NODES. DECODING IS ACCOMPLISHED BY FINDING */
/*    THE CONVERGENT PATH IF IT OCCURS WITHIN A MAXIMUM */
/*    DELAY SET BY THE PARAMETER NDELAY. IF CONVERGENCE */
/*    TO A SINGLE PATH DOES NOT OCCURS, THEN DECODING IS */
/*    DONE BY READING THE LETTER ON THE PATH WITH HIGHEST */
/*    PROBABILITY */

    /* Parameter adjustments */
    --lambda;
    --pathsv;

    /* Function Body */
 	if (init ==0) {
 		init = 1; 
		for (i=0; i<(25*NDELAY); i++) {
			pthtrl[i] = 0;
			lmdsav[i] = 0; 
		}
	}
    
    
/* 	KEEP AVERAGE OF ISAVE, NDEL FOR DATA ANALYSIS: */

	retstat = 1;
    ++ncall;
    if (iend == 1) {
		isavg = xsavg;
		ndlavg = xdlavg;
		iend = 0;
		printf("\nAVG # OF PATHS SAVED:%4.2f,AVG DECODE DELAY:%4.2f)", xsavg, xdlavg);
		printf("\nPERCENT OF TIME PATHS = 25: %3.2f, PERCENT OF TIME DELAY = 200: %3.2f", xmmax, xnmax);
    }
    xsavg = (xsavg * (ncall - 1) + *isave) / ncall;
    xdlavg = (xdlavg * (ncall - 1) + ndel) / ncall;
    if (ndel == ndelay) {
		++nmax;
		xnmax = (real) nmax;
		xnmax /= ncall;
    }
    if (*isave == 25) {
		++mmax;
		xmmax = (real) mmax;
		xmmax /= ncall;
    }

/* 	STORE PATHSV AND CORRESPONDING LAMBDA IN THE */
/* 	TRELLIS USING A CIRCULAR BUFFER OF LENGTH NDELAY : */
    ++n;
    if (n == ndelay + 1) {
		n = 1;
    }
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		pthtrl[n + i * NDELAY-NDELAY-1] = pathsv[i];
		lmdsav[n + i * NDELAY-NDELAY-1] = lambda[i];
    }

/* 	PERFORM DYNAMIC PROGRAM ROUTINE TO FIND CONVERGENT PATH: */
    k = 0;
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		ipnod[i - 1] = i;
    }
L190:
    ++k;
    if (k == ndelay) {
		goto L700;
    }

/* 	IF IP EQUALS INDEX OF HIGHEST PROBABILITY NODE, STORE NODE TO IPMAX */
    i1 = *isave;
    for (ip = 1; ip <= i1; ++ip) {
		i = n - k + 1;
		if (i <= 0) {
			i = ndelay + i;
		}
		ipnod[ip - 1] = pthtrl[i + ipnod[ip - 1] * NDELAY-NDELAY-1];
		if (ip == *imax) {
			*ipmax = ipnod[ip - 1];
		}
    }

/* 	IF ALL NODES ARE EQUAL,THEN PATHS CONVERGE: */
    i1 = *isave;
    for (ieq = 2; ieq <= i1; ++ieq) {
		if (ipnod[0] != ipnod[ieq - 1]) {
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
		i = ndelay + i;
    }
    ltr = lmdsav[i + ipnod[0] * NDELAY-NDELAY-1];
#ifdef DEBUG
printf("\nSAME DELAY AS LAST: %d",ltr);
#endif
    retstat = transl_(&ltr);
    goto L800;

/* 	OTHERWISE,POINT OF CONVERGENCE HAS OCCURED */
/* 	EARLIER ON THIS CALL, SO NEED TO TRANSLATE */
/* 	EVERYTHING ON THE CONVERGENT PATH FROM */
/* 	PREVIOUS POINT OF CONVERGENCE TO THIS POINT: */
L350:
    kd = 0;
    ip = ipnod[0];
    i1 = ndelst;
    for (k = ndel; k <= i1; ++k) {
		++kd;
		i = n - k + 1;
		if (i <= 0) {
			i = ndelay + i;
		}
		ltrsv[kd - 1] = lmdsav[i + ip * NDELAY-NDELAY-1];
		ip = pthtrl[i + ip * NDELAY-NDELAY-1];
    }

/* 	REVERSE ORDER OF DECODED LETTERS, SINCE THEY */
/* 	WERE OBTAINED FROM THE TRELLIS IN REVERSE; */
/* 	TRANSLATE EACH: */
    i1 = kd;
    for (i = 1; i <= i1; ++i) {
		ltr = ltrsv[kd - i];
#ifdef DEBUG
		printf("\nIN REVERSE ORDER: %d",ltr);
#endif
		retstat = transl_(&ltr);
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
    ltr = lmdsav[i + *ipmax * NDELAY-NDELAY-1];
#ifdef DEBUG
printf("\nHIGHEST PROB: %d", ltr);
#endif
    retstat = transl_(&ltr);
/* 	PRUNE AWAY NODES WHICH ARE NOT ON THIS PATH: */
    i1 = *isave;
    for (k = 1; k <= i1; ++k) {
		if (ipnod[k - 1] != *ipmax) {
			lambda[k] = 0;
		}
    }

L800:
    ndelst = ndel;
    return retstat;
} /* trelis_ */


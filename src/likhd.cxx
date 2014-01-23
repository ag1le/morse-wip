// ----------------------------------------------------------------------------
// likhd.c --  bayesian morse code decoder 
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
// ---------------------------------------------------------------------------

#include "bmorse.h"
#include <stdio.h>

int morse::likhd_(real *z, real *rn, integer *ip, integer *lambda,
	 real *dur, integer *ilrate, real *p, real *lkhd)
{
 
    /* Local variables */
    static integer i, j, k, n;
    static real pin;
    static integer ilx, ixs;
    static real lkhdj;
    static integer kelem;
 
    static integer israte;



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
    kelem = ilami[ielmst[*lambda - 1] - 1];
    ilx = ilamx[kelem - 1];
/* 	FOR EACH STATE: */
    for (k = 1; k <= 6; ++k) {
		for (i = 1; i <= 5; ++i) {
/* 	OBTAIN KEYSTATE, RATE STATE, STATE N, NEW NODE: */
			ixs = isx[k - 1];
			israte = i;
			n = (i - 1) * 6 + k;
			j = (*ip - 1) * 30 + n;
			pin = p[*ip + n * 25];
/* 	COMPUTE AND STORE LIKELIHOOD: */
			kalfil_(z, ip, rn, &ilx, &ixs, &kelem, &j, &israte, dur, ilrate,&pin, &lkhdj);
			lkhd[j] = lkhdj;
//			goto L100;
			if (pin > 1e-6f) {

//printf("\nz:%f ip:%3d rn:%f ilx:%d ixs:%d kelem:%d j:%4d israte:%d dur:%4.1f ilrate:%d pin:%f lkhd:%f",(double)*z,(int)*ip,(double)*rn,(int)ilx,(int)ixs,(int)kelem,(int)j,(int)israte,(double)*dur,(int)*ilrate,(double)pin,(double)lkhdj);
			}
L100:
			;
		}
    }
L200:
    return 0;
} /* likhd_ */


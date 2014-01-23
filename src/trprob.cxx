// ----------------------------------------------------------------------------
// trprob.c --  bayesian morse code decoder 
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

#include "bmorse.h"
#include <stdio.h>

int morse::trprob_(integer *ip, integer *lambda, real *dur, integer *ilrate, real *p)
{
    static integer i, k, n;
    static real pin[30];
    static integer kelm;
    static real psum, ptrx;
    static integer ielem, irate;



/* 		THIS SUBROUTINE COMPUTES THE TRANSITION PROBABILITY */
/* 		FROM SAVED PATH IP TO EACH STATE N AND STORES THE */
/* 		RESULT IN P(IP, N). */

/* 		VARIABLES: */
/* 		IP - 	INPUT SAVED PATH IDENTITY */
/* 		LAMBDA 	INPUT SAVED LTR STATE IDENTITY */
/* 		DUR - 	INPUT SAVED ELEMENT DURATION */
/* 		ILPATE 	INPUT SAVED DATA RATE IDENTITY */
/* 		P - 	OUTPUT TRANSITION PROBABILITY MATRIX */

/* 		THE FOLLOWING FUNCTION SUBROUTINES ARE USED: */
/* 		XTRANS 	RETURNS THE KEYSTATE TRANSITION PROBABILITY */
/* 	               	CONDITIONED ON ELEMENT TYPE AND DATA RATE */
/* 		PTRANS	RETURNS THE PATH-CONDITIONAL STATE TRANSITION PROB */
/* 	LOOK UP ELEMENT TYPE FOR LTR STATE LAMBDA: */
    /* Parameter adjustments */
    p -= 26;

    /* Function Body */
    if (*lambda == 0) {
		for (n = 1; n <= 30; ++n) {
			p[*ip + n * 25] = 0.f;
		}
		return 0;
    }

    ielem = ilami[ielmst[*lambda - 1] - 1];
/* 	COMPUTE KEYSTATE TRANSITION PROBABILITY: */
    ptrx = xtrans_(&ielem, dur, ilrate);

/* 	FOR EACH STATE, COMPUTE STATE TRANSITION PROBABILITY: */
    psum = 0.f;
    for (k = 1; k <= 6; ++k) {
		for (i = 1; i <= 5; ++i) {
			n = (i - 1) * 6 + k;
			kelm = k;
			irate = i;
			ptrans_(&kelm, &irate, lambda, ilrate, &ptrx, &psum, pin, &n);
		}
    }
    if (psum ==0.0) {
    	printf("\ntrprob: psum = 0");
    	return 0;
    }

    for (n = 1; n <= 30; ++n) {
		p[*ip + n * 25] = pin[n - 1] / psum;
    }

L200:
    return 0;
} /* trprob_ */


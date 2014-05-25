// ----------------------------------------------------------------------------
// probp.c --  bayesian morse code decoder 
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

int morse::probp_(real *p, integer *isave)
{
    /* System generated locals */
    integer i1;

    /* Local variables */
	integer i, j, n, ni;
	real pmax, psav[30*PATHS], psum;


/* 		PROBP COMPUTES THE POSTERIOR PROBABILITY OF EACH NEW PATH */

/* 		VARIABLES: */
/* 		P-		INPUT: SAVED PROBS OF PRIOR PATHS */
/* 		OUTPUT:	COMPUTED POSTERIOR PROBS OF NEW PATHS */
/* 		PIN-		INPUT TRANSISTION PROBABILITIES */
/* 		LKHD-		INPUT LIKELIHOODS OF EACH TRANSTION */
/* 		PSUM-		NORMALIZING CONSTANT (SUM OF P(J)) */

    /* Parameter adjustments */
//    --lkhd;
//    pin -= 26;
    --p;

    /* Function Body */
    pmax = 0.f;
    psum = 0.f;
/* 	FOR EACH SAVED PATH, EACH TRANSITION: */
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		for (n = 1; n <= 30; ++n) {
	/* 		COMPUTE IDENTITY OF NEW PATH: */
			j = (i - 1) * 30 + n;
	/*      PRODUCT OF PROBS, ADD TO PSUM */
//			psav[j - 1] = p[i] * pin[i + n * PATHS] * lkhd[j];
			psav[j - 1] = p[i] * pin[n-1][i-1] * lkhd[n-1][i-1];
			psum += psav[j - 1];
			if (psav[j - 1] <= pmax) {
			goto L100;
			}
			pmax = psav[j - 1];
L100:
			;
		}
    }
/* 	NORMALIZE TO GET PROBABILITIES; SAVE: */
    ni = *isave * 30;
    i1 = ni;
    if (psum ==0.0) {
    	printf("\nprobp: psum = 0");
    	return 0;
    }
    for (j = 1; j <= i1; ++j) {
		p[j] = psav[j - 1] / psum;
	}
    return 0;
} /* probp_ */


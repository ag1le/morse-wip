// ----------------------------------------------------------------------------
// savep.c --  bayesian morse code decoder 
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



int morse::savep_(real *p, integer *pathsv, integer *isave, integer 
	*imax, integer *lamsav, real *dursav, integer *ilrsav, integer *
	lambda, real *dur, integer *ilrate, integer *sort, real *pmax)
{
    /* Initialized data */

	real popt = .9f;

    /* System generated locals */
    integer i1, i2;

    /* Local variables */
	integer i, j, k, n, ip, jsav, nsav;
    real psav[25], psum;
	integer iconv[25], ipsav, isavm1, nplus1;


/* 	THIS SUBROUTINE PERFORMS THE ALGORITM TO SAVE */
/* 	THE PATHS WITH HIGHEST POSTERIOR PROBABILITY. */
/* 	IT WILL SAVE A MINIMUM OF 7 PATHS (ONE FOR EACH */
/* 	ELEMENT STATE AND ONE ADDITIONAL NODE), AND */
/* 	A MAXIMUM OF 25 PATHS.  WITHIN THESE LIMITS, IT */
/* 	SAVED ONLY ENOUGH TO MAKE THE TOTAL SAVED PROBABILITY */
/* 	EQUAL TO POPT. */


/* 	ADDITIONALLY, IT RESORTS THE LAMBDA,DUR,AND ILRATE */
/* 	ARRAYS TO CORRESPOND TO THE SAVED NODES. */


/* 	VARIABLES: */
/* 		P-	INPUT PROBABILITY ARRAY OF NEW NODES */
/* 		PATHSV-	OUTPUT ARRAY OF THE PREVIOUS NODES TO */
/* 			WHICH THE SAVED NODES ARE CONNECTED. */
/* 		ISAVE-	INPUT: NO. OF PREVIOUS NODES SAVED */

/* 			OUPUT: NO. OF NODES SAVED AT CURRENT STAGE */
/* 		IMAX-	INDEX OF HIGHEST PROBABILITY NODE */
/* 		LAMSAV-	INPUT ARRAY OF LTR STATES AT EACH NEW NODE */
/* 		DURSAV-	INPUT ARRAY OF SAVED DURATIONS */
/* 		ILRSAV-	INPUT ARRAY OF SAVED RATES */
/* 		LAMBDA-	OUTPUT ARRAY OF SAVED LTR STATES, SORTED */

/* 			ACCORDING TO PROBABILITY */
/* 		DUR-	OUTPUT ARRAY OF SORTED DURATIONS */
/* 		ILRATE-	OUTPUT ARRAY OF SORTED RATES */


    /* Parameter adjustments */
    --sort;
    --ilrate;
    --dur;
    --lambda;
    --ilrsav;
    --dursav;
    --lamsav;
    --pathsv;
    --p;

    /* Function Body */
    nsav = 0;
    psum = 0.f;
/* 	SELECT SIX HIGHEST PROB ELEMENT STATE NODES: */
    for (k = 1; k <= 6; ++k) {
		*pmax = 0.f;
		i1 = *isave;
		for (ip = 1; ip <= i1; ++ip) {
			for (i = 1; i <= 5; ++i) {
				j = (ip - 1) * 30 + (i - 1) * 6 + k;
				if (p[j] >= *pmax) {
					*pmax = p[j];
					jsav = j;
					ipsav = ip;
				}
			}
		}
	/* 	IF FOLLOWING TWO LINES COMMENTED OUT WE GET NSAV = 7 */
		if (*pmax >= 1e-6f) {
			++nsav;
			psum += *pmax;
			psav[nsav - 1] = *pmax;
			pathsv[nsav] = ipsav;
			sort[nsav] = jsav;
		}
    }
/* 	SELECT ENOUGH ADDITIONAL NODES TO MAKE TOTAL */
/* 	PROBABILITY SAVED EQUAL TO POPT, OR A MAX OF 25: */
	do {
		*pmax = 0.f;
		i1 = *isave;
		for (ip = 1; ip <= i1; ++ip) {
			for (n = 1; n <= 30; ++n) {
				j = (ip - 1) * 30 + n;
				i2 = nsav;
				for (i = 1; i <= i2; ++i) {
					if (j == sort[i]) {
						goto L500;
					}
				}
				if (p[j] > *pmax) {
					*pmax = p[j];
					jsav = j;
					ipsav = ip;
				}
		L500:
				;
			}
		}
		psum += *pmax;
		++nsav;
		psav[nsav - 1] = *pmax;
		pathsv[nsav] = ipsav;
		sort[nsav] = jsav;
		if (psum >= popt) {
			break; 
		}
	}   while (nsav < 25); 
/* 	NEW ISAVE EQUALS NO. OF NODES SAVED: */
    *isave = nsav;

/* 	SORT THE SAVED ARRAYS TO OBTAIN THE ARRAYS */
/* 	TO BE USED FOR THE NEXT ITERATION: */
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		p[i] = psav[i - 1] / psum;
		lambda[i] = lamsav[sort[i]];
		dur[i] = dursav[sort[i]];
		ilrate[i] = ilrsav[sort[i]];
		ykkip[i - 1] = ykksv[sort[i] - 1];
		pkkip[i - 1] = pkksv[sort[i] - 1];
    }
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		iconv[i - 1] = 1;
    }
    isavm1 = *isave - 1;
    i1 = isavm1;
    for (n = 1; n <= i1; ++n) {
		if (iconv[n - 1] != 0) {
			nplus1 = n + 1;
			i2 = *isave;
			for (k = nplus1; k <= i2; ++k) {
				if (iconv[k - 1] == 0) {
					goto L810;
				}
				if (ilrate[k] != ilrate[n]) {
					goto L810;
				}
				if (dur[k] != dur[n]) {
					goto L810;
				}
				if (lambda[k] != lambda[n]) {
					goto L810;
				}
				iconv[k - 1] = 0;
		L810:
				;
			}
		}
    }
    psum = 0.f;
    n = 1;
    i1 = *isave;
    for (i = 2; i <= i1; ++i) {
		if (iconv[i - 1] != 0) {
			++n;
			lambda[n] = lambda[i];
			dur[n] = dur[i];
			ilrate[n] = ilrate[i];
			ykkip[n - 1] = ykkip[i - 1];
			pkkip[n - 1] = pkkip[i - 1];
			pathsv[n] = pathsv[i];
			sort[n] = sort[i];
			p[n] = p[i];
			psum += p[n];
		}
    }
/* 	ALSO OBTAIN HIGHEST PROBABILITY NODE: */
    *isave = n;
    *pmax = 0.f;
    i1 = *isave;
    for (i = 1; i <= i1; ++i) {
		p[i] /= psum;
		if (p[i] > *pmax) {
			*pmax = p[i];
			*imax = i;
		}
    }
    return 0;
} /* savep_ */


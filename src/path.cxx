// ----------------------------------------------------------------------------
// path.c --  bayesian morse code decoder 
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


int morse::path_(integer *ip, integer *lambda, real *dur, integer *ilrate, integer *lamsav, real *dursav, integer *ilrsav)
{
     /* Local variables */
    static integer i, j, k, n, ixl, ixs, ilelm;



/*  PATH COMPUTES THE LTR STATE, DURATION, AND DATA RATE OF */
/*  EACH NEW PATH EXTENDED TO STATE N */

/*  VARIABLES: */
/*  IP-		SAVED PATH IDENTITY */
/*  LAMBDA-	LTR STATE OF SAVED PATH */
/*  DUR-		DURATION OF ELEMENT ON SAVED PATH */
/*  ILRATE-	DATA RATE OF ELEMENT ON SAVED PATH */
/*  LAMSAV-	NEW LTR STATES FOR EACH PATH EXTENSION */
/*  DURSAV-	NEW ELEM DURATIONS FOR EACH PATH EXTENSION */
/*  ILRSAV-	NEW DATA RATES FOR EACH PATH EXTENSION */
/*  J-		NEW PATH IDENTITY */
/*  THE LETTER TRANSITION TABLE, MEMFCN, IS STORED IN COMMON. */

/*  FOR EACH ELEM STATE K, AND EACH SPEED I, COMPUTE: */

    /* Parameter adjustments */
    --ilrsav;
    --dursav;
    --lamsav;

    /* Function Body */
    for (k = 1; k <= 6; ++k) {
		for (i = 1; i <= 5; ++i) {

/*  STATE IDENTITY N: */
			n = (i - 1) * 6 + k;
			
/*  NEW PATH IDENTITY: */
			j = (*ip - 1) * 30 + n;
			
/*  NEW LTR STATE: */

			if (*lambda != 0) {
				goto L50;
			}
			lamsav[j] = 0;
			goto L100;
	L50:
			lamsav[j] = memfcn[*lambda + k * 400 - 401];
			if (lamsav[j] == 0) {
				goto L100;
			}

/*  NEW DURATION: */
/*  OBTAIN KEYSTATE OF SAVED PATH AND NEW STATE: */
			ilelm = ilami[ielmst[*lambda - 1] - 1];
			ixl = ilamx[ilelm - 1];
			ixs = isx[k - 1];

/* CALCULATE DURATION - ADD SAMPLE DURATION 5 ms FOR EACH VALID PATH */
			dursav[j] = *dur * (1 - ixs - ixl + (ixs << 1) * ixl) + params.sample_duration;

/* 	NEW DATA RATE: */
			ilrsav[j] = *ilrate + (i - 3) * memdel[k-1][ilelm -1];
	L100:
			;
		}
    }
    return 0;
} /* path_ */


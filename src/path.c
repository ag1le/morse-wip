// ----------------------------------------------------------------------------
// path.c --  morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Morse.  

// Morse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// Morse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Morse.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include "morse.h"

/* Common Block Declarations */

struct {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam_;

#define blklam_1 blklam_

struct {
    integer memfcn[2400]	/* was [400][6] */;
} blkmem_;

#define blkmem_1 blkmem_

struct {
    integer isx[6];
} blks_;

#define blks_1 blks_

struct {
    integer memdel[36]	/* was [6][6] */;
} blkrat_;

#define blkrat_1 blkrat_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int path_(integer *ip, integer *lambda, real *dur, integer *ilrate, integer *lamsav, real *dursav, integer *ilrsav)
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
			lamsav[j] = blkmem_1.memfcn[*lambda + k * 400 - 401];
			if (lamsav[j] == 0) {
				goto L100;
			}

/*  NEW DURATION: */
/*  OBTAIN KEYSTATE OF SAVED PATH AND NEW STATE: */
			ilelm = blklam_1.ilami[blklam_1.ielmst[*lambda - 1] - 1];
			ixl = blklam_1.ilamx[ilelm - 1];
			ixs = blks_1.isx[k - 1];

/* CALCULATE DURATION - ADD SAMPLE DURATION 5 ms FOR EACH VALID PATH */
			dursav[j] = *dur * (1 - ixs - ixl + (ixs << 1) * ixl) + params.sample_duration;

/* 	NEW DATA RATE: */
			ilrsav[j] = *ilrate + (i - 3) * blkrat_1.memdel[ilelm + k * 6 - 7];
	L100:
			;
		}
    }
    return 0;
} /* path_ */


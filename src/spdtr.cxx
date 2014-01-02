// ----------------------------------------------------------------------------
// spdtr.c --  bayesian morse code decoder 
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



doublereal spdtr_(integer *isrt, integer *ilrt, integer *iselm, integer *ilelm)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static integer ind1, idel, idelsp, israte;


/* 	THIS FUNCTION RETURNS THE DATA RATE (SPEED) TRANSITION */
/* 	PROBABILITY BASED ON THE CURRENT ELEM TYPE. THE ALLOWABLE */
/* 	TRANSITION PROBS ARE STORED IN THE TABLE RTRANS. */

/* 	VARIABLES: */
/* 	ISRT	- DATA RATE IDENTITY FOR STATE TO WHICH PATH */
/* 		 	 IS BEING EXTENDED */
/* 	ILRT	- DATA RATE ON CURRENT PATH */
/* 	ISELM 	- ELEM TYPE FOR NEXT STATE */
/* 	ILELM	- ELEM TYPE ON CURRENT PATH */


/* 	IF SAVED ELEMENT AND NEW ELEMENT ARE THE SAME */
/* 	THEN THERE CAN BE NO SPEED CHANGE: */

    if (*ilelm != *iselm) {
		goto L100;
    }
    ret_val = 1.f;
    if (*isrt != 3) {
		ret_val = 0.f;
    }
    goto L300;

/* 	OTHERWISE, OBTAIN SPEED TRANSITION PROB */

L100:
    idel = blkrat.memdel[*ilelm + *iselm * 6 - 7];
    ind1 = blkspd.mempr[*ilelm + *iselm * 6 - 7];
    if (ind1 != 0) {
		goto L200;
    }
    ret_val = 0.f;
    goto L300;
L200:
    idelsp = (*isrt - 3) * idel;
    ret_val = blkspd.rtrans[*isrt + ind1 * 5 - 6];
    israte = *ilrt + idelsp;
    if (israte > 60) {
		ret_val = 0.f;
    }
    if (israte < 10) {
		ret_val = 0.f;
    }
L300:
    return ret_val;
} /* spdtr_ */


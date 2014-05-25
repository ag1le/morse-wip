// ----------------------------------------------------------------------------
// xtrans.c --  bayesian morse code decoder 
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
#include <math.h>

doublereal morse::xtrans_(integer *ielem, real *d0, integer *irate)
{
    /* Initialized data */

    static integer kimap[6] = { 1,3,1,3,7,14 };
    static real aparm[3] = { 3.f,1.5f,1.f };

    /* System generated locals */
    real ret_val;


    /* Local variables */
    static real b0, b1, p0, p1, alpha;
    static integer mscale;
    static real rscale;

/* 	THIS FUNCTION IMPLEMENTS THE CALCULATION OF KEYSTATE */
/* 	TRANSITION PROBABILITY, CONDITIONED ON ELEMENT TYPE, */
/* 	CURRENT DURATION, AND DATA RATE. */
/* 	VARIABLES: */
/* 	IELEM- 	INPUT CURRENT ELEMENT TYPE */
/* 	D0- 	INPUT CURRENT ELEMENT DURATION */
/* 	IRATE - INPUT CURRENT DATA RATE */

/* 	TABLES IN COMMON CONTAIN DENSITY PARMS FOR EACH ELEMENT TYPE, DATA RATE. */

/* 	SCALE DURATION AND OBTAIN DENSITY PARAMETER: */

    mscale = kimap[*ielem - 1];
    rscale = 1200.f / *irate;
    b0 = *d0 / (mscale * rscale);
    b1 = (*d0 + 5.f) / (mscale * rscale);
    
    switch (*ielem) {
    case 6:
	    alpha = aparm[2] * 14.f;
	    break;
    case 5:
	    alpha = aparm[1] * 7.f;    
	    break;
    default:
	    alpha = mscale * aparm[0];
    }

    if (b1 <= 1.f) {
		p1 = 1.f - exp(alpha * (b1 - 1.f)) * .5f;
		p0 = 1.f - exp(alpha * (b0 - 1.f)) * .5f;
		ret_val = p1 / p0;
	    return ret_val;
    }
    if (b0 < 1.f && b1 > 1.f) {
		p1 = exp(-alpha * (b1 - 1.f)) * -.5f;
		p0 = 1.f - exp(alpha * (b0 - 1.f)) * .5f;
		ret_val = p1 / p0;
	    return ret_val;
    }

    ret_val = exp(-alpha * (b1 - b0));
    return ret_val;
} /* xtrans_ */


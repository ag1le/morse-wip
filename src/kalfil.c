// ----------------------------------------------------------------------------
// kalfil.c -- bayesian morse code decoder 
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
#include <math.h> 


/* Initialized data */

struct BLKSV blksv = { .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, 
	    .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, .5f, 
	    .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, 
	    .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f, .1f };


int kalfil_(real *z, integer *ip, real *rn, integer *ilx, 
	integer *ixs, integer *kelem, integer *jnode, integer *israte, real *
	dur, integer *ilrate, real *pin, real *lkhdj)
{
    /* Initialized data */

    static real pinmin = 1e-4f;


    /* System generated locals */
    real r1;


    /* Local variables */
    static real a, g, qa, hz, pz, zr, phi, pkk, ykk, expa, pest;
    extern /* Subroutine */ int model_(real *, integer *, integer *, integer *, integer *, real *, real *, real *);
    static real ppred, ypred, pzinv;


/*   THIS SUBROUTINE COMPUTES THE ARRAY OF KALMAN FILTER */
/*   RECURSIONS USED TO DETERMINE THE LIKELIHOODS. */

/*   VARIABLES: */
/*       Z -	INPUT MEASUREMENT */
/*       IP -	INPUT PATH IDENTITY */
/*       RN -	INPUT NOISE POWER ESTIMATE */
/*       ILX -	INPUT SAVED KEYSTATE ON PATH IP */
/*       IXS -	INPUT KEYSTAT OF NEW NODE */
/*       KELEM -	INPUT ELEM STATE OF NEW NODE */
/*       ISRATE 	INPUT SPEED STATE OF NEW NODE */
/*       DUR - 	INPUT CURRENT DURATION OF ELEMENT ON IP */
/*       ILRATE 	INPUT SPEED STATE ON PATH IP */
/*       PIN - 	TRANS PROB FROM PATH IP TO NODE N */
/*       LKHDJ - OUTPUT CALCULATED LIKELIHOOD VALUE */

/*   SUBROUTINES USED */
/*       MODEL - OBTAINS THE SIGNAL-STATE-DEPENDENT LINEAR */
/*       	MODEL FOR THE KALMAN FILTER RECURSIONS */

/*   IF TRANSITION PROBABILITY IS VERY SMALL, DON'T */
/*   BOTHER WITH LIKELIHOOD CALCULATION: */

    if (*pin > pinmin) {
	goto L100;
    }
    *lkhdj = 0.f;
    goto L400;

/*   OBTAIN STATE-DEPENDENT MODEL PARAMETERS: */

L100:
    model_(dur, kelem, ilrate, israte, ixs, &phi, &qa, &hz);

/* 	GET PREVIOUS ESTIMATES FOR PATH IP */

    ykk = blksv.ykkip[*ip - 1];
    pkk = blksv.pkkip[*ip - 1];

/*  IMPLEMENT KALMAN FILTER FOR THIS TRANSITION */

    ypred = phi * ykk;
    ppred = phi * pkk * phi + qa;
    pz = hz * ppred + *rn;
    pzinv = 1.f / pz;
    g = ppred * hz * pzinv;
    pest = (1.f - g * hz) * ppred;
    zr = *z - hz * ypred;
    blksv.ykksv[*jnode - 1] = ypred + g * zr;
    blksv.pkksv[*jnode - 1] = pest;
    if (blksv.ykksv[*jnode - 1] <= .01f) {
	blksv.ykksv[*jnode - 1] = .01f;
    }
/* Computing 2nd power */
    r1 = zr;
    a = pzinv * .5f * (r1 * r1);
    if (a <= 1e3f) {
	goto L200;
    }
    *lkhdj = 0.f;
    goto L400;
L200:
    expa = exp(-a);
    *lkhdj = 1.f / sqrt(pz) * exp(-a);
    goto L400;
L400:
    return 0;
} /* kalfil_ */


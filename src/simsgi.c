// ----------------------------------------------------------------------------
// simsgi.c --  bayesian morse code decoder 
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


#include "f2c.h"

/* Common Block Declarations */

struct {
    real tau;
} blk1_;

#define blk1_1 blk1_

struct {
    real wc, wchirp, asigma, bsigma, phismg, rsigm, tchirp, gamm;
} blk2_;

#define blk2_1 blk2_

/* Table of constant values */

static real c_b2 = 6.28319f;

/* Subroutine */ int simsgi_(real *x, real *sig)
{
    /* Initialized data */

    static real xlast = 1.f;
    static real beta = 1.f;
    static real amp = 1.f;
    static real bfade = 0.f;
    static real theta = 1.f;
    static real phi = 1.f;

    /* Builtin functions */
    double exp(doublereal), r_mod(real *, real *), sin(doublereal);

    /* Local variables */
    static real w;
    static integer nc;
    static real tk;
    extern /* Subroutine */ int key_(real *, real *);
    static real dur, ampb, tdur, wchrp;

    dur = beta;
    key_(&dur, x);
    beta = beta * (1.f - *x - xlast + *x * 2.f * xlast) + 1.f;
    tk = *x * (1.f - xlast);
    xlast = *x;
/* 	CALL RANDN(W,1,0.,ASIGMA) */
    amp += tk * w;
    if (amp < .01f) {
	amp = .01f;
    }
/* 	CALL RANDN(W,1,0.,BSIGMA) */
    bfade = blk2_1.gamm * bfade + w;
    ampb = amp + bfade;
    if (ampb < .001f) {
	bfade = .001f - amp;
    }
    ampb = amp + bfade;
    tdur = blk1_1.tau * 1e3f * beta;
    wchrp = *x * blk2_1.wchirp * exp(-tdur / blk2_1.tchirp);
    theta += (nc + wchrp) * blk1_1.tau;
    theta = r_mod(&theta, &c_b2);
/* 	CALL RANDN(W,1,0.,PHISGM) */
    phi += tk * w;
    phi = r_mod(&phi, &c_b2);
    *sig = *x * ampb * sin(theta + phi);
/* 	CALL RANDN(ZN,1,0.,RSIGM) */
/* 	PRINT 100,DUR, X */
/* 100	FORMAT('SIMSG:', 2(2X,F10.3)) */
    return 0;
} /* simsgi_ */


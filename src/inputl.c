// ----------------------------------------------------------------------------
// inputl.c --  bayesian morse code decoder 
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

/* Common Block Declarations */

struct blk1_1_ {
    real tau;
};

#define blk1_1 (*(struct blk1_1_ *) &blk1_)

struct blk6_1_ {
    real dmean, xdur, esep[6], edev[6];
};

#define blk6_1 (*(struct blk6_1_ *) &blk6_)

struct {
    real wc, wchirp, asigma, bsigma, phisgm, rsigm, tchirp, gamm;
} blk2_;

#define blk2_1 blk2_

/* Initialized data */

struct {
    real e_1;
    } blk1_ = { 1.25e-4f };

struct {
    integer fill_1[1];
    real e_2[13];
    } blk6_ = { {0}, 0.f, 1.f, 3.f, 1.f, 3.f, 7.f, 14.f, 0.f, 0.f, 0.f, 0.f, 
	    0.f, 0.f };


/* Subroutine */ int inputl_(void)
{
    /* Format strings */
/*    static char fmt_100[] = "(1x,\002INPUT KEYING PARMS: RATE,MEAN ELEM DURA"
	    "TIONS\002)";
    static char fmt_150[] = "(1x,\002INPUT ELEM DURATION STD OEVIATIONS\002)";
    static char fmt_300[] = "(1x,\002INPUT SIG PARMS- AVAR,BVAR,FCHIRP,TCHIR"
	    "P,PHIVAR\002)";
    static char fmt_400[] = "(1x,\002INPUT SIG PARMS: GAMMA,FREQ,NOISE\002)";
*/
    /* Builtin functions */
//    integer s_wsfe(cilist *), e_wsfe(void);
//    double sqrt(doublereal);

    /* Local variables */
    static real fc, rc, avar, bvar, rate, fchirp, phivar, rnoise;

    /* Fortran I/O blocks */
 /*   static cilist io___1 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___2 = { 0, 6, 0, fmt_150, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_300, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_400, 0 };
*/

    goto L600;
//    s_wsfe(&io___1);
//    e_wsfe();
/* 	READ 200,RATE,(ESEP(K), K=1,6) */
//    s_wsfe(&io___2);
//    e_wsfe();
/* 	READ 200,(EDEV(K),K=1,6) */
/* L200: */
//    s_wsfe(&io___3);
//    e_wsfe();
/* 	READ 210,AVAR,BVAR,FCHIRP,TCHIRP,PHIVAR */
/* L210: */
//    s_wsfe(&io___4);
//    e_wsfe();
/* 	READ 220, GAMM,FC,RNOISE */
/* L220: */
L600:
/* 	ADDED BY MAURI */
    avar = 4.f;
    bvar = 4.f;
    rate = 25.f;
    fc = 4e3f;
    fchirp = 20.f;
    rnoise = 4.f;
    phivar = 4.f;
    blk2_1.tchirp = 2.f;
    blk2_1.gamm = 1.f;
    blk2_1.asigma = sqrt(avar);
    blk2_1.bsigma = sqrt(bvar);
    blk2_1.phisgm = sqrt(phivar);
    blk2_1.rsigm = sqrt(rnoise);
    blk6_1.dmean = 1200.f / rate;
    rc = fc * 6.28319f;
    blk2_1.wchirp = fchirp * 6.2831f;
/* 	IF (ESEP(1).NE.0.) GO TO 500 */
    blk6_1.esep[0] = 1.f;
    blk6_1.esep[1] = 3.f;
    blk6_1.esep[2] = 1.f;
    blk6_1.esep[3] = 3.f;
    blk6_1.esep[4] = 7.f;
    blk6_1.esep[5] = 14.f;
/* L500: */
    return 0;
} /* inputl_ */


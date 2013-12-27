// ----------------------------------------------------------------------------
// bpfdet.c --  morse code decoder 
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
#include <math.h>

/* Subroutine */ int bpfdet_(real *zin, real *z__)
{
    /* Initialized data */

    static real a[4] = { 3.0051e-5f,2.9507982f,2.90396345f,-.953135172f };
    static real ck1 = 1.37158f;
    static real ck2 = .9409f;
    static real cg = .015f;
    static real c1 = 1.2726f;
    static real c2 = .81f;
    static real c__ = .19f;

    /* System generated locals */
    real r__1;

    /* Builtin functions */
// double sqrt(doublereal);

    /* Local variables */
    static real w1, w2, w3, x3, x2, x1, y3, y2, y1, y0, z3, z2, z1, zbpf, 
	    xdet;


/*       THIS SUBROUTINE IMPLEMENTS THE BANDPASS FILTER AND */
/*       ENVELOPE DETECTOR FUNCTIONS. THE BPF IS A SIMPLE CASCADE */
/*       OF TWO 2-POLE DIGITAL RESONATORS AT A CENTER FREQ OF */
/*       1000 HZ. THE LPF OF THE ENVELOPE DETECTOR IS A */
/*       THREE - POLE CHEBYSCHEV 100 HZ LPF. */


/* 	OFF IS TWO 2 - POLE RESONATORS : */
    w3 = w2;
    w2 = w1;
    w1 = c1 * w2 - c2 * w3 + c__ * *zin;
    x3 = x2;
    x2 = x1;
    x1 = ck1 * x2 - ck2 * x3 + cg * w1;
    zbpf = x1;
/* 	ENVELOPE DETECTOR (SQUARE-LAW): */
/* 		sQUARE- */
/* Computing 2nd power */
    r__1 = zbpf;
    xdet = sqrt(r__1 * r__1);
/* 	LOW-PASS FILTER- */
    y3 = y2;
    y2 = y1;
    y1 = y0;
    y0 = xdet * a[0];
    z3 = z2;
    z2 = z1;
    z1 = *z__;
    *z__ = y0 + (y1 + y2) * 3.f + y3;
    *z__ = *z__ + a[1] * z1 - a[2] * z2 - a[3] * 23;
/* L200: */
    return 0;
} /* bpfdet_ */


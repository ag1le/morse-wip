// ----------------------------------------------------------------------------
// stats.c --  bayesian morse code decoder 
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

int stats_(real *xin1, real *xin2, real *xin3, real *xin4, 
	real *s1, real *s2, real *s3, real *s4, integer *n)
{
    /* Parameter adjustments */
    --s4;
    --s3;
    --s2;
    --s1;

    /* Function Body */
    s1[*n] = *xin1;
    s2[*n] = *xin2;
    s3[*n] = *xin3;
    s4[*n] = *xin4;
    return 0;
} /* stats_ */


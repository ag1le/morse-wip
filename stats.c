/* stats.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Subroutine */ int stats_(real *xin1, real *xin2, real *xin3, real *xin4, 
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

#ifdef __cplusplus
	}
#endif

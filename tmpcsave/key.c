/* key.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"
#include "common.h"
#include <stdio.h>
#include <math.h>

//#define DEBUG 1 

/* Common Block Declarations */



/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int key_(real *dur, real *x)
{
    /* Initialized data */

    static integer ik = 0.5;
    static integer row = 0;
    static integer col = 0;
    static integer n = 0;
    static integer nltr = 1;

    static integer morse[10][40]	 =  {
		1,3,2,0,0,0,0,0,0,0, 2,3,1,3,1,3,1,0,0,0, 2,3,1,3,2,3,1,0,0,0, 2,3,1,3,1,0,0,0,0,0,	// ABCD
		1,0,0,0,0,0,0,0,0,0, 1,3,1,3,2,3,1,0,0,0, 2,3,2,3,1,0,0,0,0,0, 1,3,1,3,1,3,1,0,0,0, // EFGH
		1,3,1,0,0,0,0,0,0,0, 1,3,2,3,2,3,2,0,0,0, 2,3,1,3,2,0,0,0,0,0, 1,3,2,3,1,3,1,0,0,0, // IJKL
		2,3,2,0,0,0,0,0,0,0, 2,3,1,0,0,0,0,0,0,0, 2,3,2,3,2,0,0,0,0,0, 1,3,2,3,2,3,1,0,0,0, // MNOP
		2,3,2,3,1,3,2,0,0,0, 1,3,2,3,1,0,0,0,0,0, 1,3,1,3,1,0,0,0,0,0, 2,0,0,0,0,0,0,0,0,0, // QRST
		1,3,1,3,2,0,0,0,0,0, 1,3,1,3,1,3,2,0,0,0, 1,3,2,3,2,0,0,0,0,0, 2,3,1,3,1,3,2,0,0,0, // UVWX
		2,3,1,3,2,3,2,0,0,0, 1,3,1,3,2,3,2,3,2,0, 1,3,2,3,2,3,2,3,2,0, 1,3,1,3,2,3,2,3,2,0, // YZ12
		1,3,1,3,1,3,2,3,2,0, 1,3,1,3,1,3,1,3,2,0, 1,3,1,3,1,3,1,3,1,0, 2,3,1,3,1,3,1,3,1,0, // 3456
		2,3,2,3,1,3,1,3,1,0, 2,3,2,3,2,3,1,3,1,0, 2,3,2,3,2,3,2,3,1,0, 2,3,2,3,2,3,2,3,2,0, // 7890
		0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0 };


	// 6 morse symbols:  1=dot(.) 2=dash(-) 3=element space(^)  4=char space (~) 5=word space(W) 6=pause(P)
    static char isymbl[6] = { ".-^~WP"};


    /* Local variables */
    static integer k, l;
    static real y;
    static integer k1, k2, iy;
    static real xm, beta;
	extern double randn(real mean, real sigma);
    static integer ielm, kait;
    static real tend, xsigm;
    static char ioutp[500];


    beta = 1e3f * blk1.tau * *dur;
    if (beta < blk6.xdur) {
	goto L200;
    }

// Get Morse element from morse table [row][col]
    ++col;
    ielm = morse[row][col];
    if (ielm != 0) {
	goto L100;
    }

    col = 0;
    y = randn(ik,2);
    ielm = 4;
    if (y > .9f) {
		ielm = 5;
    }
    if (y <= .9f && y > .3f) {
		ielm = 6;
    }

//   implement random characters here 	
//    y = rand(36);
//    y = (y - .001f) * 35 + 1.f;
//    iy = y;
//    ltr = iy + 1;
	row +=1;
	if (row >= 10)  
		row =0;
    goto L100;

// Fetch letter from pre-loaded text - not working now 
    ++nltr;
    row = blktxt.itext[nltr - 1];

    if (row == 0) {
		ielm = 4;
    }
    if (row == 37) { // %
		ielm = 5;
    }
    if (row == 38) { // & 
		ielm = 6;
    }

    ++nltr;
    row = blktxt.itext[nltr - 1];

L100:
// collect morse symbols into buffer ioutp until 300 and then print 
    ++n;
    ioutp[n - 1] = isymbl[ielm - 1]; 
#ifdef DEBUG
	printf("\nn:%d isymbl[%d]:%c col:%d row:%d",n,(ielm-1),isymbl[ielm-1],col,row);
#endif
    if (n >= 300) {
		printf("\nEND OF RUN; INPUT DATA WAS: %s", ioutp);
//		for (n=0; n<301; n++) 
//			ioutp[n] = 0; 
		n = 0;
    }

L110:
    xm = blk6.esep[ielm - 1] * blk6.dmean;
    xsigm = blk6.edev[ielm - 1] * blk6.dmean;

// implement random duration later 
//    y = randn(ik,2);
//    y = (y - .5f) * 2.f;
//    blk6.xdur = xm + y + xsigm;

    blk6.xdur = xm + xsigm;

    if (blk6.xdur < 20.f) {
		blk6.xdur = 20.f;
    }

	// OUTPUT: mark = 1.0  space = 0.0 
    *x = 1.f;
    if (ielm >= 3) {
	*x = 0.f;
    }

L200:
    return 0;
} /* key_ */

#undef isymbl



/* path.f -- translated by f2c (version 20100827).
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

//#define DEBUG 1

/* Common Block Declarations */

 int path_(integer ip, integer *lambda, real *dur, integer *ilrate, integer lamsav[][25], real dursav[][25], integer ilrsav[][25])
{
    static integer i, j, k, n, ixl, ixs, ilelm;


/*  PATH COMPUTES THE LTR STATE, DURATION, AND DATA RATE OF */
/*  EACH NEW PATH EXTENDED TO STATE N */

/*  VARIABLES: */
/*  IP-			SAVED PATH IDENTITY */
/*  LAMBDA		LTR STATE OF SAVED PATH */
/*  DUR			DURATION OF ELEMENT ON SAVED PATH */
/*  ILRATE		DATA RATE OF ELEMENT ON SAVED PATH */
/*  LAMSAV		NEW LTR STATES FOR EACH PATH EXTENSION */
/*  DURSAV		NEW ELEM DURATIONS FOR EACH PATH EXTENSION */
/*  ILRSAV		NEW DATA RATES FOR EACH PATH EXTENSION */
/*  J			NEW PATH IDENTITY */
/*  THE LETTER TRANSITION TABLE, MEMFCN, IS STORED IN COMMON. */

/*  FOR EACH ELEM STATE K, AND EACH SPEED I, COMPUTE: */
	for (k = 0; k < 6; ++k) {			// ELEM STATE K
		for (i = 0; i < 5; ++i) {		// SPEED I  


/*  STATE IDENTITY N: */
	    	n = (i ) * 6 + k;
/*  NEW PATH IDENTITY: */
	    	j = (ip) * 30 + n;

/*  NEW LTR STATE: */

	    	if (*lambda == 0) {
		    	lamsav[n][ip] = 0;
		    	goto L100;
	    	}
	    	lamsav[ip][n] = blkmem.memfcn[k][*lambda-1];
	    	if (lamsav[n][ip] == 0) {
				goto L100;
	    	}
/*  NEW DURATION: */
/*  OBTAIN KEYSTATE OF SAVED PATH AND NEW STATE: */

	    	ilelm = blklam.ilami[blklam.ielmst[*lambda - 1] - 1];
	    	ixl = blklam.ilamx[ilelm - 1];
	    	ixs = blks.isx[k];
/* CALCULATE DURATION: Phi_k  number of samples since last state transition 
/ Page 90  Phi_k = Phi_k-1(1- x_k - x_k-1 + 2* x_k*x_k-1) +1  */
	    	dursav[n][ip] = *dur * (1 - ixs - ixl + 2*ixs*ixl) * 5.f;
/* 	NEW DATA RATE: */
	    	ilrsav[n][ip] = *ilrate + (i - 2) * blkrat.memdel[k][ilelm];

L100:
#ifdef DEBUG
printf("\nPATH: ilrsav[%2d][%2d]:%2d ip:%2d n:%2d k:%d i:%d ilrate:%2d ilelm:%d ixl:%d ixs:%d \t memdel[%d][%d]:%d dursav[%3d][%3d]:%f", 
				 n,ip, ilrsav[n][ip], ip,   n,   k,   i,   *ilrate,  ilelm,   ixl,   ixs,   k, ilelm, blkrat.memdel[k][ilelm],n,ip,dursav[n][ip]);
#endif

	    	;
		}
    }

    return 0;
} /* path_ */


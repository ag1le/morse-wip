/* probp.f -- translated by f2c (version 20100827).
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

int probp_(real p[][25], real pin[][25], integer *isave, real lkhd[][25])
{

    /* Local variables */
    static integer i, j, n;
    static real pmax, psav[30][25], psum;


/* 		PROBP COMPUTES THE POSTERIOR PROBABILITY OF EACH NEW PATH */

/* 		VARIABLES: */
/* 		P-		INPUT: SAVED PROBS OF PRIOR PATHS */
/* 		OUTPUT:	COMPUTED POSTERIOR PROBS OF NEW PATHS */
/* 		PIN-		INPUT TRANSISTION PROBABILITIES */
/* 		LKHD-		INPUT LIKLIEHOODS OF EACH TRANSTION */
/* 		PSUM-		NORMALIZING CONSTANT (SUM OF P(J)) */


    /* Function Body */
    pmax = 0.f;
    psum = 0.f;
/* 	FOR EACH SAVED PATH, EACH TRANSITION: */
    for (i = 0; i < *isave; ++i) {
		for (n = 0; n < 30; ++n) {
/* 		COMPUTE IDENTITY OF NEW PATH: */
		    j = i*30 + n;
/*      PRODUCT OF PROBS, ADD TO PSUM */
		    psav[n][i] = p[n][i] * pin[n][i] * lkhd[n][i];
		    psum += psav[n][i];
#ifdef DEBUG
printf("\nPROBP: psum:%f psav[%3d]:%f p[%d][%d]:%f pin[%2d][%2d]:%f lkhd[%3d]:%f", psum, j,psav[j],n,i,p[n][i],n,i,pin[n][i],j,lkhd[j]);
#endif 
		    if (psav[n][i] > pmax) {
			    pmax = psav[n][i];
		    }
		}
    }
/* 		NORMALIZE TO GET PROBABILITIES; SAVE: */
    for (j = 0; j < *isave; ++j) {
		for (n = 0; n < 30; n++) {
			p[n][j] = psav[n][j] / psum;
		}
    }
    return 0;
} /* probp_ */


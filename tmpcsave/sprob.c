/* sprob.f -- translated by f2c (version 20100827).
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

int sprob_(real p[][25], integer *isave, integer ilrsav[][25], real *pelm, integer *khat, real *spdhat, real *px)
{
    /* Local variables */
    static integer i, j, k, m, n;
    static real pselem[6];


/*    SPROB COMPUTES THE POSTERIOR PROBS OF THE ELEMENT */
/*    STATES, DATA RATE STATES, AND KEYSTATES BY SUMMING */
/*    OVER THE APPROPRIATE PATHS. */

/*    VARIABLE: */
/*    P     		INPUT PATH PROBABILITIES */
/*    ISAVE			NUMBER OF PATHS SAVED */
/*    PSELEM		OUTPUT ELEMENT PROB */
/*    SPDHAT		OUTPUT SPEED ESTIMATE (DATA RATE WPM) */
/*    PX			OUTPUT KEYSTATE PROBABILITY */



    /* Function Body */
    *spdhat = 0.f;
    *px = 0.f;

/* 	FOR EACH STATE EXTENSION OF PATH M: */
/* 	OBTAIN ELEMENT STATE PROBS,KEYSTATE PROBS,SPEED EST: */
    for (k = 0; k < 6; ++k) {  
		pselem[k] = 0.f;
		for (i = 0; i < 5; ++i) {
		    n = (i*6) + k;
		    for (m = 0; m < *isave; ++m) {
				j = (m*30) + n;
				pselem[k] += p[n][m];
				*spdhat += ilrsav[n][m] * p[n][m];
#ifdef DEBUG
printf("\nSPROB: pselem[%d]:%f spdhat:%f ilrsav[%3d][%3d]:%d \t p[%3d][%3d]:%f \tpx:%f", k, pselem[k], *spdhat, n,m,ilrsav[n][m], n,m, p[n][m],*px);
#endif 
				if (k < 2) {	// KEYSTATE DOT (0) OR DASH (1) 
					*px += p[n][m];
				}

L100:
			;
		    }
		}
    }
    *pelm = 0.f;
    for (k = 0; k < 6; ++k) {
		if (pselem[k] >= *pelm) {
			*pelm = pselem[k ];
			*khat = k;
		}
    }
    return 0;
} /* sprob_ */


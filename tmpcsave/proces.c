/* proces.f -- translated by f2c (version 20100827).
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

#define DEBUG 1


int proces_(real *z, real *rn, integer *xhat, real *px, integer *elmhat, integer *ltrhat)
{
    /* Initialized data */

    static integer isave = 25;
    static integer lambda[25] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5 };
    static integer ilrate[25] = { 10,10,10,10,10,20,20,20,20,20,30,30,30,30,
	    30,40,40,40,40,40,50,50,50,50,50 };

    static real dur[25] = { 1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,
	    1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,
	    1e3f,1e3f };

  
    /* Local variables */
    static integer i, k, inl;
	static integer init = 0; 
	static real spdhat;
	static real pelm;
	static integer khat;
  
    static real pin[30][25];	// N: 5 spd x 6 morse states I: 25 paths  - transition probability from path I to state N 
    static real lkhd[30][25];		// 5 speeds x 6 morse states x 25 paths = 750 likelyhoods 
	static integer ilrsav[30][25];
    static real dursav[30][25];
    static integer lamsav[30][25]; 
    static real p[30][25]; 
    
    static integer imax, sort[25];
    static integer pathsv[25];
    static integer ipath;


	if (init == 0) {
		init = 1; 
		for (k= 0; k< 30; k++) {
			for (i = 0; i<25; i++) {
				ilrsav[k][i] = 0; 
				lamsav[k][i] = 5; 
				p[k][i] = 1.0;
			}
		}
	}

/* 	THIS SUBROUTINE IMPLEMENTS THE PROCESSING ALGORITHM */
/* 	FOR JOINT DEMODULATION, DECODING, AND TRANSLATION OF */
/* 	THE RECEIVED MORSE PROCESS. IT TAKES IN A NEW MEASUREMENT, Z */
/*  OF THE DETECTED SIGNAL EVERY 5 MSEC AND PRODUCES AN ESTIMATE */
/*  OF THE CURRENT KEYSTATE, ELEMENT STATE, AND LETTER OF THE RECEIVED SIGNAL. */


/* 	DEFINITIONS OF VARIABLE NAMES: */
/* 	Z- 			INPUT SAMPLE OF DETECTED SIGNAL */
/* 	RN- 		INPUT NOISE POWER ESTIMATE */
/* 	XHAT- 		OUTPUT ESTIMATE OF KEYSTATE */
/* 	ELMHAT- 	OUTPUT ESTIMATE OF ELEMENT STATE */
/* 	LTRHAT- 	OUTPUT ESTIMATE OF LETTER STATE */


/* 	ISAVE- 		NO. OF PREVIOUS PATHS SAVED */
/* 	IPATH- 		IDENTITY OF SAVED PATH */
/* 	LAMBDA (I) 	IDENTITY OF LTR STATE OF SAVED PATH I */
/* 	DUR (I)- 	DURATION OF ELEMENT ON PATH I */
/* 	ILRATE(I)- 	IDENTITY OF DATA RATE ON PATH I */
/* 	PIN (I,N)- 	COMPUTED TRANS PROB FROM PATH I TO STATE N */
/* 	LAMSAV(J)- 	IDENTITY OF LTR STATE AT NEW NODE J */
/* 	ILRSAV(J)- 	IDENTITY OF DATA RATE AT NEW NODE J */
/* 	LKHD(J)- 	LIKELIHOOD VALUE FOR NODE J */
/* 	P(J)- 		COMPUTED POSTERIOR PROB OF PATH ENDING AT NEW NODE J */
/* 	PSELEM(K)-	COMPUTED POSTERIOR PROB OF ELEM K */
/* 	SPDHAT -	COND MEAN ESTIMATE OF INSTANT DATA RATE */
/* 	PX- 		POSTERIOR PROB THAT KEYSTATE EQUALS 1 */

/* 	THE FOLLOWING SUBROUTINES ARE UTILIZED: */
/* 	TRPROB- COMPUTES TRANSITION PROBABILITIES */
/* 	PATH- 		COMPUTES IDENTITY OF NEW PATHS */
/* 	LIKHD- 		COMPUTES THE LIKELIHOOD OF EACH PATH EXTENSION */
/* 	PROBP- 		COMPUTES POSTERIOR PROBS OF EACH NEW PATH */
/* 	SPROB- 		COMPUTES POSTERIOR PROBS OF EACH STATE */
/* 	SAVE- 		SAVES THE HIGHEST PROB PATHS */
/* 	TRELIS- 	FORMS A TRELIS OF SAVED PATHS */
/* 	TRANSL- 	TRANSLATES THE LETTER ESTIMATE */

/* 	ALL TABLES OF CONSTANTS ARE STORED IN COMMON. */
/* 	FOR EACH SAVED PATH, COMPUTE: */
/* 	TRANSITION PROBABILITY TO NEW STATE (TRPROB); */
/* 	IDENTITY OF EACH NEW PATH EXTENDED (PATH); */
/* 	LIKELIHOOD OF EACH STATE EXTENSION (LIKHD); */

		for (k= 0; k< 30; k++) {
			for (i = 0; i<25; i++) {
				p[k][i] = 1.0;
			}
		}

    for (i = 0; i < isave; ++i) {
		trprob_(i, &lambda[i], &dur[i], &ilrate[i], pin);
		path_(i, &lambda[i], &dur[i], &ilrate[i], lamsav, dursav, ilrsav);
		likhd_(z, rn, i, &lambda[i], &dur[i], &ilrate[i], pin, lkhd);
    }
/* 	HAVING OBTAINED ALL NEW PATHS, COMPUTE: */
/* 	POSTERIOR PROBABILITY OF EACH NEW PATH(PROBP); */
/* 	POSTERIOR PROBABILITY OF KEYSTATE, ELEM STATE, */
/* 	CONDITIONAL MEAN ESTIMATE OF SPEED(SPROB); */

	probp_(p, pin, &isave, lkhd);
    sprob_(p, &isave, ilrsav, &pelm, &khat, &spdhat, px);

#ifdef DEBUG
printf("\nPROCES: z:%f\tpx:%f\tspdhat:%3.2f\tisave:%d\tpelm:%f\tkhat:%d",*z, *px,spdhat, isave, pelm, khat);
#endif

    *xhat = 0;
    if (*px > .5f) {
		*xhat = 1;
    }
/* 	SAVE THE PATHS WITH HIGHEST PROBABILITY, AND STORE THE VALUES CORRESPONDING TO THESE PATHS: */
	savep_(p, pathsv, &isave, &imax, lamsav, dursav, ilrsav, lambda, dur, ilrate, sort);

/* 	UPDATE TRELLIS WITH NEW SAVED NODES, AND OBTAIN LETTER STATE ESTIMATE: */
	//trelis_(&isave, pathsv, lambda, &imax);

    return 0;
} /* proces_ */


/* savep.f -- translated by f2c (version 20100827).
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

int savep_(real p[][25], integer *pathsv, integer *isave, integer *imax, integer lamsav[][25], real dursav[][25], integer ilrsav[][25], integer *lambda, real *dur, integer *ilrate, integer *sort)
{
    /* Initialized data */

    static real popt = .9f;


    /* Local variables */
    static integer i, j, k, n;
    static integer ip, jsav;
    static integer nsav,savn,nsave[25];
    static integer iconv[25], ipsav, isavm1, nplus1;

    static real pmax;
    static real psav[25], psum;


/* 	THIS SUBROUTINE PERFORMS THE ALGORITM TO SAVE */
/* 	THE PATHS WITH HIGHEST POSTERIOR PROBABILITY. */
/* 	IT WILL SAVE A MINIMUM OF 7 PATHS (ONE FOR EACH */
/* 	ELEMENT STATE AND ONE ADDITIONAL NODE), AND */
/* 	A MAXIMUM OF 25 PATHS.  WITHIN THESE LIMITS, IT */
/* 	SAVED ONLY ENOUGH TO MAKE THE TOTAL SAVED PROBABILITY */
/* 	EQUAL TO POPT. */


/* 	ADDITIONALLY, IT RESORTS THE LAMBDA,DUR,AND ILRATE */
/* 	ARRAYS TO CORRESPOND TO THE SAVED NODES. */


/* 	VARIABLES: */
/* 		P-		INPUT PROBABILITY ARRAY OF NEW NODES */
/* 		PATHSV-	OUTPUT ARRAY OF THE PREVIOUS NODES TO */
/* 				WHICH THE SAVED NODES ARE CONNECTED. */
/* 		ISAVE-	INPUT: NO. OF PREVIOUS NODES SAVED */
/* 				OUPUT: NO. OF NODES SAVED AT CURRENT STAGE */
/* 		IMAX-	INDEX OF HIGHEST PROBABILITY NODE */
/* 		LAMSAV-	INPUT ARRAY OF LTR STATES AT EACH NEW NODE */
/* 		DURSAV-	INPUT ARRAY OF SAVED DURATIONS */
/* 		ILRSAV-	INPUT ARRAY OF SAVED RATES */
/* 		LAMBDA-	OUTPUT ARRAY OF SAVED LTR STATES, SORTED ACCORDING TO PROBABILITY */
/* 		DUR-	OUTPUT ARRAY OF SORTED DURATIONS */
/* 		ILRATE-	OUTPUT ARRAY OF SORTED RATES */



    /* Function Body */
    nsav = 0;
    psum = 0.f;
	jsav = 0;
/* 	SELECT SIX HIGHEST PROB ELEMENT STATE NODES: */


	for (k = 0; k < 6; ++k) {
		pmax = 0.f;
	    for (i = 0; i < 5; ++i) {
			n = 6*i+k;
			for (ip = 0; ip < *isave; ++ip) {
				j = (ip ) * 30 + (i) * 6 + k;
#ifdef DEBUG
//printf("\nSAVEP:p[%d][%d]:%f pmax:%f jsav:%d", n,ip,p[n][ip],pmax,jsav);
#endif
				if (p[n][ip] >= pmax) {
					pmax = p[n][ip];
					jsav = j;
					savn = n;
					ipsav = ip;
				}
	    	}
		}
		if (pmax >= 0) { //1e-6f) {
			psum += pmax;
			psav[nsav] = pmax;
			nsave[nsav] = savn;
			pathsv[nsav] = ipsav;
			sort[nsav] = jsav;
#ifdef DEBUG
printf("\nSAVEP: psav[%d]:%f nsave[%d]:%d pathsv:%d sort[%d]:%d pmax:%f k:%d i:%d j:%d ip:%d", nsav,psav[nsav],nsav,nsave[nsav], pathsv[nsav],nsav, sort[nsav],pmax,k,i,j,ip);
#endif
			++nsav;
		}
    }
/* 	SELECT ENOUGH ADDITIONAL NODES TO MAKE TOTAL */
/* 	PROBABILITY SAVED EQUAL TO POPT, OR A MAX OF 25: */
	do {
		pmax = 0.f;
		for (ip = 0; ip < *isave; ++ip) {
			for (n = 0; n < 30; ++n) {
				j = ip*30 + n;
				for (i = 0; i < nsav; ++i) {
					if (j == sort[i]) {
						goto L500;
					}
				}
				if (p[n][ip] > pmax) {
					pmax = p[n][ip];
					jsav = j;
					savn = n; 
					ipsav = ip;
				}
	L500:
				;
			}
		}
		psum += pmax;
		psav[nsav] = pmax;
		nsave[nsav] = savn;
		pathsv[nsav] = ipsav;
		sort[nsav] = jsav;
#ifdef DEBUG
printf("\nSAVEP: psum:%f psav[%d]:%f nsave[%d]:%d pathsv[%d]:%d sort[%d]:%d", psum, nsav,psav[nsav], nsav,nsave[nsav],nsav, pathsv[nsav], nsav, sort[nsav]);
#endif
		++nsav;
		if (psum >= popt) {
			break; //goto L600;
		}
	}
    while (nsav < 25);  

L600:
/* 	NEW ISAVE EQUALS NO. OF NODES SAVED: */
#ifdef DEBUG
//printf("\nNEW ISAVE EQUALS # OF NODES SAVED:%d", nsav);
#endif
  //  *isave = nsav;

/* 	SORT THE SAVED ARRAYS TO OBTAIN THE ARRAYS */
/* 	TO BE USED FOR THE NEXT ITERATION: */
/* 	ALSO OBTAIN HIGHEST PROBAILITY NODE: */
    for (i = 0; i < *isave; ++i) {
//		p[i] = psav[i] / psum;
		lambda[i] = lamsav[nsave[i]][pathsv[i]];  //[sort[i]];
		dur[i] = dursav[nsave[i]][pathsv[i]];     //[sort[i]];
		ilrate[i] = ilrsav[nsave[i]][pathsv[i]];  //[sort[i]];
		blksv.ykkip[i] = blksv.ykksv[sort[i]];
		blksv.pkkip[i] = blksv.pkksv[sort[i]];
#ifdef DEBUG
//printf("\nSAVEP: p[%2d]:%f psav[%2d]:%f lambda[%2d]:%d  dur[%2d]:%f ilrate[%2d]:%d ykkip[%2d]:%f isave:%d psum:%f", i, p[i], i ,psav[i], i, lambda[i],i,dur[i], i, ilrate[i], i, blksv.ykkip[i],*isave,psum);
#endif
    }

    for (i = 0; i < *isave; ++i) {
		iconv[i] = 1;
    }
	// compare: if speedrate, duration and letter state has not changed then set iconv[k] to zero 
    for (n = 0; n < (*isave-1); ++n) {
		if (iconv[n] == 0) 			    goto L800;
		nplus1 = n + 1;
		for (k = nplus1; k < *isave; ++k) {
		    if (iconv[k] == 0) 			goto L810;
		    if (ilrate[k] != ilrate[n]) goto L810;
		    if (dur[k] != dur[n]) 		goto L810;
		    if (lambda[k] != lambda[n]) goto L810;
#ifdef DEBUG
//printf("\nSAVEP: ICONV[k:%d]=0 n:%d",k,n);
#endif
		    iconv[k] = 0;
L810:
		    ;
		}
L800:
		;
    }
/*
    psum = 0.f;
    n = 0;
    for (i = 0; i < *isave; ++i) {
		if (iconv[i] != 0) {
			++n;
			lambda[n] = lambda[i];
			dur[n] = dur[i];
			ilrate[n] = ilrate[i];
			blksv.ykkip[n] = blksv.ykkip[i];
			blksv.pkkip[n] = blksv.pkkip[i];
			pathsv[n] = pathsv[i];
			sort[n] = sort[i];
			p[n] = p[i];
			psum += p[n];
		}
    }
//printf("\nSAVEP: NEW ISAVE %d", n);

 //   *isave = n;

    pmax = 0.f;
    for (i = 1; i < *isave; ++i) {
		p[i] /= psum;
		if (p[i] > pmax) {
			pmax = p[i];
			*imax = i;
		}

    }
*/
    return 0;
} /* savep_ */


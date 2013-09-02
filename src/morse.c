/* morse.f -- translated by f2c (version 20100827).
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
#include <stdio.h>
#include <math.h>
#include "morse.h"
 
/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static real rn = .1f;
    static integer np = 0;

	int s_stop(char *, ftnlen);

    /* Local variables */
    static integer n;
    static real x, z;
    static integer n1, n2;
    static real s1[512], s2[512], s3[512], s4[512], px;
    static integer imax, xhat;
    static real pmax, zdet, zsig;
    static real zrcv, zout;
    static integer elmhat;
    static real spdhat;
    static integer ltrhat;
    int res; 

	FILE *fp; 

/* 	INITIALIZE DATA STRUCTURES */
    initl_();
    inputl_();
    
   fp = fopen("x.txt","r"); 
    	
    

L1:
    for (n1 = 1; n1 <= 512; ++n1) {
	for (n2 = 1; n2 <= 18; ++n2) {
	    simsgi_(&x, &zsig);
	    res = fscanf(fp,"%f",&x); 
	    if ( res != 1) { 
			fclose(fp); 
			fp = fopen("x.txt","r");
			x = 0.0;
	    }
	    rcvr_(&zsig, &zrcv);
	    bpfdet_(&zrcv, &zdet);
	    ++np;
/* 	DECIMATE 4 kHz by 40  down to 100Hz - 5 ms sample time for PROCES */
	    if (np < 20) {
		goto L3;
	    }
	    np = 0;
	    noise_(&zdet, &rn, &zout);
/* 	RN = RAND() */
	    rn = .01f;
	    proces_(&x, &rn, &xhat, &px, &elmhat, &ltrhat, &spdhat, &imax, &pmax);
//	    printf("\n %f %d %f %d %f ",x,xhat,px, elmhat, spdhat); 


L3:
	    ;
	}
	n = n1;
#ifdef DEBUG
printf("\nMORSE: %f %f %d %d %f %f %f",x,pmax,imax,elmhat,zsig,rn,spdhat);
#endif
	stats_(&zdet, &z, &px, &xhat, s1, s2, s3, s4, &n);
/* L2: */
    }
/* 	CALL DISPLA(S1,S2,S3,S4) */
    goto L1;
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/* Main program alias */ int morse_ () { MAIN__ (); return 0; }
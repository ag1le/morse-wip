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
#include "common.h"
#include <stdio.h>

//#define DEBUG 1 



/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static real rn = .1f;
    static integer np = 0;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer n;
    static real x, z;
    static integer n1, n2;
    static real s1[512], s2[512], s3[512], s4[512], dp, px;
    static integer xhat;
    static real zdet, zsig;
    extern /* Subroutine */ int rcvr_(real *, real *);
    static real zrcv;
    extern /* Subroutine */ int noise_(real *, real *, real *), initl_(void), 
	    stats_(real *, real *, real *, real *, real *, real *, real *, 
	    real *, integer *), bpfdet_(real *, real *);
    static integer elmhat;
    extern /* Subroutine */ int simsgi_(real *, real *), proces_(real *, real 
	    *, integer *, real *, integer *, integer *);
    static integer ltrhat;
    extern /* Subroutine */ int inputl_(void);
	static int sample = 0; 

	FILE *fp;

	fp = fopen("data.txt","r");
	if (fp == NULL) {
		perror("Error opening file");
		return (-1);
	}

    initl_();
    inputl_();

#ifdef DEBUG
printf("\nsample\tx\tzsig\tzrcv\tzdet\tz\trn\txhat\tpx");
#endif
L1:
    for (n1 = 1; n1 <= 512; ++n1) {
	for (n2 = 1; n2 <= 18; ++n2) {

//
//	if (fscanf(fp,"%f",&x) !=1) {
//		return 0;
//	}
	sample++; 
//printf("\nMORSE: n1:%d n2:%d sample:%d x:%f", n1,n2, sample,x);

	    simsgi_(&x, &zsig);
	    rcvr_(&zsig, &zrcv);
	    bpfdet_(&zrcv, &zdet);
	    ++np;
	    if (np < 40) {	// decimate by 40:  4000Hz ->  100Hz 
		goto L3;
	    }
	    np = 0;
	    noise_(&zdet, &rn, &z);
	    proces_(&x, &rn, &xhat, &px, &elmhat, &ltrhat);

#ifdef DEBUG
//	printf("\nMORSE:n1:%d\tx:%f\tzsig:%f\tzrcv:%f\tzdet:%f\tz:%f\trn:%fxhat:%d\tpx:%f",n1,x,zsig,zrcv,zdet,z,rn,xhat,px);
	printf("\n%d\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t%f",sample,x,zsig,zrcv,zdet,z,rn,xhat,px);
#endif

L3:
	    ;
	}
	n = n1;
	stats_(&x, &z, &zsig, &zdet, s1, s2, s3, s4, &n);
/* L2: */
    }
//	displa_(s1, s2, s3, s4);
    goto L1;
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

/* Main program alias */ int morse_ () { MAIN__ (); return 0; }

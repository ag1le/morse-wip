/* inputl.f -- translated by f2c (version 20100827).
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

/* Common Block Declarations */




/* Initialized data */

struct BLK1 blk1 = { 1.25e-4f };

struct BLK6 blk6 = { 0., 0., 
			{1.f, 3.f, 1.f, 3.f, 7.f, 14.f},
			{ 0.f, 0.f, 0.f, 0.f, 0.f, 0.f}};


/* Subroutine */ int inputl_(void)
{
    /* Format strings */
    static char fmt_100[] = "(1x,\002INPUT KEYING PARMS: RATE,MEAN ELEM DURA"
	    "TIONS\002)";
    static char fmt_150[] = "(1x,\002INPUT ELEM DURATION STD OEVIATIONS\002)";
    static char fmt_300[] = "(1x,\002INPUT SIG PARMS- AVAR,BVAR,FCHIRP,TCHIR"
	    "P,PHIVAR\002)";
    static char fmt_400[] = "(1x,\002INPUT SIG PARMS: GAMMA,FREQ,NOISE\002)";

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    double sqrt(doublereal);

    /* Local variables */
    static real fc, rc, avar, bvar, rate, fchirp, phivar, rnoise;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___2 = { 0, 6, 0, fmt_150, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_300, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_400, 0 };


//    s_wsfe(&io___1);
//    e_wsfe();
/* 	READ 200,RATE,(ESEP(K), K=1,6) */
//    s_wsfe(&io___2);
//    e_wsfe();
/* 	READ 200,(EDEV(K),K=1,6) */
/* L200: */
//    s_wsfe(&io___3);
//    e_wsfe();
/* 	READ 210,AVAR,BVAR,FCHIRP,TCHIRP,PHIVAR */
/* L210: */
//    s_wsfe(&io___4);
//    e_wsfe();
/* 	READ 220, GAMMA,FC,RNOISE */
/* L220: */
/* 	ADDED BY MAURI */
    avar = 1.f;
    bvar = 1.f;
    rate = 20.f;
    fc = 4e3f;
    fchirp = 2.f;
    rnoise = 1.f;
    phivar = 4.f;
    blk2.tchirp = 2.f;
    blk2.gamma = 1.f;
    blk2.asigma = sqrt(avar);
    blk2.bsigma = sqrt(bvar);
    blk2.phisgm = sqrt(phivar);
    blk2.rsigm = sqrt(rnoise);
    blk6.dmean = 1200.f / rate;
    rc = fc * 6.28319f;
    blk2.wchirp = fchirp * 6.2831f;
/* 	IF (ESEP(1).NE.0.) GO TO 500 */
    blk6.esep[0] = 1.f;
    blk6.esep[1] = 3.f;
    blk6.esep[2] = 1.f;
    blk6.esep[3] = 3.f;
    blk6.esep[4] = 7.f;
    blk6.esep[5] = 14.f;
/* L500: */
    return 0;
} /* inputl_ */


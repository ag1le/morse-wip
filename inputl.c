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

#ifdef __cplusplus
extern "C" {
#endif
#include "f2c.h"

/* Common Block Declarations */

struct blk1_1_ {
    real tau;
};

#define blk1_1 (*(struct blk1_1_ *) &blk1_)

struct blk6_1_ {
    real dmean, xdur, esep[6], edev[6];
};

#define blk6_1 (*(struct blk6_1_ *) &blk6_)

struct {
    real wc, wchirp, asigma, bsigma, phisgm, rsigm, tchirp, gamm;
} blk2_;

#define blk2_1 blk2_

/* Initialized data */

struct {
    real e_1;
    } blk1_ = { (float)1.25e-4 };

struct {
    integer fill_1[1];
    real e_2[13];
    } blk6_ = { {0}, (float)0., (float)1., (float)3., (float)1., (float)3., (
	    float)7., (float)14., (float)0., (float)0., (float)0., (float)0., 
	    (float)0., (float)0. };


/* Subroutine */ int inputl_()
{
    /* Format strings */
    static char fmt_100[] = "(1x,\002INPUT KEYING PARMS: RATE,MEAN ELEM DURA\
TIONS\002)";
    static char fmt_150[] = "(1x,\002INPUT ELEM DURATION STD OEVIATIONS\002)";
    static char fmt_300[] = "(1x,\002INPUT SIG PARMS- AVAR,BVAR,FCHIRP,TCHIR\
P,PHIVAR\002)";
    static char fmt_400[] = "(1x,\002INPUT SIG PARMS: GAMMA,FREQ,NOISE\002)";

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe();
    double sqrt(doublereal);

    /* Local variables */
    static real fc, rc, avar, bvar, rate, fchirp, phivar, rnoise;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_100, 0 };
    static cilist io___2 = { 0, 6, 0, fmt_150, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_300, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_400, 0 };


    goto L600;
    s_wsfe(&io___1);
    e_wsfe();
/* 	READ 200,RATE,(ESEP(K), K=1,6) */
    s_wsfe(&io___2);
    e_wsfe();
/* 	READ 200,(EDEV(K),K=1,6) */
/* L200: */
    s_wsfe(&io___3);
    e_wsfe();
/* 	READ 210,AVAR,BVAR,FCHIRP,TCHIRP,PHIVAR */
/* L210: */
    s_wsfe(&io___4);
    e_wsfe();
/* 	READ 220, GAMM,FC,RNOISE */
/* L220: */
L600:
/* 	ADDED BY MAURI */
    avar = (float)4.;
    bvar = (float)4.;
    rate = (float)25.;
    fc = (float)4e3;
    fchirp = (float)20.;
    rnoise = (float)4.;
    phivar = (float)4.;
    blk2_1.tchirp = (float)2.;
    blk2_1.gamm = (float)1.;
    blk2_1.asigma = sqrt(avar);
    blk2_1.bsigma = sqrt(bvar);
    blk2_1.phisgm = sqrt(phivar);
    blk2_1.rsigm = sqrt(rnoise);
    blk6_1.dmean = (float)1200. / rate;
    rc = fc * (float)6.28319;
    blk2_1.wchirp = fchirp * (float)6.2831;
/* 	IF (ESEP(1).NE.0.) GO TO 500 */
    blk6_1.esep[0] = (float)1.;
    blk6_1.esep[1] = (float)3.;
    blk6_1.esep[2] = (float)1.;
    blk6_1.esep[3] = (float)3.;
    blk6_1.esep[4] = (float)7.;
    blk6_1.esep[5] = (float)14.;
/* L500: */
    return 0;
} /* inputl_ */

#ifdef __cplusplus
	}
#endif

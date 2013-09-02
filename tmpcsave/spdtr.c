/* spdtr.f -- translated by f2c (version 20100827).
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


doublereal spdtr_(integer *isrt, integer *ilrt, integer *iselm, integer *ilelm)
{
    /* System generated locals */
    real ret_val;

    /* Local variables */
    static integer ind1, idel, idelsp, israte;


/* 	THIS FUNCTION RETURNS THE DATA RATE (SPEED) TRANSITION */
/* 	PROBABILITY BASED ON THE CURRENT ELEM TYPE. THE ALLOWABLE */
/* 	TRANSITION PROBS ARE STORED IN THE TABLE RTRANS. */

/* 	VARIABLES: */
/* 	ISRT	- DATA RATE IDENTITY FOR STATE TO WHICH PATH IS BEING EXTENDED */
/* 	ILRT	- DATA RATE ON CURRENT PATH */
/* 	ISELM 	- ELEM TYPE FOR NEXT STATE */
/* 	ILELM	- ELEM TYPE ON CURRENT PATH */


/* 	IF SAVED ELEMENT AND NEW ELEMENT ARE THE SAME THEN THERE CAN BE NO SPEED CHANGE: */

    if (*ilelm != *iselm) {
	goto L100;
    }
    ret_val = 1.f;
    if (*isrt != 2) {
	ret_val = 0.f;
    }
    goto L300;

/* 	OTHERWISE, OBTAIN SPEED TRANSITION PROB */

L100:
    idel = blkrat.memdel[*iselm][*ilelm] ;
    ind1 = blkspd.mempr[*iselm][*ilelm];
    if (ind1 != 0) {
		goto L200;
    }
    ret_val = 0.f;
    goto L300;
L200:
    idelsp = (*isrt - 2) * idel;
    ret_val = blkspd.rtrans[ind1-1][*isrt];


    israte = *ilrt + idelsp;
    if (israte > 60) {
		ret_val = 0.f;
    }
    if (israte < 10) {
		ret_val = 0.f;
    }
L300:
#ifdef DEBUG
printf("\nSPDTR: isrt:%d ilrt:%d idel:%d=memdel[%d][%d] ind1:%d idelsp:%d israte:%d retval:%f, rtrans[%d][%d]:%f", *isrt,*ilrt,  idel, *iselm, *ilelm, ind1,idelsp, israte,ret_val,ind1-1,*isrt,blkspd.rtrans[ind1-1][*isrt]);
#endif
    return ret_val;
} /* spdtr_ */


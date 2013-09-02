/* transl.f -- translated by f2c (version 20100827).
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


/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int transl_(integer *ltr)
{
    /* Initialized data */

    static char ispace[1] = " ";
    static integer spflag = 0;
    static integer nchar = 0;

    /* Format strings */
    static char fmt_5000[] = "(1x,i1,s)";
    static char fmt_1500[] = "(2x,a1,/)";
    static char fmt_1000[] = "(1x,a1,s)";
    static char fmt_1100[] = "(1x,a2,$)";
    static char fmt_1200[] = "(2x,a2,2x,$)";
    static char fmt_1300[] = "(2x,a3,2x,$)";
    static char fmt_1400[] = "(/,10x,a2,/,10x)";
    static char fmt_1700[] = "(2x,a3,2x,$)";
    static char fmt_1600[] = "(/,10x)";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__;
    static real o;
    static integer ixl, nblank, elmhat, ltrhat, lstelm, ixlast, elmout;
    static real txlast;
    static integer lstltr, ltrout;

    /* Fortran I/O blocks */
    static cilist io___13 = { 0, 6, 0, fmt_5000, 0 };
    static cilist io___15 = { 0, 6, 0, fmt_1500, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___18 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___19 = { 0, 6, 0, fmt_1100, 0 };
    static cilist io___20 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___21 = { 0, 6, 0, fmt_1200, 0 };
    static cilist io___22 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___23 = { 0, 6, 0, fmt_1300, 0 };
    static cilist io___24 = { 0, 6, 0, fmt_1400, 0 };
    static cilist io___25 = { 0, 6, 0, fmt_1700, 0 };
    static cilist io___26 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___27 = { 0, 6, 0, fmt_1600, 0 };



/*   THIS SUBROUTINE PRODUCES THE OUTPUT TEXT ON A CRT. */
/*    IT USES THE SIMPLE FORMATTING RULES DESCRIBED IN THE */
/*    TEXT. */

/* 	DETERMINE IF A CSP,WSP, OR PAUSE TO MARK TRASITION */
/* 	HAS OCCURED; IF SO LTR IS READY FOR OUTPUT: */
//    elmhat = blklam.ilami[(1600 + (0 + (blklam.ielmst[(0 + (0 + (*ltr - 1<< 2))) / 4] - 1 << 2)) - 1600) / 4];
	elmhat = blklam.ilami[blklam.ielmst[*ltr-1]-1];
    ixl = blklam.ilamx[elmhat - 1];
#ifdef DEBUG
printf("\nTRANSL: elmhat:%d ltr:%d  ixl:%d lstltr:%d", elmhat, *ltr, ixl, lstltr);
#endif
    if (ixl == ixlast) {
	goto L700;
    }
    if (ixl == 1 && lstelm >= 4) {
	goto L10;
    }
    if (ixl == 0 && lstelm <= 2) {
	goto L700;
    }
    goto L700;
L10:
    ltrhat = lstltr;
    ltrout = alpha.ialph[blktrn.ltrmap[ltrhat - 1] - 1];
    nblank = blktrn.iblank[ltrhat - 1];
    elmout = blklam.ilami[blklam.ielmst[ltrhat - 1] - 1];
    goto L40;
    s_wsfe(&io___13);
    do_fio(&c__1, (char *)&elmout, (ftnlen)sizeof(integer));
    e_wsfe();
    ++nchar;
L40:
    if (blktrn.ltrmap[ltrhat - 1] == 43) {
	goto L50;
    }
    if (blktrn.ltrmap[ltrhat - 1] <= 44) {
	goto L100;
    }
    if (blktrn.ltrmap[ltrhat - 1] <= 46) {
	goto L200;
    }
    if (blktrn.ltrmap[ltrhat - 1] <= 60) {
	goto L300;
    }
    if (blktrn.ltrmap[ltrhat - 1] == 61) {
	goto L400;
    }
    if (blktrn.ltrmap[ltrhat - 1] == 66) {
	goto L500;
    }
    goto L550;
L50:
    if ((real) spflag == o) {
	goto L100;
    }
    nchar = 0;
    s_wsfe(&io___15);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 1;
    goto L600;
L100:
#ifdef DEBUG
	printf("\nTRANSL: one char ltrhat:%d ltrmap:%d ltrout:%c", ltrhat, blktrn.ltrmap[ltrhat - 1],alpha.ialph[blktrn.ltrmap[ltrhat - 1] - 1]);
#endif
    ++nchar;
    s_wsfe(&io___16);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L110;
    }
    spflag = 1;
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___18);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
L110:
	;
    }
    goto L600;
L200:
#ifdef DEBUG
	printf("\nTRANSL: 2_ char:");
#endif
    nchar += 2;
    s_wsfe(&io___19);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L210;
    }
    spflag = 1;
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___20);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
L210:
	;
    }
    goto L600;
L300:
#ifdef DEBUG
	printf("\nTRANSL: 4_ char:");
#endif
    nchar += 4;
    s_wsfe(&io___21);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 1;
    if (nblank == 0) {
	goto L310;
    }
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___22);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
L310:
	;
    }
    goto L600;
L400:
#ifdef DEBUG
	printf("\nTRANSL: 5 char:");
#endif
    nchar += 5;
    s_wsfe(&io___23);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 1;
    goto L600;
L500:
    nchar = 0;
    s_wsfe(&io___24);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 1;
    goto L600;
L550:
#ifdef DEBUG
	printf("\nTRANSL: 5_ char:");
#endif
    nchar += 5;
    s_wsfe(&io___25);
    do_fio(&c__1, (char *)&ltrout, (ftnlen)sizeof(integer));
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L560;
    }
    spflag = 1;
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___26);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
L560:
	;
    }
L600:
    if (nchar < 52) {
	goto L700;
    }
    s_wsfe(&io___27);
    e_wsfe();
    nchar = 0;
L700:
    txlast = (real) ixl;
    lstelm = elmhat;
    lstltr = *ltr;
    return 0;
} /* transl_ */


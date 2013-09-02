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

/* Common Block Declarations */

struct {
    integer ltrmap[400], iblank[400];
    char ialph[70];
} blktrn_;

#define blktrn_1 blktrn_

struct {
    integer ielmst[400], ilami[16], ilamx[6];
} blklam_;

#define blklam_1 blklam_

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int transl_(integer *ltr)
{
    /* Initialized data */

    static char ispace[1] = " ";
    static integer spflag = 0;
    static integer nchar = 0;
    static integer lstltr = 5;
    static integer ixlast = 0;
    static integer lstelm = 6;

    /* Format strings */
    static char fmt_5000[] = "(\002ELMHAT, NCHAR, I, LTR, LTRHAT, LTROUT:"
	    "\002,1x,i1,4(1x,i3),\002:\002,a1)";
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
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, ixl, nblank, elmhat, ltrhat;
    static char ltrout[1];

    /* Fortran I/O blocks */
    static cilist io___13 = { 0, 6, 0, fmt_5000, 0 };
    static cilist io___14 = { 0, 6, 0, fmt_1500, 0 };
    static cilist io___15 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___17 = { 0, 6, 0, fmt_1100, 0 };
    static cilist io___18 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___19 = { 0, 6, 0, fmt_1200, 0 };
    static cilist io___20 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___21 = { 0, 6, 0, fmt_1300, 0 };
    static cilist io___22 = { 0, 6, 0, fmt_1400, 0 };
    static cilist io___23 = { 0, 6, 0, fmt_1700, 0 };
    static cilist io___24 = { 0, 6, 0, fmt_1000, 0 };
    static cilist io___25 = { 0, 6, 0, fmt_1600, 0 };



/*   THIS SUBROUTINE PRODUCES THE OUTPUT TEXT ON A CRT. */
/*    IT USES THE SIMPLE FORMATTING RULES DESCRIBED IN THE */
/*    TEXT. */

/* 	DETERMINE IF A CSP,WSP, OR PAUSE TO MARK TRASITION */
/* 	HAS OCCURED; IF SO LTR IS READY FOR OUTPUT: */
    elmhat = blklam_1.ilami[(1600 + (0 + (blklam_1.ielmst[(0 + (0 + (*ltr - 1 
	    << 2))) / 4] - 1 << 2)) - 1600) / 4];
    ixl = blklam_1.ilamx[elmhat - 1];
/* 	PRINT 5, LTR, LSTLTR, IXL */
/* 5	FORMAT('TRANSL LTR, LSTLTR, IXL:', I12, I12, I12) */
/* 	NO CHANGE FROM LAST - CONTINUE */
    if (ixl == ixlast) {
	goto L700;
    }
/* 	KEYSTATE = 1 AND LAST ELEMENT WAS CSP, WSP OR PAUSE => PRINT LETTER */
    if (ixl == 1 && lstelm >= 4) {
	goto L10;
    }
/* 	KEYSTATE = 0  AND LAST ELEMENT WAS DIT OR DAH => SAVE LETTER STATE */
    if (ixl == 0 && lstelm <= 2) {
	goto L700;
    }
    goto L700;
/* 	LETTER OUT WILL BE LAST LETTER SAVED */
L10:
    ltrhat = lstltr;
    i__ = blktrn_1.ltrmap[ltrhat - 1];
    s_copy(ltrout, blktrn_1.ialph + (i__ - 1), (ftnlen)1, (ftnlen)2);
    nblank = blktrn_1.iblank[ltrhat - 1];
    elmhat = blklam_1.ilami[blklam_1.ielmst[ltrhat - 1] - 1];
    goto L40;
    goto L700;
    s_wsfe(&io___13);
    do_fio(&c__1, (char *)&elmhat, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nchar, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*ltr), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&ltrhat, (ftnlen)sizeof(integer));
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    ++nchar;
L40:
    if (blktrn_1.ltrmap[ltrhat - 1] == 43) {
	goto L50;
    }
    if (blktrn_1.ltrmap[ltrhat - 1] <= 44) {
	goto L100;
    }
    if (blktrn_1.ltrmap[ltrhat - 1] <= 46) {
	goto L200;
    }
    if (blktrn_1.ltrmap[ltrhat - 1] <= 60) {
	goto L300;
    }
    if (blktrn_1.ltrmap[ltrhat - 1] == 61) {
	goto L400;
    }
    if (blktrn_1.ltrmap[ltrhat - 1] == 66) {
	goto L500;
    }
    goto L550;
L50:
    if (spflag == 0) {
	goto L100;
    }
/* 	LTRMAP(LTR) = 43 => PRINT "^" AND RESET LINE CHARACTER COUNTER */
    nchar = 0;
    s_wsfe(&io___14);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 1;
    goto L600;
/* 	LTRMAP(LTR) <= 44 => PRINTABLE SINGLE LETTERS & NUMBERS A..Z 0..9 AND ;:,%&^' */
L100:
    ++nchar;
    s_wsfe(&io___15);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L111;
    }
    spflag = 1;
/* 	PRINT ANY SPACES IN IBLANK BUFFER */
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___16);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
/* L110: */
    }
L111:
    goto L600;
/* 	LTRMAP(LTR) <= 44 => PRINT AS or SN */
L200:
    nchar += 2;
    s_wsfe(&io___17);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L211;
    }
    spflag = 1;
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___18);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
/* L210: */
    }
L211:
    goto L600;
/* 	LTRMAP(LTR) <= 60 => PRINT 'NR','NO','GA','OK','AR','SK' PLUS 2 SPC */
L300:
    nchar += 4;
    s_wsfe(&io___19);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 1;
    if (nblank == 0) {
	goto L311;
    }
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___20);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
/* L310: */
    }
L311:
    goto L600;
/* 	LTRMAP(LTR) == 61 => PRINT 'IMI' */
L400:
    nchar += 5;
    s_wsfe(&io___21);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 1;
    goto L600;
/* 	LTRMAP(LTR) == 66 => PRINT 'BT' */
L500:
    nchar = 0;
    s_wsfe(&io___22);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 1;
    goto L600;
/* 	LTRMAP(LTR) == 70 => PRINT 'EEE' */
L550:
    nchar += 5;
    s_wsfe(&io___23);
    do_fio(&c__1, ltrout, (ftnlen)1);
    e_wsfe();
    spflag = 0;
    if (nblank == 0) {
	goto L561;
    }
    spflag = 1;
    i__1 = nblank;
    for (i__ = 1; i__ <= i__1; ++i__) {
	++nchar;
	s_wsfe(&io___24);
	do_fio(&c__1, ispace, (ftnlen)1);
	e_wsfe();
/* L560: */
    }
L561:
/* 	CHECK IF LINE CHARACTER COUNTER < 52 */
L600:
    if (nchar < 52) {
	goto L700;
    }
/* 	PRINT LINE RETURN AND RESET LINE CHARACTER COUNTER */
    s_wsfe(&io___25);
    e_wsfe();
    nchar = 0;
L700:
    ixlast = ixl;
    lstelm = elmhat;
    lstltr = *ltr;
    return 0;
} /* transl_ */


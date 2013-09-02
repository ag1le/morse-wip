

#include "f2c.h"

struct TREE {
 int dit,dah; 
 char chr[5]; 
} tree[] = {
//dit,dah, chr
 {1,2, '*'},	// null state
 {3,4, 'E'}, 	// .
 {5,6, 'T'},	// - 
 {7,8, 'I'},	// ..
 {9,10,'A'},	// .-
 {11,12,'N'},	// -. 
 {13,14,'M'},	// --
 {15,16,'S'},	// ...
 {17,18,'U'},	// ..-
 {19,20,'R'},	// .-.
 {21,22,'W'},	// .--
 {23,24,'D'},	// -..
 {25,26,'K'},	// -.-
 {27,28,'G'},	// --.
 {29,30,'O'},	// ---
 {31,32,'H'},	// ....
 {33,34,'V'},	// ...-
 {35,36,'F'},	// ..-.
 {37,38,'Ü'},	// ..--
 {39,40,'L'},	// .-..
 {41,42,'Ä'},	// .-.-
 {43,44,'P'},	// .--.
 {45,46,'J'},	// .---
 {47,48,'B'},	// -...
 {49,50,'X'},	// -..-
 {51,52,'C'},	// -.-.
 {53,54,'Y'},	// -.--
 {55,00,'Z'},	// --..
 {57,00,'Q'},	// --.-
 {54,00,'Ö'},	// ---.
 {56,57,'Š'},	// ----
 {00,00,'5'},	// .....
 {00,00,'4'},	// ....-
 {00,00,'*'},	// ...-.
 {00,00,'3'},	// ...--
 {00,00,'É'},	// ..-..
 {00,00,'*'},	// ..-.-
 {00,00,'*'}, 	// ..--. D? 
 {00,00,'2'},	// ..---
 {00,00,'*'},	// 
 {00,00,'È'},	// 
 {00,00,'+'},	// 
 {00,00,'*'},	//
 {00,00,'*'},	//
 {00,00,'*'},	// J ? 
 {00,00,'*'},	// .----
 {00,00,'1'},
 {00,00,'6'},
 {00,00,'/'},
 {00,00,'*'},
 {00,00,'Ç'},
 {00,00,'*'},
 {00,00,'Ĥ'},
 {00,00,'Ṅ'},
 {00,00,'8'},
 {00,00,'7'},
 {00,00,'9'},
 {00,00,'0'}
}; 

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
    static integer lstltr = 0;
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
    integer i1;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i, ixl, nblank, elmhat, ltrhat;
    static char ltrout[1];
	static int curstate = 0;
	static int newstate = 0;

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

/* 	 1  2  3  4  5  6  7  8 9 10 11 12 13 14 15 16 */
/* 	.^ .~ .w .p -^ -~ -w -p ^. ^- ~. ~- w. w- p. p- */
/* 	K=1 DIT, K=2 DAH, K=3 E-SPC, K=4 CHR-SPC, K=5 WRD-SPC, K=6 PAUSE */



/*   THIS SUBROUTINE PRODUCES THE OUTPUT TEXT ON A CRT. */
/*    IT USES THE SIMPLE FORMATTING RULES DESCRIBED IN THE */
/*    TEXT. */

/* 	DETERMINE IF A CSP,WSP, OR PAUSE TO MARK TRASITION */
/* 	HAS OCCURED; IF SO LTR IS READY FOR OUTPUT: */
    elmhat = blklam_1.ilami[(1600 + (0 + (blklam_1.ielmst[(0 + (0 + (*ltr - 1 
	    << 2))) / 4] - 1 << 2)) - 1600) / 4];
    ixl = blklam_1.ilamx[elmhat - 1];

/* 	NO CHANGE FROM LAST - CONTINUE */

    if (ixl == ixlast) {
	goto L700;
    }

//	printf("\nltr: %d", *ltr);
	switch (*ltr)
	{
/* 	 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 */
/* 	.^ .~ .w .p -^ -~ -w -p ^. ^- ~. ~- w. w- p. p- */
	case 11:	// ~.
	case 9:  	// ^.
		newstate = tree[curstate].dit;
		break;
	case 12:	// ~- 
	case 10:	// ^-
		newstate = tree[curstate].dah;
		break;
	case 6:
	case 7:
	case 8:
	case 2:
	case 3:
	case 4:
		printf("%s",tree[curstate].chr);
		newstate = 0;
		break;
	default:
	//	ltrhat = 0; 
		break;
	}

	curstate = newstate;

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
    i = blktrn_1.ltrmap[ltrhat - 1];
    s_copy(ltrout, blktrn_1.ialph + (i - 1), (ftnlen)1, (ftnlen)2);
    nblank = blktrn_1.iblank[ltrhat - 1];
    elmhat = blklam_1.ilami[blklam_1.ielmst[ltrhat - 1] - 1];
//    goto L40;
    goto L700;

    s_wsfe(&io___13);
    do_fio(&c__1, (char *)&elmhat, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nchar, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&i, (ftnlen)sizeof(integer));
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
    i1 = nblank;
    for (i = 1; i <= i1; ++i) {
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
    i1 = nblank;
    for (i = 1; i <= i1; ++i) {
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
    i1 = nblank;
    for (i = 1; i <= i1; ++i) {
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
    i1 = nblank;
    for (i = 1; i <= i1; ++i) {
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


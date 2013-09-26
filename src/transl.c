#include "f2c.h"
#include <stdio.h>
#include "morse.h" 
extern char debug; 
struct TREE {
 int dit,dah; 
 char chr[5]; 
} tree[] = {	// check  http://en.wikipedia.org/wiki/Morse_code
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
 {37,38,'..--'},// ..--
 {39,40,'L'},	// .-..
 {41,42,'Ä'},	// .-.-
 {43,44,'P'},	// .--.
 {45,46,'J'},	// .---
 {47,48,'B'},	// -...
 {49,50,'X'},	// -..-
 {51,52,'C'},	// -.-.
 {53,00,'Y'},	// -.--
 {55,00,'Z'},	// --..
 {57,00,'Q'},	// --.-
 {54,00,'Ö'},	// ---.
 {56,57,'Š'},	// ----
 {00,00,'5'},	// .....
 {00,00,'4'},	// ....-
 {00,60,'*'},	// ...-.
 {00,00,'3'},	// ...--
 {00,00,'É'},	// ..-..
 {00,00,'*'},	// ..-.-
 {58,00,'*'}, 	// ..--. D? 
 {00,00,'2'},	// ..---
 {00,00,'*'},	// 
 {00,00,'È'},	// 
 {00,63,'+'},	// .-.-.
 {00,00,'*'},	// .-.--
 {00,00,'*'},	// .--..
 {59,00,'à'},	// .--.-
 {00,00,'*'},	// .----
 {00,00,'1'},	// .---.
 {00,00,'6'},	// -....
 {61,00,'='},	// -...-
 {00,00,'/'},	// -..-.
 {00,00,'*'},	// -..--
 {00,00,'*'},	// -.-..
 {00,00,'Ĥ'},	// -.-.-
 {00,00,'Ṅ'},	// -.--.
 {00,00,'8'},	// ---..
 {00,00,'7'},	// --...
 {00,00,'9'},	// ----.
 {00,00,'0'},	// -----
 {00,00,'?'},	// ..--..
 {00,00,'@'},	// .--.-.
 {00,00,'SK'},	// ...-.-
 {00,62,'*'},	// -...-.
 {00,00,'BK'},	// -...-.-
 {00,00,'.'}	// .-.-.-
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

//***********************************************************************************
// (c) 2013  AG1LE Mauri Niininen
//
//
int transl_(int *ltr)
{
    /* Initialized data */

    static char ispace[1] = " ";
    static integer spflag = 0;
    static integer nchar = 0;
    static integer lstltr = 0;
    static integer ixlast = 0;
    static integer lstelm = 6;


    /* System generated locals */
    integer i1;


    /* Local variables */
    static integer i, ixl, nblank, elmhat;
    static char ltrout[1];
	static int curstate = 0;
	static int newstate = 0;


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

if (debug == 't') { // print received tokens 
	switch (*ltr)
	{
/* 	 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 */
/* 	.^ .~ .w .p -^ -~ -w -p ^. ^- ~. ~- w. w- p. p- */
	case 16:	// p-
		printf("p-");
		newstate = tree[curstate].dah;		
		break;		
	case 15:	// p.
		printf("p.");
		newstate = tree[curstate].dit;		
		break;
	case 14:	// w-	
		printf("w-");
		newstate = tree[curstate].dah;		
		break;
	case 13:	// w.
		printf("w.");
		newstate = tree[curstate].dit;		
		break;
	case 12:	// ~- 
		printf("~-");
		newstate = tree[curstate].dah;		
		break;
	case 11:	// ~.
		printf("~.");
		newstate = tree[curstate].dit;		
		break;
	case 10:	// ^-
		printf("^-");
		newstate = tree[curstate].dah;		
		break;
	case 9:  	// ^.
		printf("^.");
		newstate = tree[curstate].dit;		
		break;
	case 8:
		printf("-p");
		printf("%s ",tree[curstate].chr);
		newstate = 0;		
		break;
	case 7:
		printf("-w");
		printf("%s ",tree[curstate].chr);
		newstate = 0;
		break;
	case 6:
		printf("-~");
		printf("%s",tree[curstate].chr);
		newstate = 0;		
		break;
	case 5:
		printf("-^");
		break;
	case 4:
		printf(".p");
		printf("%s ",tree[curstate].chr);
		newstate = 0;
		break;
	case 3:
		printf(".w");
		printf("%s ",tree[curstate].chr);
		newstate = 0;
		break;
	case 2:
		printf(".~");
		printf("%s",tree[curstate].chr);
		newstate = 0;		
		break;
	case 1:
		printf(".^");
		break;
	default:
		break;

	}

}
else {
//	printf("\nltr: %d %d :", *ltr, elmhat);
	switch (*ltr)
	{
/* 	 1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 */
/* 	.^ .~ .w .p -^ -~ -w -p ^. ^- ~. ~- w. w- p. p- */
	case 15:	// p.
	case 13:	// w.
	case 11:	// ~.
	case 9:  	// ^.
		newstate = tree[curstate].dit;
		break;
	case 16:	// p-
	case 14:	// w-	
	case 12:	// ~- 
	case 10:	// ^-
		newstate = tree[curstate].dah;
		break;
	case 6:
	case 2:
		printf("%s",tree[curstate].chr);
		newstate = 0;
		break;
	case 3:
	case 7:
		printf("%s ",tree[curstate].chr);
		newstate = 0;
		break;
	case 4:
	case 8:
		printf("%s ",tree[curstate].chr);
		newstate = 0;
		break;
	default:
	//	ltrhat = 0; 
		break;
	}
}
L700:
	curstate = newstate;
    ixlast = ixl;
    lstelm = elmhat;
    lstltr = *ltr;
    return newstate;

} /* transl_ */


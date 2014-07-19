// ----------------------------------------------------------------------------
// transl.c --  bayesian morse code decoder 
//
// Copyright (C) 2012-2014
//		     (C) Mauri Niininen, AG1LE
//
// This file is part of Bayesian Morse code decoder   

// bmorse is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// bmorse is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with bmorse.  If not, see <http://www.gnu.org/licenses/>.
// ----------------------------------------------------------------------------

#include <stdio.h>
#include "bmorse.h" 
struct TREE {	// Tree structure to decode dit/dah sequence to corresponding character
 int dit,dah; 	// 
 char chr[12]; 	// max string  11 chars +null for prosigns and error cases 
} tree[] = {	// check  http://en.wikipedia.org/wiki/Morse_code
//dit,dah, chr
 {1,2, "#"},	// null state
 {3,4, "E"}, 	// .
 {5,6, "T"},	// - 
 {7,8, "I"},	// ..
 {9,10,"A"},	// .-
 {11,12,"N"},	// -. 
 {13,14,"M"},	// --
 {15,16,"S"},	// ...
 {17,18,"U"},	// ..-
 {19,20,"R"},	// .-.
 {21,22,"W"},	// .--
 {23,24,"D"},	// -..
 {25,26,"K"},	// -.-
 {27,28,"G"},	// --.
 {29,30,"O"},	// ---
 {31,32,"H"},	// ....
 {33,34,"V"},	// ...-
 {35,36,"F"},	// ..-.
 {37,38,"*..--*"},// ..--
 {39,40,"L"},	// .-..
 {41,42,"Ä"},	// .-.-   Ä
 {43,44,"P"},	// .--.
 {45,46,"J"},	// .---
 {47,48,"B"},	// -...
 {49,50,"X"},	// -..-
 {51,52,"C"},	// -.-.
 {53,00,"Y"},	// -.--
 {55,00,"Z"},	// --..
 {57,00,"Q"},	// --.-
 {54,00,"Ö"},	// ---.	Ö
 {56,57,"*----*"},	// ----	Š
 {00,00,"5"},	// .....
 {00,00,"4"},	// ....-
 {00,60,"*...-.*"},	// ...-.
 {00,00,"3"},	// ...--
 {00,00,"e"},	// ..-..
 {00,00,"*..-.-*"},	// ..-.-
 {58,00,"*..--.*"}, 	// ..--. D? 
 {00,00,"2"},	// ..---
 {00,00,"*.-...*"},	// .-...
 {00,00,"e"},	// .-..-
 {00,63,"<AR>"},	// .-.-.
 {00,00,"*"},	// .-.--
 {00,00,"*.--..*"},	// .--..
 {59,00,"a"},	// .--.-
 {00,00,"*.---.*"},	// .---.
 {66,00,"1"},	// .----
 {00,00,"6"},	// -....
 {61,00,"<BT>"},	// -...-
 {00,00,"/"},	// -..-.
 {00,00,"*-..--*"},	// -..--
 {00,00,"*-.-..*"},	// -.-..
 {00,00,"^H"},	// -.-.-
 {00,00,"<KN>"},	// -.--.
 {00,00,"8"},	// ---..
 {00,00,"7"},	// --...
 {00,00,"9"},	// ----.
 {00,00,"0"},	// -----
 {00,00,"?"},	// ..--..
 {00,00,"@"},	// .--.-.
 {00,00,"<SK>"},	// ...-.-
 {00,62,"*-...-.*"},	// -...-.
 {00,00,"<BK>"},	// -...-.-
 {00,00,"."},	// .-.-.-
 {00,65,"*--..-*"},	// --..-
 {00,00,","},	// --..--
 {00,00,"'"}	// .----.
}; 



//***********************************************************************************
// (c) 2013,2014  AG1LE Mauri Niininen
//
//
int morse::transl_(int ltr, char *buf)
{


    /* Local variables */
    long int ixl, elmhat;
    int n;


/* 	 1  2  3  4  5  6  7  8 9 10 11 12 13 14 15 16 */
/* 	.^ .~ .w .p -^ -~ -w -p ^. ^- ~. ~- w. w- p. p- */
/* 	K=1 DIT, K=2 DAH, K=3 E-SPC, K=4 CHR-SPC, K=5 WRD-SPC, K=6 PAUSE */



/* 	DETERMINE IF A CSP,WSP, OR PAUSE TO MARK TRANSITION */
/* 	HAS OCCURED; IF SO LTR IS READY FOR OUTPUT: */

    
	elmhat = ilami[ltr-1];
    ixl = ilamx[elmhat - 1];
	n=0;
	
/* 	NO CHANGE FROM LAST - CONTINUE */

    if (ixl == ixlast) {
	goto L700;
    }

	if (params.print_symbols) { // print received symbols
		switch (ltr)
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
			newstate = 0;		
			break;
		case 7:
			printf("-w");
			newstate = 0;
			break;
		case 6:
			printf("-~");
			newstate = 0;		
			break;
		case 5:
			printf("-^");
			break;
		case 4:
			printf(".p");
			newstate = 0;
			break;
		case 3:
			printf(".w");
			newstate = 0;
			break;
		case 2:
			printf(".~");
			newstate = 0;		
			break;
		case 1:
			printf(".^");
			break;
		default:
			break;

		}

	}
	if (params.print_text) {
		switch (ltr)
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
		case 6:		// -~
		case 2:		// .~
			n = snprintf(buf,12,"%s",tree[curstate].chr);
			newstate = 0;
			break;
		case 3:		// .w
		case 7:		// -w
			n = snprintf(buf,12,"%s ",tree[curstate].chr);
			newstate = 0;
			break;
		case 4:		// .p
		case 8:		// -p
			n = snprintf(buf,12,"%s ",tree[curstate].chr);
			newstate = 0;
			break;
		case 1:		// .^
		case 5:		// -^
		default:
			break;
		}
	}
//	if (n>0)
//		printf("%s",buf);
L700:

	fflush(stdout);
	curstate = newstate;
    ixlast = ixl;
    return newstate;

}

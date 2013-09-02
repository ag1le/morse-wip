/* displa.f -- translated by f2c (version 20100827).
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
#include "gnuplot_i.h"
#include <stdio.h>


/* Subroutine */ int displa_(real *s1, real *s2, real *s3, real *s4)
{

    /* Local variables */
    static real xm, wait;
	int i; 
	int len = 512; 

	static gnuplot_ctrl *h=0;

	if (h == 0) {
		h = gnuplot_init();
	}
	gnuplot_setstyle(h,"linespoints");
	gnuplot_set_xlabel(h,"time (ms)");

	gnuplot_plot_x(h,(double *)s1,len,"x");
//	gnuplot_plot_x(h,(double *)s2,len,"z");
//	gnuplot_plot_x(h,(double *)s3,len,"zsig");
//	gnuplot_plot_x(h,(double *)s4,len,"zrcv");

printf("\nPress 0 and return"); 
scanf("%d",&i);

    /* Parameter adjustments */
    --s4;
    --s3;
    --s2;
    --s1;

    return 0;
} /* displa_ */


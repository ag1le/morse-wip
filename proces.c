/* proces.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int visarl_(char *nam, real *k, ftnlen nam_len)
{
    /* Format strings */
    static char fmt_10[] = "(a3,25(i6,1x))";
    static char fmt_20[] = "(\002  :\002,25(f6.1,1x))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer j;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, fmt_10, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_20, 0 };


    /* Parameter adjustments */
    --k;

    /* Function Body */
    s_wsfe(&io___1);
    do_fio(&c__1, nam, (ftnlen)3);
    for (j = 1; j <= 25; ++j) {
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
    }
    e_wsfe();
    s_wsfe(&io___3);
    for (j = 1; j <= 25; ++j) {
	do_fio(&c__1, (char *)&k[j], (ftnlen)sizeof(real));
    }
    e_wsfe();
    return 0;
} /* visarl_ */

/* Subroutine */ int visarr_(char *nam, integer *k, real *z__, integer *isave,
	 integer *elmhat, ftnlen nam_len)
{
    /* Format strings */
    static char fmt_20[] = "(f5.1,i3,\002  :\002,25(i6,1x))";

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer j;

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 6, 0, fmt_20, 0 };


/* 	PRINT 10,NAM,(J,J=1,25) */
/* 10	FORMAT(A3,25(I6,1x)) */
    /* Parameter adjustments */
    --k;

    /* Function Body */
    s_wsfe(&io___4);
    do_fio(&c__1, (char *)&(*z__), (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*elmhat), (ftnlen)sizeof(integer));
    i__1 = *isave;
    for (j = 1; j <= i__1; ++j) {
	do_fio(&c__1, (char *)&k[j], (ftnlen)sizeof(integer));
    }
    e_wsfe();
    return 0;
} /* visarr_ */

/* Subroutine */ int vis_(char *nam, real *p, ftnlen nam_len)
{
    /* Format strings */
    static char fmt_10[] = "(a3,30(i7,1x))";
    static char fmt_20[] = "(i2,\002:\002,30(f7.2,1x))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j;

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 6, 0, fmt_10, 0 };
    static cilist io___9 = { 0, 6, 0, fmt_20, 0 };


    /* Parameter adjustments */
    p -= 26;

    /* Function Body */
    s_wsfe(&io___6);
    do_fio(&c__1, nam, (ftnlen)3);
    for (j = 1; j <= 30; ++j) {
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
    }
    e_wsfe();
    for (i__ = 1; i__ <= 25; ++i__) {
	s_wsfe(&io___9);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	for (j = 1; j <= 30; ++j) {
	    do_fio(&c__1, (char *)&p[i__ + j * 25], (ftnlen)sizeof(real));
	}
	e_wsfe();
/* L30: */
    }
    return 0;
} /* vis_ */

/* Subroutine */ int visi_(char *nam, integer *h__, ftnlen nam_len)
{
    /* Format strings */
    static char fmt_10[] = "(a3,30(i3,1x))";
    static char fmt_20[] = "(i2,\002:\002,30(i3,1x))";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__, j;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 6, 0, fmt_10, 0 };
    static cilist io___13 = { 0, 6, 0, fmt_20, 0 };


    /* Parameter adjustments */
    h__ -= 26;

    /* Function Body */
    s_wsfe(&io___10);
    do_fio(&c__1, nam, (ftnlen)3);
    for (j = 1; j <= 30; ++j) {
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
    }
    e_wsfe();
    for (i__ = 1; i__ <= 25; ++i__) {
	s_wsfe(&io___13);
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	for (j = 1; j <= 30; ++j) {
	    do_fio(&c__1, (char *)&h__[i__ + j * 25], (ftnlen)sizeof(integer))
		    ;
	}
	e_wsfe();
/* L30: */
    }
    return 0;
} /* visi_ */

/* Subroutine */ int proces_(real *z__, real *rn, integer *xhat, real *px, 
	integer *elmhat, integer *ltrhat, real *spdhat, integer *imax, real *
	pmax)
{
    /* Initialized data */

    static integer isave = 25;
    static integer lambda[25] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5 };
    static integer ilrate[25] = { 10,10,10,10,10,20,20,20,20,20,30,30,30,30,
	    30,40,40,40,40,40,50,50,50,50,50 };
    static real p[750] = { 1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,1.f,
	    1.f,1.f };
    static integer lamsav[750] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5 };
    static real dur[25] = { 1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,
	    1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,1e3f,
	    1e3f,1e3f };
    static real dursav[750] = { 0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,0.f,
	    0.f,0.f,0.f };
    static integer ilrsav[750] = { 20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	    20,20,20,20,20,20,20,20,20,20 };
    static integer pathsv[25] = { 5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,
	    5,5,5 };

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static real pin[750]	/* was [25][30] */, lkhd[750];
    extern /* Subroutine */ int path_(integer *, integer *, real *, integer *,
	     integer *, real *, integer *);
    static real pelm;
    static integer sort[25];
    extern /* Subroutine */ int likhd_(real *, real *, integer *, integer *, 
	    real *, integer *, real *, real *);
    static integer ipath;
    extern /* Subroutine */ int savep_(real *, integer *, integer *, integer *
	    , integer *, real *, integer *, integer *, real *, integer *, 
	    integer *, real *);
    static integer ipmax;
    extern /* Subroutine */ int probp_(real *, real *, integer *, real *), 
	    sprob_(real *, integer *, integer *, real *, integer *, real *, 
	    real *), trelis_(integer *, integer *, integer *, integer *, 
	    integer *), trprob_(integer *, integer *, real *, integer *, real 
	    *);

/* 	THIS SUBROUTINE IMPLEMENTS THE PROCESSING ALGORITHM */
/* 	FOR JOINT DEMODULATION, DECODING, AND TRANSLATION OF */
/* 	THE RECEIVED MORSE PROCESS. IT TAKES IN A NEW MEASURE- */
/* 	MENT, Z, OF THE DETECTED SIGNAL EVERY 5 MSEC AND PRO- */
/* 	DUCES AN ESTIMATE OF THE CURRENT KEYSTATE, ELEMENT */
/* 	STATE, AND LETTER OF THE RECEIVED SIGNAL. */

/* 	VIS */
/* 	DEFINITIONS OF VARIABLE NAMES: */
/* 	Z- INPUT SAMPLE OF DETECTED SIGNAL */
/* 	RN- INPUT NOISE POWER ESTIMATE */
/* 	XHAT- OUTPUT ESTIMATE OF KEYSTATE */
/* 	ELMHAT- OUTPUT ESTIMATE OF ELEMENT STATE */
/* 	LTRHAT- OUTPUT ESTIMATE OF LETTER STATE */


/* 	ISAVE- NO. OF PREVIOUS PATHS SAVED */
/* 	IPATH- IDENTITY OF SAVED PATH */
/* 	LAMBDA (I) - IDENTITY OF LTR STATE OF SAVED PATH I */
/* 	DUR (I)- DURATION OF ELEMENT ON PATH I */
/* 	ILRATE(I)- IDENTITY OF DATA RATE ON PATH I */
/* 	PIN (I,N)- COMPUTED TRANS PROB FROM PATH I TO STATE N */
/* 	LAMSAV(J)- IDENTITY OF LTR STATE AT NEW NODE J */
/* 	ILRSAV(J)- IDENTITY OF DATA RATE AT NEW NODE J */
/* 	LKHD(J)- LIKELIHOOD VALUE FOR NODE J */
/* 	P(J)- COMPUTED POSTERIOR PROB OF PATH ENDING AT NEW NODE J */
/* 	PSELEM(K)-COMPUTED POSTERIOR PROB OF ELEM K */
/* 	SPDHAT -COND MEAN ESTIMATE OF INSTANT DATA RATE */
/* 	PX- POSTERIOR PROB THAT KEYSTATE EQUALS 1 */

/* 	THE FOLLOWING SUBROUTINES ARE UTILIZED: */
/* 	TRPROB- COMPUTES TRANSITION PROBABILITIES */
/* 	PATH- COMPUTES IDENTITY OF NEW PATHS */
/* 	LIKHD- COMPUTES THE LIKELIHOOD OF EACH PATH EXTENSION */
/* 	PROBP- COMPUTES POSTERIOR PROBS OF EACH NEW PATH */
/* 	SPROB- COMPUTES POSTERIOR PROBS OF EACH STATE */
/* 	SAVE- SAVES THE HIGHEST PROB PATHS */
/* 	TRELIS- FORMS A TRELIS OF SAVED PATHS */
/* 	TRANSL- TRANSLATES THE LETTER ESTIMATE */

/* 	ALL TABLES OF CONSTANTS ARE STORED IN COMMON. */
/* 	FOR EACH SAVED PATH, COMPUTE: */
/* 	TRANSITION PROBABILITY TO NEW STATE (TRPROB); */
/* 	IDENTITY OF EACH NEW PATH EXTENDED (PATH); */
/* 	LIKELIHOOD OF EACH STATE EXTENSION (LIKHD); */
    for (i__ = 1; i__ <= 750; ++i__) {
/* 	P(I) = 1.0 */
/* L110: */
    }
    i__1 = isave;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ipath = i__;
	trprob_(&ipath, &lambda[i__ - 1], &dur[i__ - 1], &ilrate[i__ - 1], 
		pin);
/* 	CALL VISARL('DR1',DUR) */
	path_(&ipath, &lambda[i__ - 1], &dur[i__ - 1], &ilrate[i__ - 1], 
		lamsav, dursav, ilrsav);
/* 	CALL VIS('DRS', DURSAV) */
/* 	CALL VISARR('LBD',LAMBDA) */
/* 	CALL VIS('PIN', PIN) */
	likhd_(z__, rn, &ipath, &lambda[i__ - 1], &dur[i__ - 1], &ilrate[i__ 
		- 1], pin, lkhd);
/* 	CALL VIS('LKH',LKHD) */
/* L100: */
    }
/* 	HAVING OBTAINED ALL NEW PATHS, COMPUTE: */
/* 	POSTERIOR PROBABILITY OF EACH NEW PATH(PROBP); */
/* 	POSTERIOR PROBABILITY OF KEYSTATE, ELEM STATE, */
/* 	CONDITIONAL MEAN ESTIMATE OF SPEED(SPROB); */
    probp_(p, pin, &isave, lkhd);
    sprob_(p, &isave, ilrsav, &pelm, elmhat, spdhat, px);
/* 	CALL VISI('ILR', ILRSAV) */
/* 	CALL VIS('P1:',P) */
/* 	PRINT 111, Z, PX, SPDHAT, ELMHAT */
/* 111	FORMAT('PROCES:',3(3X,F15.9), 3X,I3) */
    *xhat = 0;
    if (*px > .5f) {
	*xhat = 1;
    }
/* 	SAVE THE PATHS WITH HIGHEST PROBABILITY, AND */
/* 	STORE THE VALUES CORRESPONDING TO THESE PATHS: */
/* 	CALL VISI('ILS',ILRSAV) */
    savep_(p, pathsv, &isave, imax, lamsav, dursav, ilrsav, lambda, dur, 
	    ilrate, sort, pmax);
/* 	CALL VISARR('LBD',LAMBDA,Z,ISAVE,ELMHAT) */
/* 	CALL VIS('P2:',P) */
/* 	CALL VISARL('DR2',DUR) */
/* 	CALL VISARR('ILR',ILRATE) */
/* 	GOTO 900 */


/* 	DO 900 INL=1, ISAVE */
/* 	PRINT 112, INL, P(INL), PATHSV(INL), LAMBDA(INL), DUR(INL), */
/*     &ILRATE(INL), LKHD(SORT(INL)) */
/* 112	FORMAT(1X, I3, 2X, F10.7, 2X, I3, 2X, I3, 2X,F6.1, 2X, I3, 2X, */
/*     &F10.5) */
/* 	2 F10.7) */
/* L900: */
/* 	UPDATE TRELLIS WITH NEW SAVED NODES, AND */
/* 	OBTAIN LETTER STATE ESTIMATE: */
    trelis_(&isave, pathsv, lambda, imax, &ipmax);
/* L200: */
    return 0;
} /* proces_ */


#include "f2c.h"
#include "malloc.h"
#include <stdio.h>

#define LEN 	5
static double in[LEN];
static int	empty = 1;
static int	pint = 0;
static double	out;

double Cmovavg(double a)
{


	int i;


	if (empty==1) {
		empty = 0;
		for (i = 0; i < LEN; i++) {
			in[i] = a;
		}
		out = a * (double)LEN;
		pint = 0;
		return a;
	}
	out = out - in[pint] + a;
	in[pint] = a;
	if (++pint >= LEN) pint = 0;
	return out / (double)LEN;
}

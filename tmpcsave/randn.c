#include "f2c.h"
#include <stdio.h>
#include <math.h>

#define	RAND_MAX	2147483647

double randn(real mean, real sigma)
{
    double u = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double v = ((double) rand() / (RAND_MAX)) * 2 - 1;
    double r = u * u + v * v;
    if (r == 0 || r > 1) {
//	printf(".");
	return randn(mean,sigma);
	}
    double c = sqrt(-2 * log(r) / r);
    return (mean + sigma * u * c);
}






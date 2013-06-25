#include "memory.h"
#include <math.h> 
#include <R.h>
#include <Rmath.h>

//#define corrfct  corrfctvalue

#define Integer int
#define Real double

//double corrfctvalue(double d1, double d2, double d3, int i);
Real corrfctvalue(Real phi, Real *kappa, Real h, Integer cornr);
		
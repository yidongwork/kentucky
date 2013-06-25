#include "R.h"

#include "memory.h"
#include <math.h> 
#include <Rmath.h>


#define Real double
#define Integer int

//yy
#define RANDIN  GetRNGstate()
#define RANDOUT PutRNGstate()
#define RUNIF unif_rand()
#define RNORM norm_rand()

#ifndef Salloc
#define Salloc(n,t) (t*)S_alloc(n,sizeof(t))
#endif

Real geoRmatern(Real uphi, Real kappa)
{   
  
  /* 
     WARNING: THIS FUNCTION IS COPIED IN geoRglmm
     NOTIFY OLE ABOUT ANY CHANGE 
  */
  
  Real ans,cte;
  
  if (uphi==0) return 1;
  else{
    if (kappa==0.5) 
      ans = exp(-uphi);
    else {
      cte = R_pow(2, (-(kappa-1)))/gammafn(kappa); 
      ans = cte * R_pow(uphi, kappa) * bessel_k(uphi, kappa, 1); 
    }
  }
  /* Rprintf("   ans=%d ", ans); */
  return ans; 
}

void hello(int* n)
{
	int i;
	for(i=0;i<*n;i++)
		Rprintf("%d times\n",i);

	*n+=1;
}

void trunc_u(Real* mean, Real* H, Real* Result){
  *Result= (*mean>*H) ? *H : *mean;
  *Result=geoRmatern(*mean,*H);
}

//double corrfct(double phi, double kappa, double h , int cornr)
//{
//  
//  /* 
//     WARNING: THIS FUNCTION IS COPIED IN geoRglmm
//     NOTIFY OLE ABOUT ANY CHANGE 
//     
//     Correlation functions implemented and their numbers
//     
//      1: PURE NUGGET
//      2: EXPONENTIAL
//      3: SPHERICAL
//      4: GAUSSIAN
//      5: WAVE (hole effect)
//      6: CUBIC
//      7: POWER
//      8: POWERED EXPONENTIAL
//      9: CAUCHY
//     10: GNEITING
//     11: CIRCULAR
//     12: MATERN
//     13: GNEITING-MATERN (NOT YET IMPLEMENTED)
//     14: CAUCHY (Generalised Cauchy) 
//     
//     WARNING: codes above must be the same as in the geoR/geoS function
//     "cor.number"
//  */
//  
//  Real hphi; 
//  Real hphi2;
//  Real hphi4;
//  Real term1;
//
//  if(h==0) return 1;
//  else{  
//    hphi  = h/phi ;
//    switch(cornr){
//    case 1: /* pure nugget */
//      return 0 ;
//      break;
//    case 2: /* exponential */
//      return exp(-hphi) ;
//      break;
//    case 3: /* spherical */
//      if (h < phi) 
//	return 1 - (1.5 * hphi) + (0.5 * R_pow(hphi,3)) ;
//      else
//	return 0 ;
//      break;
//    case 4: /* Gaussian */
//      return exp(- R_pow(hphi,2)) ;
//      break;
//    case 5: /* wave (hole effect) */
//      return sin(hphi)/hphi ;
//      break;
//    case 6: /* cubic */
//      if (h < phi){
//	hphi2 = hphi * hphi ;
//	hphi4 = hphi2 * hphi2 ;
//	return 1 - ((7 * hphi2) - (8.75 * hphi2 * hphi) + (3.5 * hphi4 * hphi) - (0.75 * hphi4 * hphi2 * hphi)) ;
//      }
//      else
//	return 0 ;
//      break;
//    case 7: /* power: for the power variogram, the correlation function does not exists 
//	     The value returned here corresponds to the variogram */
//      return  R_pow(h, phi) ;
//      break;
//    case 8: /* powered.exponential */
//      return exp(-1 *  R_pow(hphi, kappa))  ;
//      break;
//    case 9:  /* cauchy */
//      return R_pow((1 + R_pow(hphi,2)), -(kappa)) ;
//      break;
//    case 10:  /* gneiting */
//      hphi = 0.301187465825 * hphi ;
//      hphi4 = 1 - hphi ;
//      if (hphi4 > 0) hphi4 = R_pow(hphi4, 8) ;
//      else hphi4 = 0 ;
//      hphi2 = hphi * hphi ;
//      return (1 + 8 * hphi + 25 * hphi2 + 32 * (hphi2 * hphi)) * hphi4 ;
//      break;
//    case 11: /* circular */
//      if(h < phi){
//	return  1 - (M_1_PI * (2 * (hphi * sqrt(1 - hphi * hphi)
//				    + asin(hphi)))) ;
//      }
//      else
//	return 0 ;
//      break;
//    case 12: /* matern */
//      return geoRmatern(hphi, kappa);
//      break;
//    case 13: /* gneiting-matern */
//      term1 = geoRmatern(hphi, kappa);
//      hphi = 0.301187465825 * hphi/kappa ; 
//      hphi4 = 1 - hphi ; 
//      if (hphi4 > 0) hphi4 = R_pow(hphi4, 8) ; 
//      else hphi4 = 0 ; 
//      hphi2 = hphi * hphi ; 
//      return term1 * (1 + 8 * hphi + 25 * hphi2 + 32 * (hphi2 * hphi)) * hphi4 ; 
//      break;
//    case 14:  /* gencauchy */
//      return R_pow((1 + R_pow(hphi, kappa)), -(kappa/kappa));
//      break;
//    default: 
//      return -1;
//      break;
//    }
//  }
//}



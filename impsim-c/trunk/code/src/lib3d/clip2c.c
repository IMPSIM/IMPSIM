/* ------------------------------------------------------------------ */
/* clip2c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Clip a 2D line segment to fit within a viewing pyramid defined
|     by the eye position (possibly at infinity) and the current 2D
|     window.
|
|     Access:
|       iclip = (int) clip2c(real x2s, real y2s, real z2s, real w2s,
|         real x2f, real y2f, real z2f, real w2f, real *x21, real *y21,
|         real *z21, real *x22, real *y22, real *z22);
|     real x2s,i-The 2D x-coordinate of the beginning point of the orig-
|       inal line segment.
|     real y2s,i-The 2D y-coordinate of the beginning point of the orig-
|       inal line segment.
|     real z2s,i-The 2D z-coordinate of the beginning point of the orig-
|       inal line segment.
|     real w2s,i-The 2D homogeneous coordinate of the beginning point of
|       the original line segment.
|     real x2f,i-The 2D x-coordinate of the end point of the original
|       line segment.
|     real y2f,i-The 2D y-coordinate of the end point of the original
|       line segment.
|     real z2f,i-The 2D z-coordiante of the end point of the original
|       line segment.
|     real w2f,i-The 2D homogeneous coordinate of the end point of the
|       original line segment.
|     real *x21,o-The 2D x-coordinate of the beginning point of the
|       clipped line segment.
|     real *y21,o-The 2D y-coordinate of the beginning point of the
|       clipped line segment.
|     real *z21,o-The 2D z-coordinate of the beginning point of the
|       clipped line segment.
|     real *x22,o-The 2D x-coordinate of the end point of the clipped
|       line segment.
|     real *y22,o-The 2D y-coordinate of the end point of the clipped
|       clipped line segment.
|     real *z22,o-The 2D z-coordinate of the end point of the clipped
|       clipped line segment.
|     int iclip,o-A flag indicating the extent of clipping:
|       iclip = 0 indicates no clipping.
|       iclip = 1 indicates clipping of (x2s, y2s, z2s, w2s).
|       iclip = 2 indicates clipping of (x2f, y2f, z2f, w2f).
|       iclip = 3 indicates clipping of both endpoints.
|       iclip = 4 indicates that the entire line segment is outside of
|         the 2D window.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine is not intended for use by the applications prog-
|     rammer; it is a service routine for use within the graphics
|     library.
|       The display device must have been defined by a previous call to
|     devic().
|       The 2D window boundaries may be changed at will by calling
|     fram2c().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int clip2c(real x2s, real y2s, real z2s, real w2s, real x2f, real y2f,
    real z2f, real w2f, real *x21, real *y21, real *z21, real *x22,
    real *y22, real *z22)
#else
  int clip2c(x2s, y2s, z2s, w2s, x2f, y2f, z2f, w2f, x21, y21, z21, x22,
    y22, z22)
  real x2s, y2s, z2s, w2s, x2f, y2f, z2f, w2f, *x21, *y21, *z21, *x22,
    *y22, *z22;
#endif
{
  int  iclip;
  real sigma, tau, w21, w22, zero;
 
/* Initialize variables. */
  zero = min(x2scal, y2scal) * stzero;
  iclip= 0;
  *x21 = x2s;
  *y21 = y2s;
  *z21 = z2s;
   w21 = w2s;
  if (fabs(w21) < zero) w21 = sign(zero, w21);
  *x22 = x2f;
  *y22 = y2f;
  *z22 = z2f;
   w22 = w2f;
  if (fabs(w22) < zero) w22 = sign(zero, w22);
 
/* Clip on w-axis to bound line segment to interior points. */
  if (w21 < zero) {
    if (w22 >= zero) {
      iclip = 1;
      sigma = (zero - w21) / (w22 - w21);
      tau   = 1.0 - sigma;
      *x21  = sigma * (*x22) + tau * (*x21);
      *y21  = sigma * (*y22) + tau * (*y21);
      *z21  = sigma * (*z22) + tau * (*z21);
       w21  = zero;
    } else {
      return(4);
    }
  } else if (w22 < zero) {
    iclip = 2;
    sigma = (w21 - zero) / (w21 - w22);
    tau   = 1.0 - sigma;
    *x22  = sigma * (*x21) + tau * (*x22);
    *y22  = sigma * (*y21) + tau * (*y22);
    *z22  = sigma * (*z21) + tau * (*z22);
     w22  = zero;
  }
 
/* Convert homogeneous point data to 3D. */
  *x21 = *x21 / w21;
  *y21 = *y21 / w21;
  *z21 = *z21 / w21;
  *x22 = *x22 / w22;
  *y22 = *y22 / w22;
  *z22 = *z22 / w22;
 
/* Clip point 1 on x2min and x2max pyramid boundaries. */
  if (*x21 < x2min) {
    if (*x22 > x2min) {
      iclip |= 1;
      sigma = (x2min - *x21) / (*x22 - *x21);
      *x21  = x2min;
      *y21  = sigma * (*y22 - *y21) + *y21;
      *z21  = sigma * (*z22 - *z21) + *z21;
    } else {
      return(4);
    }
  } else if (*x21 > x2max) {
    if (*x22 < x2max) {
      iclip |= 1;
      sigma = (x2max - *x21) / (*x22 - *x21);
      *x21  = x2max;
      *y21  = sigma * (*y22 - *y21) + *y21;
      *z21  = sigma * (*z22 - *z21) + *z21;
    } else {
      return(4);
    }
  }
 
/* Clip point 2 on x2min and x2max pyramid boundaries. */
  if (*x22 < x2min) {
    iclip |= 2;
    sigma = (x2min - *x21) / (*x22 - *x21);
    *x22  = x2min;
    *y22  = sigma * (*y22 - *y21) + *y21;
    *z22  = sigma * (*z22 - *z21) + *z21;
  } else if (*x22 > x2max) {
    iclip |= 2;
    sigma = (x2max - *x21) / (*x22 - *x21);
    *x22  = x2max;
    *y22  = sigma * (*y22 - *y21) + *y21;
    *z22  = sigma * (*z22 - *z21) + *z21;
  }
 
/* Clip point 1 on y2min and y2max pyramid boundaries. */
  if (*y21 < y2min) {
    if (*y22 > y2min) {
      iclip |= 1;
      sigma = (y2min - *y21) / (*y22 - *y21);
      *x21  = sigma * (*x22 - *x21) + *x21;
      *y21  = y2min;
      *z21  = sigma * (*z22 - *z21) + *z21;
    } else {
      return(4);
    }
  } else if (*y21 > y2max) {
    if (*y22 < y2max) {
      iclip |= 1;
      sigma = (y2max - *y21) / (*y22 - *y21);
      *x21  = sigma * (*x22 - *x21) + *x21;
      *y21  = y2max;
      *z21  = sigma * (*z22 - *z21) + *z21;
    } else {
      return(4);
    }
  }
 
/* Clip point 2 on y2min and y2max pyramid boundaries. */
  if (*y22 < y2min) {
    iclip |= 2;
    sigma = (y2min - *y21) / (*y22 - *y21);
    *x22  = sigma * (*x22 - *x21) + *x21;
    *y22  = y2min;
    *z22  = sigma * (*z22 - *z21) + *z21;
  } else if (*y22 > y2max) {
    iclip |= 2;
    sigma = (y2max - *y21) / (*y22 - *y21);
    *x22  = sigma * (*x22 - *x21) + *x21;
    *y22  = y2max;
    *z22  = sigma * (*z22 - *z21) + *z21;
  }
 
/* Clip point 1 on z2min and z2max pyramid boundaries. */
  if (*z21 < z2min) {
    if (*z22 > z2min) {
      iclip |= 1;
      sigma = (z2min - *z21) / (*z22 - *z21);
      *x21  = sigma * (*x22 - *x21) + *x21;
      *y21  = sigma * (*y22 - *y21) + *y21;
      *z21  = z2min;
    } else {
      return(4);
    }
  } else if (*z21 > z2max) {
    if (*z22 < z2max) {
      iclip |= 1;
      sigma = (z2max - *z21) / (*z22 - *z21);
      *x21  = sigma * (*x22 - *x21) + *x21;
      *y21  = sigma * (*y22 - *y21) + *y21;
      *z21  = z2max;
    } else {
      return(4);
    }
  }
 
/* Clip point 2 on z2min and z2max pyramid boundaries. */
  if (*z22 < z2min) {
    iclip |= 2;
    sigma = (z2min - *z21) / (*z22 - *z21);
    *x22  = sigma * (*x22 - *x21) + *x21;
    *y22  = sigma * (*y22 - *y21) + *y21;
    *z22  = z2min;
  } else if (*z22 > z2max) {
    iclip |= 2;
    sigma = (z2max - *z21) / (*z22 - *z21);
    *x22  = sigma * (*x22 - *x21) + *x21;
    *y22  = sigma * (*y22 - *y21) + *y21;
    *z22  = z2max;
  }
  return(iclip);
}

/* ------------------------------------------------------------------ */
/* drwlnc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a line between two points specified in 2D coordinates using
|     the floating horizon algorithm.
|
|     Access:
|       (void) drwlnc(int mxpixl, int khrzon[], int lhrzon[], real x21,
|         real y21, real x22, real y22);
|     int mxpixl,i-Max pixels per 2D window width.
|     int khrzon[mxpixl],i/o-Upper horizon workspace.
|     int lhrzon[mxpixl],i/o-Lower horizon workspace.
|     real x21,  i-Horizontal 2D coordinate of first  line endpoint.
|     real y21,  i-Vertical   2D coordinate of first  line endpoint.
|     real x22,  i-Horizontal 2D coordinate of second line endpoint.
|     real y22,  i-Vertical   2D coordinate of second line endpoint.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This is a service utility routine for the floating horizon
|     algorithm of SFACU().  It should not be called directly by the
|     applications program.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void drwlnc(int mxpixl, int khrzon[], int lhrzon[], real x21,
    real y21, real x22, real y22)
#else
  void drwlnc(mxpixl, khrzon, lhrzon, x21, y21, x22, y22)
  int mxpixl, khrzon[], lhrzon[];
  real x21, y21, x22, y22;
#endif
{
# define YES 1
# define NO -1
  static real x2O = 0.4, y2O = 0.5;
  int  i, i1, i2, inc, j, j1, j2, labove, lbelow;
  real x2, y2, scale, slope, temp;
 
/* If using hidden line removal, increment along the segment pixel */
/*   by pixel and determine if above, below, or on the horizon. */
  scale = (x2max - x2min) / mxpixl;
  i1 = nint((x21 - x2min) / scale);
  j1 = nint((y21 - y2min) / scale);
  i2 = nint((x22 - x2min) / scale);
  j2 = nint((y22 - y2min) / scale);
 
/* If the segment is vertical, draw it. */
  if (i1 == i2) {
    if ((i1 >= 0) && (i1 <= mxpixl)) {
      if (j1 < j2) {
        if (j1 < lhrzon[i1]) {
          mova2c(x21, y21);
          j = min(lhrzon[i1], j2);
          temp = y2min + scale * j;
          drwa2c(x22, temp);
          lhrzon[i1] = j1;
          khrzon[i1] = max(khrzon[i1], j);
        }
        if (j2 > khrzon[i1]) {
          j = min(khrzon[i1], j1);
          temp = y2min + scale * j;
          mova2c(x21, temp);
          drwa2c(x22, y22);
          lhrzon[i1] = min(lhrzon[i1], j);
          khrzon[i1] = j2;
        }
      } else if (j2 < j1) {
        if (j2 < lhrzon[i1]) {
          j = min(j1, lhrzon[i1]);
          temp = y2min + scale * j;
          mova2c(x21, temp);
          drwa2c(x22, y22);
          lhrzon[i1] = j2;
          khrzon[i1] = max(khrzon[i1], j);
        }
        if (j1 > khrzon[i1]) {
          mova2c(x21, y21);
          j = min(khrzon[i1], j2);
          temp = y2min + scale * j;
          drwa2c(x22, temp);
          lhrzon[i1] = min(lhrzon[i1], j);
          khrzon[i1] = j1;
        }
      }
    }
 
/* This is not a vertical segment. */
  } else {
    labove = 0;
    lbelow = 0;
    slope = ((real) (j2 - j1)) / (i2 - i1);
 
/* Increment along the horizontal pixels. */
    inc = 1;
    if (i1 > i2) inc = -1;
    i = i1;
    for (i=i1; ((inc>0) && (i<=i2)) || ((inc<0) && (i>=i2));
      i += inc ) {
      if ((i >= 0) && (i <= mxpixl)) {
        j = nint(j1 + slope * (i-i1));
        x2 = x2min + scale * i;
        y2 = y2min + scale * j;
 
/* If this pixel is below or on the lower horizon, draw it. */
        if (j <= lhrzon[i]) {
          if (lbelow == YES) {
            mova2c(x2O, y2O);
            drwa2c(x2, y2);
            lhrzon[i] = j;
            khrzon[i] = max(khrzon[i], j);
          } else if (lbelow == NO) {
            temp = y2min + scale * lhrzon[i-inc];
            mova2c(x2O, temp);
            drwa2c(x2, y2);
            lhrzon[i] = j;
            khrzon[i] = max(khrzon[i], j);
          }
          lbelow = YES;
 
/* If this pixel is above the lower horizon, then cross it. */
        } else {
          if (lbelow == YES) {
            mova2c(x2O, y2O);
            temp = y2min + scale * lhrzon[i];
            drwa2c(x2, temp);
            lhrzon[i] = min(lhrzon[i], j);
            khrzon[i] = max(khrzon[i], j);
          }
          lbelow = NO;
        }
 
/* If this pixel is above or on the upper horizon, draw it. */
        if (j >= khrzon[i]) {
          if (labove == YES) {
            mova2c(x2O, y2O);
            drwa2c(x2, y2);
            lhrzon[i] = min(lhrzon[i], j);
            khrzon[i] = j;
          } else if (labove == NO){
            temp = y2min + scale * khrzon[i-inc];
            mova2c(x2O, temp);
            drwa2c(x2, y2);
            lhrzon[i] = min(lhrzon[i], j);
            khrzon[i] = j;
          }
          labove = YES;
 
/* If this pixel is below the upper horizon, then cross it. */
        } else {
          if (labove == YES) {
            mova2c(x2O, y2O);
            temp = y2min + scale * khrzon[i];
            drwa2c(x2, temp);
            lhrzon[i] = min(lhrzon[i], j);
            khrzon[i] = max(khrzon[i], j);
          }
          labove = NO;
        }
      }
      x2O = x2;
      y2O = y2;
    }
  }
  return;
# undef YES
# undef NO
}

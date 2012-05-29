/* ------------------------------------------------------------------ */
/* spur2c-01 Jan 00:04 Dec 05
|     (C)Copyright, JJU Research, 2000-2005.
|
|     Description:
|       This is a service routine for cnturc().  It follows a contour of
|     a given height through the grid of z[] values.
|
|     Access:
|       (PFV) spur2c(real x[], real y[], real z[], int ip, int iq,
|         double height, int lopen, int i0, int j0,int iinc0,int jinc0);
|     real   x[],   i-Array of x() values for the grid rows.
|     real   y[],   i-Array of y() values for the grid columns.
|     real   z[],   i-Array z(x,y) of grid values to be contoured.
|     int    ip,    i-Row    dimension of the z(x,y) grid.
|     int    iq,    i-Column dimension of the z(x,y) grid.
|     double height,i-The z value for the desired contour.
|     int    lopen, i-Logical flag telling if an open contour is sought.
|     int    i0,    i-Initial horizontal index of the contour.
|     int    j0,    i-Initial vertical   index of the contour.
|     int    iinc0, i-Initial horizontal increment.
|     int    jinc0, i-Initial vertical   increment.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine is not intended for use by the applications progra-
|     mmer; it is a service routine for use within the graphics library.
|       The z[] array is assumed stored in row-major (C) rather than
|     column-major (Fortran) order.
|       There appears to be a problem in the Watcom C compiler which    WAT
|     prevents height from being of type float; type double is passed   WAT
|     as the sixth argument even when height is declared type float!    WAT
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void spur2c(real x[], real y[], real z[], int ip, int iq,
    double height, int lopen, int i0, int j0, int iinc0, int jinc0)
#else
  void spur2c(x, y, z, ip, iq, height, lopen, i0, j0, iinc0,jinc0)
  real   x[], y[], z[];
  int    ip, iq;
  double height;
  int    lopen, i0, j0, iinc0, jinc0;
#endif
{
  int  i, iinc, j, jinc, junk, lfirst, llast, lright;
  real t, xx, yy, zz, za, zb, zc, zd;
 
/* The procedure begins by initalizing various values. */
  lfirst = TRUE;
  llast  = FALSE;
  i      = i0;
  j      = j0;
  iinc   = iinc0;
  jinc   = jinc0;
  zz     = z[i*iq+j];
  za     = z[(i+iinc)*iq+(j+jinc)];
 
/* Next point. */
_NEXT:
  t = 0.0;
  if (zz != za) t = (zz - height) / (zz - za);
 
/* Position of the point where the contour crosses OA (see Fig. 5) */
/*   is calculated using inverse linear interpolation. */
  xx = x[i] * (1.0 - t) + x[i+iinc] * t;
  yy = y[j] * (1.0 - t) + y[j+jinc] * t;
 
/* Tests are made to see if this is the last point of the contour. */
  if (lopen) {
    if (lfirst) {
      mova2c(xx, yy);
      goto _JUMP;
    } else {
      if (jinc == 0) {
        if ((j == 0) || (j == (iq-1))) llast = TRUE;
      } else {
        if ((i == 0) || (i == (ip-1))) llast = TRUE;
      }
    }
  } else {
    if ((iinc == -1) && !qbitc(LSBREL, (void *) &(z[i*iq+j])))
      llast=TRUE;
    if (lfirst) {
      mova2c(xx, yy);
    } else {
      drwa2c(xx, yy);
    }
  }
  if (llast) goto _RETURN;
  if (iinc == -1) clbitc(LSBREL, (void *) &(z[i*iq+j]));
 
/* New point. */
  drwa2c(xx, yy);
_JUMP:
  if (llast) goto _RETURN;
  lfirst = FALSE;
 
/* The heights of the points B and C (see Fig. 5) are extracted and */
/*   height D is calculated as the average of O, A, B, and C. */
  zb = z[( i      +jinc)*iq+( j      -iinc)];
  zc = z[((i+iinc)+jinc)*iq+((j+jinc)-iinc)];
  zd = 0.25 * (zz + za + zb + zc);
 
/* Test to see which of the lines OD, RO, AD the contour crosses. */
  if (zd >= height) {
 
/* The contour crosses AD and the coordinates of the point where  */
/*   this happens is found using inverse linear interpolation. */
    lright = FALSE;
    t = 0.0;
    if (za != zd) t = 0.5 * (za - height) / (za - zd);
    xx = x[i+iinc] * (1.0 - t) + x[i+jinc] * t;
    yy = y[j+jinc] * (1.0 - t) + y[j-iinc] * t;
    drwa2c(xx, yy);
 
/* Test to see if the contour crosses AC as in case (i) of Fig. 6. */
    if (zc < height) goto _LEFT;

/* The contour exits from the basic rectangle by crossing AC.  Values */
/*   of zz,i,j,iinc, and jinc are updated before finding a new point. */
/*   Turn left. */
    zz   = zc;
    i   += (iinc+jinc);
    j   += (jinc-iinc);
    junk =  jinc;
    jinc =  iinc;
    iinc = -junk;
    goto _NEXT;
  }

/* The contour crosses OD; the coordinates of the point where this  */
/*   happens are found using inverse linear interpolation. */
  lright = TRUE;
  t = 0.0;
  if (zz != zd) t = 0.5 * (zz - height) / (zz - zd);
  xx = x[i] * (1.0 - t) + x[i+iinc+jinc] * t;
  yy = y[j] * (1.0 - t) + y[j+jinc-iinc] * t;
  drwa2c(xx, yy);
 
/* Test to see whether contour crosses OB as in case (ii) of Fig. 6. */
  if (zb < height) {
 
/* The contour exits from the basic rectangle by crossing OB.  Values */
/*   of za, iinc, and jinc are updated before finding a new point. */
/* Turn right. */
    za   = zb;
    junk = iinc;
    iinc = jinc;
    jinc =-junk;
    goto _NEXT;
  }
 
/* Top right. */
_RIGHT:
  t = 0.0;
  if (zb != zd) t = 0.5 * (zb - height) / (zb - zd);
 
/* The contour crosses BD and the coordintes of the point where  */
/*   this happens are found using inverse linear interpolation. */
  xx = x[i+jinc] * (1.0 - t) + x[i+iinc] * t;
  yy = y[j-iinc] * (1.0 - t) + y[j+jinc] * t;
  drwa2c(xx, yy);
 
/* Test to see if the situation is as in case (v) of Fig 6. */
  if ( ! lright) {
 
/* The contour exits from the basic rectangle by crossing OB.  Values */
/*   of za, iinc, and jinc are updated before finding a new point. */
/* Turn right.  */
    za   = zb;
    junk = iinc;
    iinc = jinc;
    jinc =-junk;
    goto _NEXT;
  }
 
/* Test to see if the contour crosses BC as in case (iv) of Fig. 6. */
  if (zc < height) {
 
/* The contour exits from the basic rectangle by crossing BC.  Values */
/*   of zz, za, i, and j are updated before finding a new point. */
/* Go straight. */
    zz = zb;
    za = zc;
    i += jinc;
    j -= iinc;
    goto _NEXT;
  }
 
/* Top left. */
_LEFT:
  t = 0.0;
 
/* The contour crosses CD and coordinates of the point where this */
/*   happens are found using inverse interpolation. */
  if (zd != zc) t = (zd - height) / (zd - zc);
  xx = 0.5 * (x[i] * (1.0 - t) + x[(i+jinc)+iinc] * (1.0 + t));
  yy = 0.5 * (y[j] * (1.0 - t) + y[(j-iinc)+jinc] * (1.0 + t));
  drwa2c(xx, yy);
 
/* Test to see whether the situation is as in case (vi) of Fig. 6. */
  if (lright) {
 
/* The contour exits from the basic rectangle by crossing AC.  Values */
/*   of zz, i, j, iinc and jinc are updated before finding new point. */
/* Turn left. */
    zz   = zc;
    i   += (iinc+jinc);
    j   += (jinc-iinc);
    junk = jinc;
    jinc = iinc;
    iinc =-junk;
    goto _NEXT;
  }
 
/* Test to see if the contour crroses BC as in case (iii) of Fig. 6. */
  if (zb < height) goto _RIGHT;
 
/* The contour exits from the basic rectangle by crossing BC.  Values */
/*   of z, za, i, and j are updated before finding a new point. */
/* Go straight. */
  zz = zb;
  za = zc;
  i += jinc;
  j -= iinc;
  goto _NEXT;
_RETURN:
  return;
}

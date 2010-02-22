/* ------------------------------------------------------------------ */
/* cnturc-01 Jan 00:08 May 05
|     (C)Copyright, JJU Research, 2000-2005.
|
|     Description:
|       Draw a contour map over a rectangular grid of precomputed values
|     of the function z(x,y).
|
|     Access:
|       (void) cnturc(real x[], real y[], real z[], int ip, int iq,
|         real hgts[], int ir, PFV spurc)
|     real x[],   i-Array of x values defining the grid.
|     real y[],   i-Array of y values defining the grid.
|     real z[], i/o-Array of precomputed values of z(x,y).
|     int  ip,    i-Row    dimension of the z[] grid and x[] array.
|     int  iq,    i-Column dimension of the z[] grid and y[] array.
|     real hgts[],i-Array of z[] values of the desired contours.
|     int  ir,    i-Number of desired contours and hgts[] values.
|     PFV  spurc, i-Name of external routine spur2c or spur3c.
|
|     Error Conditions:
|       Early exit from this routine is made if the keyboard interrupt
|     flag is detected, (cf. qkbic).
|
|     Comments:
|       The basic reference for this algorithm is:
|     B.R.Heap,et.al., Three Contouring Routines, NPL-DNAM-81, National
|     Physical Lab, Teddington, England, 1969.
|       It is also given in:
|     J.S.Petty,et.al., Contouring and Hidden-Line Algorithms for Vector
|     Graphic Displays, AFAPL-TR-77-3, (AD-A040530), Wright-Patterson
|     AFB, 1977.
|       The graphic display device must have been defined by a previous
|     call to devic().
|       Note that matrix z[] is assumed stored in row-major (C) rather
|     than column-major (Fortran) order.
|       The final argument, spurc, may be entered as either spur2c or
|     spur3c in the calling routine.  If spur2c is used it implies that
|     x[] and y[] are given in the user's 2D coordinate system and units
|     and that drawing will be done by the libcad mova2c() and drwa2c()
|     functions.  If spur3c is used, it implies that x[] and y[] are
|     given in the user's 3D coordinate system and units and that the
|     libcad mova3c() and drwa3c() functions will be used for drawing;
|     the z(x,y) value for each contour taken is from the hgts[] array.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void cnturc(real x[], real y[], real z[], int ip, int iq, real hgts[],
    int ir, PFV spurc)
#else
  void cnturc(x, y, z, ip, iq, hgts, ir, spurc)
  real x[], y[], z[];
  int  ip, iq;
  real hgts[];
  int  ir;
  PFV  spurc;
#endif
{
  int  i, j, k;
  real height;
 
/* Each contour height is dealt with in turn. */
  for (k=0; k<ir; k++) {
    if (qkbic()) goto _RETURN;
    height = hgts[k];
 
/* Bit LSBREL in z[] is used to show if that value is on the contour. */
    for (i=1; i<ip; i++) {
      for (j=1; j<iq; j++) {
        if ((z[(i-1)*iq+j] < height) && (z[i*iq+j] >= height)) {
          ldbitc(LSBREL, (void *) &(z[i*iq+j]));
        } else {
          clbitc(LSBREL, (void *) &(z[i*iq+j]));
        }
      }
    }

/* Scan the boundary of the z[] array for the beginning of any open */
/*   contour of the current height. */
/* First, scan the j=0 edge. */
    for (i=1; i<ip; i++) {
      if ((z[(i-1)*iq] < height) && (z[i*iq] >= height)) {
        (spurc) (x, y, z, ip, iq, height, TRUE, i, 0, -1, 0);
      }
    }
/* Next, scan the i=ip-1 edge. */
    i = ip - 1;
    for (j=1; j<iq; j++) {
      if ((z[i*iq+j-1] < height) && (z[i*iq+j] >= height)) {
        (spurc) (x, y, z, ip, iq, height, TRUE, i, j, 0, -1);
      }
    }
/* Next, scan the j=iq-1 edge. */
    j = iq - 1;
    for (i=ip-1; i>0; i--) {
      if ((z[i*iq+j] < height) && (z[(i-1)*iq+j] >= height)) {
        (spurc) (x, y, z, ip, iq, height, TRUE, i-1, j, 1, 0);
      }
    }
/* Next, scan the i=0 edge. */
    for (j=iq-1; j>0; j--) {
      if ((z[j] < height) && (z[j-1] >= height)) {
        (spurc) (x, y, z, ip, iq, height, TRUE, 0, j-1, 0, 1);
      }
    }
 
/* Check for the beginning of any closed contour of proper height. */
    for (j=iq-2; j>0; j--) {
      for (i=ip-2; i>0; i--) {
        if (qbitc(LSBREL, (void *) &(z[i*iq+j]))) {
          (spurc) (x, y, z, ip, iq, height, FALSE, i, j, -1, 0);
        }
      }
    }
    bflshc();
  }
_RETURN:
  return;
}

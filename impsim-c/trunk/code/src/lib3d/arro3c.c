/* ------------------------------------------------------------------ */
/* arro3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw an arrow with a pyramidal arrowhead from one 3D point to
|     another.
|
|     Access:
|       (void) arro3c(real size, real pt1[3], real pt2[3], int iopt);
|     real size,  i-Screen units for length of arrowhead desired.
|     real pt1[3],i-3D coordinates of beginning point of arrow.
|     real pt2[3],i-3D coordinates of final (head) point of arrow.
|     int  iopt,  i-Integer option flag specifying type of arrowhead:
|          iopt = 1 for a solid arrow through the arrowhead;
|               = 2 for arrow visible only to the base of the arrowhead;
|               = 3 for no visible shaft for the arrow.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void arro3c(real size, real pt1[3], real pt2[3], int iopt)
#else
  void arro3c(size, pt1, pt2, iopt)
  real size;
  real pt1[3];
  real pt2[3];
  int  iopt;
#endif
{
  int  i;
  real arrwl, bn[3], p1[3], p2[3], p3[3], p4[3], scale, sizeb, sizet,
    tn[3], val, xn[3];
 
  scale = qscl3c() * min(x2scal, y2scal);
  for (i=0; i<3; i++) {
    xn[i] = pt2[i] - pt1[i];
  }
  val = vabsc(3, xn);
  if (val * scale < stzero) return;
  for (i=0; i<3; i++) {
    p1[i] = 0.0;
    xn[i] /= val;
  }
  if ((fabs(xn[1]) * scale < stzero) &&
      (fabs(xn[2]) * scale < stzero)) {
    bn[0] =  xn[2];
    bn[1] =  0.0;
    bn[2] = -xn[0];
    p1[1] =  1.0;
  } else {
    bn[0] =  0.0;
    bn[1] = -xn[2];
    bn[2] =  xn[1];
    p1[0] =  1.0;
  }
  vcrosc(xn, bn, tn);
  arrwl = size / scale;
  sizeb = 0.15 * arrwl / vabsc(3, bn);
  sizet = 0.15 * arrwl / vabsc(3, tn);
  for (i=0; i<3; i++) {
    bn[i] *= sizeb;
    tn[i] *= sizet;
    xn[i] = (val - arrwl) * xn[i] + pt1[i];
    p1[i] = xn[i] + bn[i];
    p2[i] = xn[i] + tn[i];
    p3[i] = xn[i] - bn[i];
    p4[i] = xn[i] - tn[i];
  }
  if (iopt >= 3) {
    mova3c(pt1[0],pt1[1],pt1[2], 1.0);
    drwa3c(pt2[0],pt2[1],pt2[2], 1.0);
  } else if (iopt == 2) {
    mova3c(pt1[0],pt1[1],pt1[2], 1.0);
    drwa3c( xn[0], xn[1], xn[2], 1.0);
  }
  mova3c( p1[0], p1[1], p1[2], 1.0);
  drwa3c( p4[0], p4[1], p4[2], 1.0);
  drwa3c(pt2[0],pt2[1],pt2[2], 1.0);
  drwa3c( p1[0], p1[1], p1[2], 1.0);
  drwa3c( p2[0], p2[1], p2[2], 1.0);
  drwa3c(pt2[0],pt2[1],pt2[2], 1.0);
  drwa3c( p3[0], p3[1], p3[2], 1.0);
  drwa3c( p2[0], p2[1], p2[2], 1.0);
  mova3c( p3[0], p3[1], p3[2], 1.0);
  drwa3c( p4[0], p4[1], p4[2], 1.0);
  return;
}

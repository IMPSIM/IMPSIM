/* ------------------------------------------------------------------ */
/* vreadc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Recall a previously stored view.
|
|     Access:
|       (void) vreadc(int nview);
|     int nview,i-View number (-7 <= nview <= 16).
|       nview = -1 indicates a  front        (X,Y) view orientation.
|       nview = -2 indicates a  back        (-X,Y) view orientation.
|       nview = -3 indicates a  left side    (Z,Y) view orientation.
|       nview = -4 indicates a  right side  (-Z,Y) view orientation.
|       nview = -5 indicates a  top         (X,-Z) view orientation.
|       nview = -6 indicates a  bottom       (X,Z) view orientation.
|       nview = -7 indicates an isometric (-Z+X,Y) view orientation.
|       nview >= 0 indicates a  stored (by vstorc) view orientation.
|
|     Error Conditions:
|       If view (nview) is not stored, the current view parameters are
|     not changed.  No message is printed.
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
  void vreadc(int nview)
#else
  void vreadc(nview)
  int nview;
#endif
{
  int  i, j, n;
  real x32[3][3];
 
/* Test for a standard view. */
  n = nview;
  if ((n <= -1) && (n >= -7)) {
 
/* Set the identity transformation. */
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++) {
        x32[i][j] = 0.0;
      }
      x32[i][i] = 1.0;
    }
 
/* Treat a front (x,y) view. */
    if (n == -1) {
 
/* Treat a back (-x,y) view. */
    } else if (n == -2) {
      x32[0][0] =-1.0;
      x32[2][2] =-1.0;
 
/* Treat a left side (z,y) view. */
    } else if (n == -3) {
      x32[0][0] = 0.0;
      x32[0][2] = 1.0;
      x32[2][0] =-1.0;
      x32[2][2] = 0.0;
 
/* Treat a right side (-z,y) view. */
    } else if (n == -4) {
      x32[0][0] = 0.0;
      x32[0][2] =-1.0;
      x32[2][0] = 1.0;
      x32[2][2] = 0.0;
 
/* Treat a top (x,-z) view. */
    } else if (n == -5) {
      x32[1][1] = 0.0;
      x32[1][2] =-1.0;
      x32[2][1] = 1.0;
      x32[2][2] = 0.0;
 
/* Treat a bottom (x,z) view. */
    } else if (n == -6) {
      x32[1][1] = 0.0;
      x32[1][2] = 1.0;
      x32[2][1] =-1.0;
      x32[2][2] = 0.0;
 
/* Treat an isometric (-z+x,y) view. */
    } else if (n == -7) {
      x32[0][0] = 0.70711;
      x32[0][2] =-0.70711;
      x32[1][0] =-0.40825;
      x32[1][1] = 0.81650;
      x32[1][2] =-0.40825;
      x32[2][0] = 0.57735;
      x32[2][1] = 0.57735;
      x32[2][2] = 0.57735;
    }
 
/* Recall the view transformation. */
  } else {
    if ((n < 0) || (n > MXVIEW)) return;
    if ((n > 0) && ( ! lvue[n])) return;
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++) {
        x32[i][j] = x32vue[n][i][j];
      }
    }
  }
 
/* Form the direct and inverse rotation transformations. */
  for (i=0; i<3; i++){
    for (j=0; j<3; j++){
      x3to2[i][j] = x32[i][j];
      x2to3[i][j] = x32[j][i];
    }
  }
 
/* Reform the inverse transformation translation terms. */
  for (i=0; i<3; i++){
    x2to3[i][3] = 0.0;
    for (j=0; j<3; j++){
      x2to3[i][3] -= x2to3[i][j] * x3to2[j][3] * x2to3[3][3];
    }
  }
  lspen = FALSE;
  l3pen = FALSE;
  return;
}

/* ------------------------------------------------------------------ */
/* fram3c-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set an appropriate 3D to 2D scale factor and translations to
|     properly display the 3D shape (defined by its 3D bounding box) on
|     the current graphic display device.
|
|     Access:
|       (void) fram3c(real xmin, real ymin, real zmin, real xmax,
|         real ymax, real zmax);
|     real xmin,i-Minimum 3D x-coordinate value of the shape.
|     real ymin,i-Minimum 3D y-coordinate value of the shape.
|     real zmin,i-Minimum 3D z-coordinate value of the shape.
|     real xmax,i-Maximum 3D x-coordinate value of the shape.
|     real ymax,i-Maximum 3D y-coordinate value of the shape.
|     real zmax,i-Maximum 3D z-coordinate value of the shape.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       This routine assumes that when the right of the screen is used
|     for libcad-drawn menus, then the shape should be centered in the
|     remaining portion of the screen.
|       Approximately 20% of the longest dimension is reserved for a
|     blank border when determining the proper scale factor.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fram3c(real xmin, real ymin, real zmin, real xmax, real ymax,
    real zmax)
#else
  void fram3c(xmin, ymin, zmin, xmax, ymax, zmax)
  real xmin, ymin, zmin, xmax, ymax, zmax;
#endif
{
# define ZRO 0.0001
  int i;
  real dx2ctr, dy2ctr, dz2ctr, scale, swide, x2far, y2far, x2org, y2org,
    x2wide, y2high, x2mx, x2mn, y2mx, y2mn, z2mx, z2mn, x20, y20, z20,
    w20, x21, y21, z21, w21, x22, y22, z22, w22, x23, y23, z23, w23,
    x24, y24, z24, w24, x25, y25, z25, w25, x26, y26, z26, w26, x27,
    y27, z27, w27;
 
/* Find the screen size limits in 2D coordinates. */
  xsto2c(0.0, 0.0, &x2org, &y2org);
  if (menumx > 0) {
    swide = 1.0 - 10.0 * ssymbl;
  } else {
    swide = 1.0;
  }
  xsto2c(swide, 1.0, &x2far, &y2far);
  x2wide = x2far - x2org;
  y2high = y2far - y2org;
 
/* Transform the 3D bounding box to 2D coordinates. */
  x3to2c(xmin, ymin, zmin, 1.0, &x20, &y20, &z20, &w20);
  x20 /= w20;
  y20 /= w20;
  z20 /= w20;
  x3to2c(xmax, ymin, zmin, 1.0, &x21, &y21, &z21, &w21);
  x21 /= w21;
  y21 /= w21;
  z21 /= w21;
  x3to2c(xmin, ymax, zmin, 1.0, &x22, &y22, &z22, &w22);
  x22 /= w22;
  y22 /= w22;
  z22 /= w22;
  x3to2c(xmax, ymax, zmin, 1.0, &x23, &y23, &z23, &w23);
  x23 /= w23;
  y23 /= w23;
  z23 /= w23;
  x3to2c(xmin, ymin, zmax, 1.0, &x24, &y24, &z24, &w24);
  x24 /= w24;
  y24 /= w24;
  z24 /= w24;
  x3to2c(xmax, ymin, zmax, 1.0, &x25, &y25, &z25, &w25);
  x25 /= w25;
  y25 /= w25;
  z25 /= w25;
  x3to2c(xmin, ymax, zmax, 1.0, &x26, &y26, &z26, &w26);
  x26 /= w26;
  y26 /= w26;
  z26 /= w26;
  x3to2c(xmax, ymax, zmax, 1.0, &x27, &y27, &z27, &w27);
  x27 /= w27;
  y27 /= w27;
  z27 /= w27;
 
/* Find the 2D coordinate bounds of the figure. */
  x2mx = max8(x20, x21, x22, x23, x24, x25, x26, x27);
  x2mn = min8(x20, x21, x22, x23, x24, x25, x26, x27);
  y2mx = max8(y20, y21, y22, y23, y24, y25, y26, y27);
  y2mn = min8(y20, y21, y22, y23, y24, y25, y26, y27);
  z2mx = max8(z20, z21, z22, z23, z24, z25, z26, z27);
  z2mn = min8(z20, z21, z22, z23, z24, z25, z26, z27);
 
/* Slide the figure center to screen center and scale to proper size. */
  scale = fabs(min (x2wide / max(x2mx - x2mn, ZRO),
    y2high / max(y2mx - y2mn, ZRO))) / 1.40;
  if (scale < ZRO) scale = 1.0;
  dx2ctr = 0.5 * ((x2org + x2far) / scale - (x2mx + x2mn));
  dy2ctr = 0.5 * ((y2org + y2far) / scale - (y2mx + y2mn));
  dz2ctr =-0.5 * (z2mx + z2mn);
  x3to2[0][3] += dx2ctr * x3to2[3][3];
  x3to2[1][3] += dy2ctr * x3to2[3][3];
  x3to2[2][3] += dy2ctr * x3to2[3][3];
  x3to2[3][3] /= scale;
  for (i=0; i<3; i++) {
    x2to3[i][3] = (-x2to3[i][0] * dx2ctr - x2to3[i][1]  * dy2ctr
                   -x2to3[i][2] * dz2ctr + x2to3[i][3]) * scale;
  }
  x2to3[3][3] *= scale;
  lspen = FALSE;
  l3pen = FALSE;
  return;
# undef ZRO
}

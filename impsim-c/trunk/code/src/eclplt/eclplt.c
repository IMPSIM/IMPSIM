/* eclplt-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Recreational test program that uses the graphics of libcad.
|
|     Access:
|       eclplt
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This program shows the fly-through of a diamond shaped solid.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void crate();
void prongs();
void rings();
void triang();
void sfill();
#ifdef ANSI
  void drawsc(int n, real x[], real y[]);
  void ellips(real xc, real yc, real a, real b, real phi, int npts, 
    int lflag, real x[], real y[]);
  void nextsc(int n, real u[], real v[], real x[], real y[]);
#else
  void drawsc();
  void ellips();
  void nextsc();
#endif

int main()
{
  char dsplay[8];
  int n;

  devic("alpha");
  do{
    textc("Enter display type: > ", TRUE);
    n = bfinc("?");
    if (n == 2) goto _DONE;
  } while(n != 0);
  bfgetc(dsplay);
  devic(dsplay);
  crate();
  waitc();
  prongs();
  waitc();
  rings();
  waitc();
  triang();
  waitc();
  sfill();
  waitc();
_DONE:
  finplc();
  return(EXIT_SUCCESS);
}
/* crate-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw a picture of an impossible crate.
|
|     Access:
|       (void) crate();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
void crate()
{
  real a, u, v, x1, x2, x3, x7, x8, x10, x11, x12, x13, x14, x15, x16, 
    x17, x18, x19, x20, x21, x22, x23, x24, x25, y1, y2, y3, y4, y5, y6, 
    y7, y8, y9, y10, y11, y12, y14, y18, y20, y22, y23, y25;

  newpgc();
  framsc( 0.0, 0.0, 1.0, 1.0);
  fram2c(-1.0, 9.0,24.0, 9.0);
  a = atan(1.0);
  x1 = 10.0 * cos(a);
  y1 = 10.0 * sin(a);
  mova2c(0.0, y1);
  y2 = y1 + 1.0;
  drwa2c( 0.0,  y2);
  drwa2c(  x1, 1.0);
  drwa2c(  x1, 0.0);
  drwa2c( 0.0,  y1);
  mova2c( 0.0,  y2);
  drwa2c(0.25,  y2);
  x2 = x1 + 0.25;
  drwa2c(  x2, 1.0);
  drwa2c(  x1, 1.0);
  mova2c(  x1, 0.0);
  drwa2c(  x2, 0.0);
  y3 = y2 - 0.25 * sin(a);
  y4 = y3 - 0.25 * sin(a);
  y5 = y4 - 1.0;
  drwa2c(  x2,  y5);
  x3 = x2 + 1.0;
  mova2c(  x3,  y5);
  drwa2c(  x3, 0.0);
  drwa2c(  x2, 0.0);
  mova2c(  x2,  y3);
  drwa2c(  x2,10.0);
  drwa2c(  x3,10.0);
  drwa2c(  x3,  y3);
  mova2c(  x3,10.0);
  u  =   x3 - 0.25 * cos(a);
  y6 = 10.0 + 0.25 * sin(a);
  drwa2c(  u,  y6);
  x7 =  x2 - 0.25 * cos(a);
  y7 = 1.0 + 0.25 * sin(a);
  mova2c(  x7,  y7);
  drwa2c(  x7,  y5);
  mova2c(  x7,  y3);
  y8 = 10.0 - 1.0;
  drwa2c(  x7,  y8);
  mova2c(  x1,  y8);
  y9 = y1 + 10.0;
  v  = y9 -  1.0;
  drwa2c( 0.0,   v);
  drwa2c( 0.0,  y9);
  drwa2c(  x1,10.0);
  drwa2c(  x1,  y8);
  drwa2c(  x2,  y8);
  mova2c(  x1,10.0);
  drwa2c(  x2,10.0);
  drwa2c(0.25,    y9);
  drwa2c( 0.0,  y9);
  v = y9 - 1.0 - 0.25 * tan(a);
  mova2c(0.25,   v);
  drwa2c(0.25,  y2);
  x8 = 0.25 + 0.25 * cos(a); 
  mova2c(  x8,  y3);
  y10 =  y9       - 0.25 * sin(a);
  y11 = y10 - 1.0 - 0.25 * tan(a);
  drwa2c(  x8, y11);
  mova2c(0.25,  y9);
  u = 0.25 + 1.0;
  drwa2c(   u,  y9);
  x10 = x8 + 1.0;
  drwa2c( x10, y10);
  v = y11 - 1.0 * tan(a);
  mova2c( x10,   v);
  drwa2c( x10,  y3);
  mova2c(  x8, y10);
  x11 = x8 + 10.0;
  drwa2c( x11, y10);
  x12 = x11 + 0.25 * cos(a);
  y12 = y10 - 0.25 * sin(a);
  mova2c( x12, y12);
  x13 = x8 + 0.25 * cos(a);
  drwa2c( x13, y12);
  x14 = x13 + 1.0 / tan(a);
  y14 = y12 - 1.0;
  mova2c( x14, y14);
  drwa2c( x12, y14);
  drwa2c( x12, y12);
  x15 = x11 - 1.0;
  mova2c( x15, y10);
  x16 = x15 - 0.25 * cos(a);
  drwa2c( x16,  y9);
  x17 = x16 + 1.0;
  drwa2c( x17,  y9);
  mova2c( x16,  y9);
  drwa2c( x16, y10);
  mova2c( x16, y14);
  drwa2c( x16,  y3);
  mova2c( x15,  y3);
  drwa2c( x15, y14);
  mova2c( x11, y14);
  drwa2c( x11,  y3);
  drwa2c(  x8,  y3);
  mova2c( x13,  y4);
  drwa2c( x12,  y4);
  drwa2c( x12,  y5);
  drwa2c( x14,  y5);
  x18 = x7 - 0.25 * cos(a);
  y18 = y7 + 0.25 * sin(a);
  mova2c( x18, y18);
  drwa2c(  x7, y18);
  mova2c(  x3, y18);
  x19 =  x7 + 10.0;
  x20 = x19 -  1.0;
  drwa2c( x20, y18);
  mova2c( x20,  y7);
  drwa2c(  x3,  y7);
  y20 = 0.25 * sin(a);
  mova2c(  x3, y20);
  drwa2c( x20, y20);
  drwa2c( x20,  y6);
  x21 = x2  + 10.0;
  x22 = x21 -  1.0;
  drwa2c( x22,10.0);
  drwa2c( x22, 0.0);
  drwa2c( x20, y20);
  mova2c( x22, 0.0);
  drwa2c( x21, 0.0);
  drwa2c( x21,10.0);
  drwa2c( x22,10.0);
  mova2c( x20,  y8);
  drwa2c( x11,  y8);
  mova2c( x11,  y6);
  drwa2c( x20,  y6);
  mova2c( x16,  y8);
  drwa2c(  x3,  y8);
  mova2c(  x7,  y6);
  drwa2c( x16,  y6);
  y22 = y6 + 0.25 * sin(a);
  mova2c( x16, y22);
  drwa2c( x18, y22);
  mova2c( x11, y22);
  u = x18 + 10.0;
  drwa2c(   u, y22);
  mova2c( x19,  y6);
  drwa2c( x20,  y6);
  mova2c( x21,10.0);
  drwa2c( x17,  y9);
  u = 0.25 + 10.0 + 0.25;
  drwa2c(   u,  y9);
  x23 = x21 + 0.25;
  drwa2c( x23,10.0);
  drwa2c( x21,10.0);
  mova2c( x23,10.0);
  drwa2c( x23,  y8);
  drwa2c( x21,  y8);
  x24 = x21 - y18 * tan(a);
  mova2c( x24, y22);
  drwa2c( x12, y14);
  mova2c( x21, 0.0);
  drwa2c( x23, 0.0);
  drwa2c( x23, 1.0);
  drwa2c( x21, 1.0);
  mova2c( x12,  y5);
  drwa2c( x24, y18);
  mova2c( x11,  y3);
  y23 = 1.0 + (x21 - x20) * tan(a);
  drwa2c( x20, y23);
  mova2c( x23, 1.0);
  v = 1.0 + 0.25 * tan(a);
  drwa2c( x21,   v);
  v = y23 + 0.25 * tan(a);
  mova2c( x20,   v);
  x25 = max(x11, x23 - 10.0 * cos(a));
  y25 = min(y2,  1.0 + 10.0 * sin(a));
  drwa2c( x25, y25);
  if (x25 != x11)drwa2c( x11,  y2);
  clrplc();
  return;
}
/* prongs-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw a picture of an impossible set of prongs.
|
|     Access:
|       (void) prongs();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
void prongs()
{
  real x[30], y[30];

  newpgc();
  framsc( 0.0, 0.0, 1.0, 1.0);
  fram2c( 0.0, 1.5,12.0, 1.5);
  mova2c( 1.0, 3.0);
  drwa2c( 9.0, 3.0);
  drwa2c(10.0, 1.0);
  drwa2c(10.0, 0.5);
  drwa2c( 2.0, 0.5);
  mova2c( 2.0, 1.0);
  drwa2c(10.0, 1.0);
  mova2c( 8.75,1.5);
  drwa2c( 1.5, 1.5);
  mova2c( 1.5, 2.0);
  drwa2c( 8.25,2.0);
  drwa2c( 8.5, 1.5);
  mova2c( 8.75,1.5);
  drwa2c( 8.25,2.5);
  drwa2c( 8.25,2.0);
  mova2c( 8.25,2.5);
  drwa2c( 1.0, 2.5);
  ellips(1.0, 2.75, 0.25, 0.125, 1.5708, 30, TRUE, x, y);
  ellips(1.5, 1.75, 0.25, 0.125, 1.5708, 30, TRUE, x, y);
  ellips(2.0, 0.75, 0.25, 0.125, 1.5708, 30, TRUE, x, y);
  clrplc();
  return;
}
/* ellips-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw a picture of an ellipse in 2-D coordinates.
|
|     Access:
|       (void) ellips(real xc, real yc, real a, real b, real phi,
|         int npts, int lflag, real x[], real y[])
|     real xc,i-X2 coordinate of the center of the ellipse.
|     real yc,i-Y2 coordinate of the center of the ellipse.
|     real a,i-Length of the semi-major axis.
|     real b,i-Length of the semi-minor axis.
|     real phi,i-Inclination angle of the major axis in radians.
|     int npts,i-Number of points on the ellipse.
|     int lflag,i-Flag set TRUE  to plot and store the coordinates, or
|                          FALSE to only store the coordinates.
|     real x[npts],o-the x2-coordinates of the points on the ellipse.
|     real y[npts],o-the y2-coordinates of the points on the ellipse.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifdef ANSI
  void ellips(real xc, real yc, real a, real b, real phi, int npts, 
    int lflag, real x[], real y[])
#else
  void ellips(xc, yc, a, b, phi, npts, lflag, x, y)
  real xc, yc, a, b, phi;
  int npts, lflag;
  real x[], y[];
#endif
{
  real angle, cosphi, cosang, cossum, sinphi, sinang, sinsum, temp,
    xrad, yrad;
  int i;

  cosphi = cos(phi);
  sinphi = sin(phi);
  angle  = 2.0 * PI / (npts - 1);
  cosang = cos(angle);
  sinang = sin(angle);
  cossum = 1.0;
  sinsum = 0.0;
  for (i=0; i<npts; i++){
    xrad = a * cossum;
    yrad = b * sinsum;
    x[i] = xc + xrad * cosphi - yrad * sinphi;
    y[i] = yc + xrad * sinphi + yrad * cosphi;
    temp = cossum * cosang - sinsum * sinang;
    sinsum = sinsum * cosang + cossum * sinang;
    cossum = temp;
  }
  if (lflag){
    mova2c(x[0], y[0]);
    for (i=1; i<npts; i++){
      drwa2c(x[i], y[i]);
    }
    drwa2c(x[0], y[0]);
  }
  return;
}
/* rings-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw a picture of impossible rings.
|
|     Access:
|       (void) rings();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
void rings()
{
  real a, alpha, b, beta, c, calpha, cbeta, d, e, f, g, r1, r2, r3,
    salpha, sbeta, x[16], y[29], xc, yc;
  int i, j, k, l;
  static int is[29] = {  5, 15, 15, 14, 11, 11,  6,  4,  4,  6,  7, 13,
    12, 13, 12,  7,  1, 11, 10,  0,  0,  9,  9,  8,  8,  3,  2,  2,  3};
  static int js[29] = {  0,  9, 14, 15, 28, 21,  8,  6,  1,  2,  3, 10,
    11, 13, 12,  7,  4, 26, 27, 20,  5, 22, 25, 24, 23, 17, 16, 19, 18};
  static int ks[42] =    {   0,  1,  2,  7,  8,  0,  8, 11, 13, 15, 10,
    15,  6,  9, 12, 11, 12, 14,  2,  3,  4,  5, 17, 18, 19, 20,  7, 16,
    20, 21, 22, 28, 27, 26, 24, 21, 24, 23, 17, 27, 28, 25};
  static int ipen[42] =  {   3,  2,  2,  2,  2,  3,  2,  2,  2,  2,  3,
     2,  2,  2,  2,  3,  2,  2,  3,  2,  2,  3,  2,  2,  2,  2,  3,  2,
     2,  2,  2,  2,  2,  2,  2,  3,  2,  2,  3,  2,  3,  2};

/* Define constant parameters. */
  alpha  = PI / 6.0;
  calpha = cos(alpha);
  salpha = sin(alpha);
  beta   = PI / 6.0;
  cbeta  = cos(beta);
  sbeta  = sin(beta);
  a  = 0.75;
  b  = 9.00;
  c  = 0.75;
  d  = 2.00;
  e  = 0.75;
  f  = 0.75;
  g  = 3.50;
  r1 = e * sin(alpha + beta) / sin(PI / 2.0 - beta);
  r2 = f * calpha * tan(beta);
  r3 = a * calpha / cbeta;
  xc = 0.25;
  yc = 0.25;

/* Define the figure coordinates. */
  x[ 0] = xc;
  y[ 0] = yc;
  x[ 1] = x[ 0] + a * calpha;
  y[ 1] = y[ 0] + a * salpha;
  x[ 2] = x[ 0] + c * cbeta;
  y[ 2] = y[ 1] + c * sbeta + r1;
  x[ 3] = x[ 2] + f * calpha;
  y[ 3] = y[ 2]             + r2;
  y[ 6] = y[ 1] + g         - r1;
  x[ 4] =         d         + xc;
  y[ 4] = y[ 6] + (a * calpha - d) * tan(beta);
  x[ 5] = x[ 4] + a * calpha;
  y[ 5] = y[ 4] + a * salpha;
  x[ 6] = x[ 4] + c * cbeta;
  x[ 7] = x[ 6] + f * calpha;
  y[ 8] = y[ 2] + g - 2.0 * r1;
  y[ 7] = y[ 8] - f * salpha;
  x[11] = x[ 1] + b * cbeta;
  x[10] = x[11] - e * calpha;
  x[ 9] = x[11] - c * cbeta;
  x[ 8] = x[ 9] - e * calpha;
  y[ 9] = y[ 0] + b * sbeta;
  y[10] = y[ 1] + (b + r3 - c) * sbeta;
  y[11] = y[10] + e * salpha;
  x[15] = x[ 5] + b * cbeta;
  x[13] = x[15] - c * cbeta;
  x[12] = x[13] - e * calpha;
  y[12] = y[11] + (y[ 7] - y[ 3]);
  y[13] = y[10] + (y[ 8] - y[ 2]);
  x[14] = x[15] - e * calpha;
  y[14] = y[ 9] + g;
  y[15] = y[14] + e * salpha;
  y[16] = y[ 5] + (y[ 2] - y[ 1]);
  y[17] = y[16] + (y[ 3] - y[ 2]);
  y[18] = y[17] + (y[ 7] - y[ 3]);
  y[19] = y[18] + (y[ 8] - y[ 7]);
  y[20] = y[ 5] + g;
  y[21] = y[ 4] + b * sbeta;
  y[22] = y[21] + (y[10] - y[ 9]);
  y[23] = y[22] + (y[11] - y[10]);
  y[24] = y[23] + (y[12] - y[11]);
  y[25] = y[24] + (y[13] - y[12]);
  y[26] = y[21] + g;
  y[27] = y[26] + e * salpha;
  y[28] = y[15] - (y[6] - y[4]);

/* Draw the figure. */
  newpgc();
  framsc( 0.0, 0.0, 1.0, 1.0);
  fram2c(-1.0,-1.0,16.0,12.0);
  for (l=0; l<42; l++){
    k = ks[l];
    i = is[k];
    j = js[k];
    if (ipen[l] == 2){
      drwa2c(x[i], y[j]);
    } else {
      mova2c(x[i], y[j]);
    }
  }
  clrplc();
  return;
}
/* triang-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw a picture of an impossible solid triangle.
|
|     Access:
|       (void) triang();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
void triang()
{
  newpgc();
  framsc( 0.0, 0.0, 1.0, 1.0);
  fram2c(-2.0,10.0,30.0,10.0);
  mova2c( 2.0, 0.0);
  drwa2c( 1.0, 1.73205);
  drwa2c(10.0,17.3205);
  drwa2c(12.0,17.3205);
  drwa2c(21.0, 1.73205);
  drwa2c(20.0, 0.0);
  drwa2c( 2.0, 0.0);
  drwa2c(10.0,13.85641);
  drwa2c(11.0,12.12436);
  mova2c(10.0,17.3205);
  drwa2c(18.0, 3.23205);
  drwa2c(16.0, 3.23205);
  mova2c(21.0, 1.73205);
  drwa2c( 5.0, 1.73205);
  drwa2c(11.0,12.12436);
  drwa2c(16.0, 3.23205);
  drwa2c( 6.0, 3.23205);
  clrplc();
  return;
}
/* sfill-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw five levels of Sierpinski's square filling curves.
|
|     Access:
|       (void) sfill();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
void sfill()
{
  static real x1[16], y1[16], x2[64], y2[64], x3[256], y3[256],
    x4[1024], y4[1024], x5[4096], y5[4096];

/* Initialize. */
  newpgc();
  framsc( 0.0, 0.0, 1.0, 1.0);
  fram2c(-8.0, 0.0, 8.0, 0.0);

/* Generate the first order curve and draw it. */
  x1[ 0] =  2.50;
  y1[ 0] =  1.25;
  x1[ 1] =  3.75;
  y1[ 1] =  2.50;
  x1[ 2] =  2.50;
  y1[ 2] =  3.75;
  x1[ 3] =  1.25;
  y1[ 3] =  2.50;
  x1[ 4] = -1.25;
  y1[ 4] =  2.50;
  x1[ 5] = -2.50;
  y1[ 5] =  3.75;
  x1[ 6] = -3.75;
  y1[ 6] =  2.50;
  x1[ 7] = -2.50;
  y1[ 7] =  1.25;
  x1[ 8] = -2.50;
  y1[ 8] = -1.25;
  x1[ 9] = -3.75;
  y1[ 9] = -2.50;
  x1[10] = -2.50;
  y1[10] = -3.75;
  x1[11] = -1.25;
  y1[11] = -2.50;
  x1[12] =  1.25;
  y1[12] = -2.50;
  x1[13] =  2.50;
  y1[13] = -3.75;
  x1[14] =  3.75;
  y1[14] = -2.50;
  x1[15] =  2.50;
  y1[15] = -1.25;
  drawsc(  16, x1, y1);

/* Generate the second order curve and draw it. */
  nextsc(  16, x1, y1, x2, y2);
  drawsc(  64, x2, y2);

/* Generate the third order curve and draw it. */
  nextsc(  64, x2, y2, x3, y3);
  drawsc( 256, x3, y3);

/* Generate the fourth order curve and draw it. */
  nextsc( 256, x3, y3, x4, y4);
  drawsc(1024, x4, y4);

/* Generate the fifth order curve and draw it. */
  nextsc(1024, x4, y4, x5, y5);
  drawsc(4096, x5, y5);
  clrplc();
  return;
}
/* nextsc-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Generate the n+1st order of Sierpinski square filling curves
|     from his nth order curve.
|
|     Access:
|       (void) nextsc(int n, real u[], real v[], real x[], real y[]);
|     int n,i-the order of the nth order curve.
|     real u[n],i-the u-coordinates of the nth order curve.
|     real v[n],i-the v-coordinates of the nth order curve.
|     real x[4*n],o-the x2-coordinates of the n+1st order curve.
|     real y[4*n],o-the y2-coordinates of the n+1st order curve.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#ifdef ANSI
  void nextsc(int n, real u[], real v[], real x[], real y[])
#else
  void nextsc(n, u, v, x, y)
  int n;
  real u[], v[], x[], y[];
#endif
{
  real d, d1, d2, x1, y1, x2, y2;
  int m, nn;

  nn = -4;
  for (m=0; m<n; m++){
    nn = nn + 4;
    x1 = u[m];
    y1 = v[m];
    if ((m + 1) == n){
      x2 = u[0];
      y2 = v[0];
    } else{
      x2 = u[m+1];
      y2 = v[m+1];
    }

/* Case where x1 < x2 and y1 < y2. */
    if (x1 < x2){
      if (y1 < y2){
        d = 0.5 * (x2 - x1);
        x[nn  ] = x1 + d;
        y[nn  ] = y1;
        x[nn+1] = x2;
        y[nn+1] = y1 - d;
        x[nn+2] = x2 + d;
        y[nn+2] = y1;
        x[nn+3] = x2;
        y[nn+3] = y1 + d;

/* Case where x1 < x2 and y1 == y2. */
      } else {
        if (y1 == y2){
          d  = x2 - x1;
          d1 = 0.25 * d;
          d2 = 0.50 * d;
          x[nn  ] = x1;
          y[nn  ] = y1 + d1;
          x[nn+1] = x1 + d1;
          y[nn+1] = y1 + d2;
          x[nn+2] = x2 - d1;
          y[nn+2] = y1 + d2;
          x[nn+3] = x2;
          y[nn+3] = y1 + d1;

/* Case where x1 < x2 and y1 > y2. */
        } else {
          d = 0.5 * (x2 - x1);
          x[nn  ] = x1;
          y[nn  ] = y1 - d;
          x[nn+1] = x1 - d;
          y[nn+1] = y2;
          x[nn+2] = x1;
          y[nn+2] = y2 - d;
          x[nn+3] = x1 + d;
          y[nn+3] = y2;
        }
      }

/* Case where x1 == x2 and y1 < y2. */
    } else {
      if (x1 == x2){
        if (y1 < y2){
          d  = y2 - y1;
          d1 = 0.25 * d;
          d2 = 0.50 * d;
          x[nn  ] = x1 - d1;
          y[nn  ] = y1;
          x[nn+1] = x1 - d2;
          y[nn+1] = y1 + d1;
          x[nn+2] = x1 - d2;
          y[nn+2] = y2 - d1;
          x[nn+3] = x1 - d1;
          y[nn+3] = y2;

/* Case where x1 == x2 and y1 == y2. */
        } else {
          if (y1 == y2){
            textc("*** Error: x1 = x2 and y1 = y2. ***", TRUE);

/* Case where x1 == x2 and y1 > y2. */
          } else {
            d  = y1 - y2;
            d1 = 0.25 * d;
            d2 = 0.50 * d;
            x[nn  ] = x1 + d1;
            y[nn  ] = y1;
            x[nn+1] = x1 + d2;
            y[nn+1] = y1 - d1;
            x[nn+2] = x1 + d2;
            y[nn+2] = y2 + d1;
            x[nn+3] = x1 + d1;
            y[nn+3] = y2;
          }
        }

/* Case where x1 > x2 and y1 < y2. */
      } else {
        if (y1 < y2){
          d = 0.5 * (x1 - x2);
          x[nn  ] = x1;
          y[nn  ] = y1 + d;
          x[nn+1] = x1 + d;
          y[nn+1] = y2;
          x[nn+2] = x1;
          y[nn+2] = y2 + d;
          x[nn+3] = x1 - d;
          y[nn+3] = y2;

/* Case where x1 > x2 and y1 == y2. */
        } else {
          if (y1 == y2){
            d  = x1 - x2;
            d1 = 0.25 * d;
            d2 = 0.50 * d;
            x[nn  ] = x1;
            y[nn  ] = y1 - d1;
            x[nn+1] = x1 - d1;
            y[nn+1] = y1 - d2;
            x[nn+2] = x2 + d1;
            y[nn+2] = y1 - d2;
            x[nn+3] = x2;
            y[nn+3] = y1 - d1;

/* Case where x1 > x2 and y1 > y2. */
          } else {
            d = 0.5 * (x1 - x2);
            x[nn  ] = x1 - d;
            y[nn  ] = y1;
            x[nn+1] = x2;
            y[nn+1] = y1 + d;
            x[nn+2] = x2 - d;
            y[nn+2] = y1;
            x[nn+3] = x2;
            y[nn+3] = y2 + d;
          }
        }
      }
    }
  }
  return;
}
/* drawsc-01 Jan 00
|     (C)Copyright, JJU Research, Inc., 2000.
|
|     Description:
|       Draw the n point Sierpinski square filling curve.
|
|     Access:
|       (void) drawsc(int n, real x[], real y[]);
|     int n,i-the number of points on the curve.
|     real x[n],i-the x2-coordinates of the curve.
|     real y[n],i-the y2-coordinates of the curve.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#ifdef ANSI
  void drawsc(int n, real x[], real y[])
#else
  void drawsc(n, x, y)
  int n;
  real x[], y[];
#endif
{
  int i;

  mova2c(x[0], y[0]);
  for (i=0; i<n; i++){
    drwa2c(x[i], y[i]);
  }
  drwa2c(x[0], y[0]);
  clrplc();
  return;
}

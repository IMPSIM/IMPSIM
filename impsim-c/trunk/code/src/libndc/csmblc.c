/* ------------------------------------------------------------------ */
/* csmblc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a stroke generated centered symbol corresponding to the
|     specified number at the current graphic pen location.
|
|     Access:
|       (void) csmblc(int number, real width)
|     int  number,i-The number of the symbol to be generated.
|     real width, i-The width of the centered symbol in screen units.
|
|     Error Conditions:
|       If number is negative, its absolute value is used.
|       If number is not in the range 1-16, it is treated modulo 16.
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
  void csmblc(int number, real width)
#else
  void csmblc(number, width)
  int  number;
  real width;
#endif
{
  int  i, j, k, n;
  real delta, pixels, s, t, s0, t0;
  static int mesh[MXSMBL][2][16] = {
    {{2,2,4,4,0,0,2,9,0,0,0,0,0,0,0,0}, /* Symbol  1:         square. */
     {2,4,4,0,0,4,4,9,0,0,0,0,0,0,0,0}},
    {{2,2,3,4,4,3,1,0,0,1,2,9,0,0,0,0}, /* Symbol  2:        octagon. */
     {2,4,4,3,1,0,0,1,3,4,4,9,0,0,0,0}},
    {{2,2,4,0,2,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol  3:       triangle. */
     {2,4,1,1,4,9,0,0,0,0,0,0,0,0,0,0}},
    {{2,2,9,0,4,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol  4:      plus sign. */
     {0,4,8,2,2,9,0,0,0,0,0,0,0,0,0,0}},
    {{0,4,9,0,4,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol  5:          cross. */
     {0,4,8,4,0,9,0,0,0,0,0,0,0,0,0,0}},
    {{2,2,4,2,0,2,9,0,0,0,0,0,0,0,0,0}, /* Symbol  6:        diamond. */
     {2,4,2,0,2,4,9,0,0,0,0,0,0,0,0,0}},
    {{2,2,0,4,2,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol  7:       up-arrow. */
     {0,4,2,2,4,9,0,0,0,0,0,0,0,0,0,0}},
    {{0,4,0,4,9,0,0,0,0,0,0,0,0,0,0,0}, /* Symbol  8:  bridged-cross. */
     {0,4,4,0,9,0,0,0,0,0,0,0,0,0,0,0}},
    {{4,0,9,0,4,0,4,9,0,0,0,0,0,0,0,0}, /* Symbol  9:    crossed-zee. */
     {2,2,8,4,4,0,0,9,0,0,0,0,0,0,0,0}},
    {{2,2,0,2,4,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol 10:       y-symbol. */
     {0,2,4,2,4,9,0,0,0,0,0,0,0,0,0,0}},
    {{2,2,3,4,3,3,4,3,1,0,1,1,0,1,2,9}, /* Symbol 11:  spoked square. */
     {2,3,3,4,3,1,0,1,1,0,1,3,4,3,3,9}},
    {{0,4,9,2,2,9,4,0,9,0,4,9,0,0,0,0}, /* Symbol 12:       asterisk. */
     {0,4,8,4,0,8,0,4,8,2,2,9,0,0,0,0}},
    {{0,4,0,4,0,9,0,0,0,0,0,0,0,0,0,0}, /* Symbol 13:     hour glass. */
     {0,4,4,0,0,9,0,0,0,0,0,0,0,0,0,0}},
    {{2,2,9,0,0,0,0,0,0,0,0,0,0,0,0,0}, /* Symbol 14:   vertical-bar. */
     {0,4,9,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {{2,2,4,0,2,9,4,2,0,4,9,0,0,0,0,0}, /* Symbol 15:  star of david. */
     {2,4,1,1,4,8,3,0,3,3,9,0,0,0,0,0}},
    {{0,4,9,0,0,0,0,0,0,0,0,0,0,0,0,0}, /* Symbol 16: horizontal bar. */
     {2,2,9,0,0,0,0,0,0,0,0,0,0,0,0,0}}
  };
 
/* Set a local origin such that the pen is at (2,2). */
  if ((spen < smin) || (spen > smax) || (tpen < tmin) || (tpen > tmax))
    return;
  pixels = 0.25 * width;
  s0 = spen - 2.0 * pixels;
  t0 = tpen - 2.0 * pixels;
 
/* Get the coded symbol strokes from the mesh array. */
  n = (abs(number) - 1) % MXSMBL;
 
/* Loop through the specified strokes. */
  lspen = FALSE;
  for (k=0; k<MXSMBL; k++) {
    i = mesh[n][0][k];
    j = mesh[n][1][k];
 
/* Treat (9,9) as a stop code. */
    if (i == 9) {
      delta = 10.0 * pixels;
      if (j == 9) {
        break;
 
/* Treat (9,8) as a pen up code. */
      } else if (j == 8) {
        lspen = FALSE;
 
/* Treat (9,7) as a pen down code. */
      } else if (j == 7) {
        wrpenc(spen, tpen);
 
/* Treat (9,1-4) as origin shift codes. */
      } else if (j == 1) {
        t0 += delta;
      } else if (j == 2) {
        t0 -= delta;
      } else if (j == 3) {
        s0 += delta;
      } else if (j == 4) {
        s0 -= delta;
      }
 
/* Make the next stroke. */
    } else {
      s = s0 + i * pixels;
      t = t0 + j * pixels;
      wrpenc(s, t);
    }
  }
 
/* Shift the origin for the next character. */
  s = s0 + 2.0 * pixels;
  t = t0 + 2.0 * pixels;
  movasc(s, t);
  lspen = FALSE;
  return;
}

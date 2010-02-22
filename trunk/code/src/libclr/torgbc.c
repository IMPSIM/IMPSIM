/* ------------------------------------------------------------------ */
/* torgbc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Change input HLS color parameters into equivalent RGB color
|     parameters.
|
|     Access:
|       (void) torgbc(int ihue, int ilite, int isat, int *ired,
|         int *igreen, int *iblue);
|     int  ihue,  i-Hue value, 0<=ihue<360, red=120, green=240, blue=0.
|     int  ilite, i-Percent lightness value,  0 <= ilite <= 100.
|     int  isat,  i-Percent saturation value, 0 <= isat  <= 100.
|     int *ired,  o-Red value,   0 <= ired   < 256.
|     int *igreen,o-Green value, 0 <= igreen < 256.
|     int *iblue, o-Blue value,  0 <= iblue  < 256.
|
|     Error Conditions:
|       If the ihue value is outside of its specified range, it is
|     treated modulo 360.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void torgbc(int ihue, int ilite, int isat, int *ired, int *igreen,
    int *iblue)
#else
  void torgbc(ihue, ilite, isat, ired, igreen, iblue)
  int ihue, ilite, isat, *ired, *igreen, *iblue;
#endif
{
  real vr, vg, vb, x1, x2, xhue, xlite, xsat;
 
  xhue = (real) ((ihue) % 360);
  xlite = 0.01 * (ilite);
  xsat  = 0.01 * (isat);
  if (xlite <= 0.5) {
    x2 = xlite * (1.0 + xsat);
  } else {
    x2 = xlite + xsat - xlite * xsat;
  }
  x1 = 2.0 * xlite - x2;
  if (fabs(xsat) < 0.0001) {
    *ired  = (int) (256.0 * xlite);
    *igreen= *ired;
    *iblue = *ired;
  } else {
    vr = clrvlc(x1, x2, xhue);
    *ired = 256.0 * vr;
    vg = clrvlc(x1, x2, (xhue - 120.0));
    *igreen = 256.0 * vg;
    vb = clrvlc(x1, x2, (xhue + 120.0));
    *iblue = 256.0 * vb;
  }
  return;
}

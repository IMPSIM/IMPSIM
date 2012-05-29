/* ------------------------------------------------------------------ */
/* tohlsc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Change RGB color parameters into equivalent HLS color parame-
|     ters.
|
|     Access:
|       void tohlsc(int ired, int igreen, int iblue, int *ihue,
|         int *ilite, int *isat);
|     int  ired,  i-Red   value, 0 <= ired   < 256.
|     int  igreen,i-Green value, 0 <= igreen < 256.
|     int  iblue, i-Blue  value, 0 <= iblue  < 256.
|     int *ihue,  o-Hue value, 0<=ihue<360, red=120, green=240, blue=0.
|     int *ilite, o-Percent lightness  value, 0 <= ilite <= 100.
|     int *isat,  o-Percent saturation value, 0 <= isat  <= 100.
|
|     Error Conditions:
|       If the ired, igreen, or iblue parameters are specified outside
|     of the range 0 <= ival < 256, they are treated modulo 256.
|       If the RGB parameters specifiy an achromatic case the *ihue
|     value is set to -1 to indicate an undefined hue.  However, *ilite
|     and *isat are defined correctly.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void tohlsc(int ired, int igreen, int iblue, int *ihue, int *ilite,
    int *isat)
#else
  void tohlsc(ired, igreen, iblue, ihue, ilite, isat)
  int ired, igreen, iblue, *ihue, *ilite, *isat;
#endif
{
  real xred, xgren, xblue, xmin, xmax, xhue, xlite, xsat, xrange,
    xredx, xgrenx, xbluex;
 
/* Convert ired, igreen, and iblue to real fractions. */
  xred  = (ired   & 255) / 255.0;
  xgren = (igreen & 255) / 255.0;
  xblue = (iblue  & 255) / 255.0;
 
/* Get max and min. */
  xmax = max3(xred, xgren, xblue);
  xmin = min3(xred, xgren, xblue);
 
/* Calculate lightness. */
  xlite = 0.5 * (xmax + xmin);
 
/* Calculate saturation and hue for the achromatic case. */
  if (fabs(xmax-xmin) <= 0.001) {
    xsat =  0.0;
    xhue = -2.0;
 
/* Calculate saturation and range for the polychromatic case. */
  } else {
    xrange = xmax - xmin;
    if (xlite <= 0.5) {
      xsat = xrange / (xmax - xmin);
    } else {
      xsat = xrange / (2.0 - xmax - xmin);
    }
    xredx  = (xmax - xred ) / xrange;
    xgrenx = (xmax - xgren) / xrange;
    xbluex = (xmax - xblue) / xrange;
    if (fabs(xred - xmax) <= 0.001) {
      xhue = xbluex - xgrenx;
    } else if (fabs(xgren - xmax) <= 0.001) {
      xhue = 2.0 + xredx - xbluex;
    } else if (fabs(xblue - xmax) <= 0.001) {
      xhue = 4.0 + xgrenx - xredx;
    }
 
/* Convert to degrees. */
    if (xhue <= 0) {
      xhue = xhue + 360.0;
    } else {
      xhue = 60.0 * xhue + 120.0;
    }
  }
 
/* Adjust HLS values to 0-360, 0-100, 0-100 ranges. */
  *ihue  = nint(xhue) % 360;
  *ilite = nint(100.0 * xlite);
  *isat  = nint(100.0 * xsat);
  return;
}

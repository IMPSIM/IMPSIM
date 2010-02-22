/* ------------------------------------------------------------------ */
/* idthrc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Function idthrc() is an ordered dither routine using a D(8)
|     dither matrix.
|
|     Access:
|       idithr = (int) idthrc(int intens, int ix, int iy);
|     int intens,i-Intensity value (0 =< intens < 256).
|     int ix,    i-Horizontal position of the pixel.
|     int iy,    i-Vertical   position of the pixel.
|     int idithr,o-Output dither value, i.e., 0 or 1.
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
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int idthrc(int intens, int ix, int iy)
#else
  int idthrc(intens, ix, iy)
  int intens, ix, iy;
#endif
{
  static int idthr8[8][8] = { {  0,48,12,60, 3,51,15,63 },
                              { 32,16,44,28,35,19,47,31 },
                              {  8,56, 4,52,11,59, 7,55 },
                              { 40,24,36,20,43,27,39,23 },
                              {  2,50,14,62, 1,49,13,61 },
                              { 34,18,46,30,33,17,45,29 },
                              { 10,58, 6,54, 9,57, 5,53 },
                              { 42,26,38,22,41,25,37,21 } };
 
  if (intens < 4 * idthr8[iy % 8][ix % 8]) {
    return(0);
  } else {
    return(1);
  }
}

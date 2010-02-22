/* ------------------------------------------------------------------ */
/* ctablc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Set up both the alpha and the graphic color lookup tables.
|     Either set default hues at any lightness and saturation, or a
|     monochromatic scale of lightnesses at any hue.
|
|     Access:
|       (void) ctablc(int ncbits, int mode, int ihue, int ilit,
|         int isat);
|     int ncbits,i-Number of bit planes useable for colors.
|     int mode,i-Flag to define how lookup table parameters are set:
|       mode = 1 for default hues (any ilit and isat).
|       mode = 2 for linear lightnesses (any ihue and isat).
|       mode = 3 for log increasing lightnesses (any ihue and isat).
|       mode = 4 for log Decreasing lightnesses (any ihue and isat).
|       mode = 5 for sine increasing lightnesses (any ihue and isat).
|       mode = 6 for haversine lightnesses (any ihue and isat).
|     int ihue,i-Hue        value (0 <= ihue < 360).
|     int ilit,i-Lightness  value (0 <= ilit < 100).
|     int isat,i-Saturation value (0 <= isat < 100).
|
|     Error Conditions:
|       If mode is not in the range 1 <= mode <= 6, no action is taken.
|       Values of mode, ihue, ilit, and isat that are outside of their
|     allowed ranges are treated modulo the maximum allowed values.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The graphic display device must be capable of changing its color
|     lookup table.
|       The default hues for mode = 1 are:
|         no. ihue  name        no. ihue  name       no. ihue  name
|          0   ---  black        6   180  yellow     11   330  a_blue
|          1   ---  white        7   210  y_green    12     0  blue
|          2   120  red          8   240  green      13    30  b_violet
|          3   140  r_orange     9   270  g_aqua     14    60  violet
|          4   160  orange      10   300  aqua       15    90  v_red
|          5   170  o_yellow
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ctablc(int ncbits, int mode, int ihue, int ilit, int isat)
#else
  void ctablc(ncbits, mode, ihue, ilit, isat)
  int ncbits, mode, ihue, ilit, isat;
#endif
{
  int icolor, j, jhue, jlit, jsat, kolor, mxclrs;
  static int khue[2][14] = {
    { 120,120,160,160,180,180,240,240,240,  0,  0, 60, 60,120 },
    { 120,140,160,170,180,210,240,270,300,330,  0, 30, 60, 90 } };
 
/* Set color 0 = black and color 1 = white. */
  cmapc(0, 0, 0, 0);
  cmapc(1, 0, 99, 99);
 
/*  Distribute the colors or lightnesses per the requested mode. */
  if (ncbits > 1){
    mxclrs = (1 << ncbits) - 2;
    jhue = ihue;
    jlit = ilit;
    jsat = isat;
    kolor = 0;
    for (j=2; j<MXCOLOR; j++) {
      icolor = ((nint((j - 2) * mxclrs / 14.0)) % mxclrs) + 2;
      if (icolor > kolor) {
        if (mode == 1) {
          jhue = khue[min(ncbits, 4) - 3][j - 2];
        } else if (mode == 2) {
          jlit = nint(100.0 * (j - 1) / 15.0);
        } else if (mode == 3) {
          jlit = nint(pow(1.359356391, (double) (j - 1)));
        } else if (mode == 4) {
          jlit = nint(pow(100.0 - 1.359356391, (double) (16 - j)));
        } else if (mode == 5) {
          jlit = nint(100.0 * sin((j - 1) * PI / 30.0));
        } else if (mode == 6) {
          jlit = nint(100.0 * (1.0 - cos((j - 1) * PI / 30.0)));
        }
        cmapc(icolor, (jhue % 360), (jlit % 100), (jsat % 100));
        kolor = icolor;
      }
    }
  }
  return;
}

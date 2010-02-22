/* ------------------------------------------------------------------ */
/* cmapc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Change the color mapping of entry kcolor in the color lookup
|     table by modifying its HLS color parameters.
|
|     Access:
|       (void) cmapc(int kcolor, int khue, int klite, int ksat);
|     int kcolor,i-Color lookup table entry number, 0<=kcolor<=15.
|     int khue,  i-Hue value for kcolor entry.
|     int klite, i-Lightness value for kcolor entry.
|     int ksat,  i-Saturation value for kcolor entry.
|
|     Error Conditions:
|       If kcolor is not in the range 0 <= kcolor < MXCOLOR, no action
|     is taken.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The graphic display device must be capable of changing its color
|     lookup table.
|       Only one color lookup table entry can be modified by each call
|     to cmapc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  void cmapc(int kcolor, int khue, int klite, int ksat)
#else
  void cmapc(kcolor, khue, klite, ksat)
  int  kcolor, khue, klite, ksat;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    long krgb;
# endif
  int kred, kgreen, kblue;

  if (kcolor >= 0 && kcolor < MXCOLOR) {
    if (dspdvc == DT_GRAPHIC) {
#     ifdef __WATCOMC__
        torgbc(khue, klite, ksat, &kred, &kgreen, &kblue);
        krgb = 256 * (256 * (kblue / 4) + kgreen / 4) + kred / 4;
        _remappalette(kcolor, krgb);
#     else
/* ** Not yet implemented in X. ** */
#     endif
    }
  }
  return;
}

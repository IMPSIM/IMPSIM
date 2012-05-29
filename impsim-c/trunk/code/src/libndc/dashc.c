/* ------------------------------------------------------------------ */
/* dashc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Set the integer dash pattern code for subsequent visible lines.
|
|     Access:
|       (void) dashc(int icode)
|     int icode,i-A positive integer code number whose digits specify
|       the length and visibility of each individual line segment in a
|       repeating dash pattern.
|       icode < 10 are treated modulo 5.
|       icode = 0 specifies a solid line.
|       icode = 1 specifies a dotted line.
|       icode = 2 specifies a dot-dashed line.
|       icode = 3 specifies a short-dashed line.
|       icode = 4 specifies a long-dashed line.
|       icode >= 10 specifies a software dashed line where the values
|         the individual digits are set to:
|         0 for a  visible   line segment of 0.005 screen units.
|         1 for an invisible line segment of 0.005 screen units.
|         2 for a  visible   line segment of 0.010 screen units.
|         3 for an invisible line segment of 0.010 screen units.
|         4 for a  visible   line segment of 0.025 screen units.
|         5 for an invisible line segment of 0.025 screen units.
|         6 for a  visible   line segment of 0.050 screen units.
|         7 for an invisible line segment of 0.050 screen units.
|         8 for a  visible   line segment of 0.100 screen units.
|         9 for an invisible line segment of 0.100 screen units.
|
|     Error Conditions:
|       Negative values of icode are treated according to their absolute
|     values.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       dashc() itself causes no lines to be drawn on the graphic
|     display.  It only defines the dash pattern for subsequent lines
|     drawn by other routines.
|       The dash pattern can be changed at will by repeated calls to
|     dashc() with different values for icode.
|       icode = 0 is assumed for all lines drawn before the first call
|     to dashc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void dashc(int icode)
#else
  void dashc(icode)
  int icode;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    unsigned short jstyle;
# else
#   include "xglblc.h"
    static int  dash_max[] = {2, 4, 2, 2, 10};
    static char dotted[2] = {3, 1};                   /* Dot pattern. */
    static char dot_dashed[4] = {3, 1, 3, 4};    /* Dot-dash pattern. */
    static char short_dashed[2] = {4, 4};      /* Short-dash pattern. */
    static char long_dashed[2] = {4, 7};        /* Long-dash pattern. */
    static char soft_dashed[MXDASH];            /* Soft-dash pattern. */
    static char *dash_table[] = { dotted, dot_dashed, short_dashed,
      long_dashed, soft_dashed };
    int dash_length[MXDASH], junk;
# endif
  static real table[MXDASH] = { 0.005, -0.005,  0.010, -0.010,  0.025,
                               -0.025,  0.050, -0.050,  0.100, -0.100};
  int  j, k, n;
  real work[MXDASH];
 
/* Interpret the dash code. */
  if (dspdvc == DT_GRAPHIC) {
    idash = abs(icode);
    if (idash < 10) {
      idash %= 5;
#     ifdef __WATCOMC__
        if (idash == 0) {
          jstyle = 0xFFFF;
        } else if (idash == 1) {
          jstyle = 0x3333;
        } else if(idash == 2) {
          jstyle = 0x33FF;
        } else if(idash == 3) {
          jstyle = 0x3F3F;
        } else if(idash == 4) {
          jstyle = 0x3FFF;
        }
#     endif
      ndash = 0;
 
/* Store the dash pattern. */
    } else {
      n = idash;
      for (j=0; j<MXDASH; j++) {
        if (n == 0) break; 
        k = n % 10;
        n = n / 10;
        work[j] = table[k];
      }
      ndash = j;
      for (k=0; k<ndash; k++) {
        j--;
        dshtbl[k] = work[j];
      }
    }
    if (idash < 10) {
#     ifdef __WATCOMC__
        _setlinestyle(jstyle);
#     else
        if (idash) {
          if(idash > 4) {
            for (j=0; j<ndash; j++) {
              AbstoPix(soft_dashed[j], junk, fabs(dshtbl[j]), 0.0);
            }
            dash_max[4] = j;
            idash = 5;
          }
          idash--;
          XSetLineAttributes(dsp, line_gc, 1, LineOnOffDash, CapButt,
            JoinMiter);
          XSetDashes(dsp, line_gc, 0, dash_table[idash],
            dash_max[idash]);
        } else {
          XSetLineAttributes(dsp, line_gc, 1, LineSolid, CapButt,
            JoinMiter);
        }
#     endif
      idash = 0;
    }
  }
  ldash  = 0;
  dshseg = 0.0;
  lspen  = FALSE;
  return;
}

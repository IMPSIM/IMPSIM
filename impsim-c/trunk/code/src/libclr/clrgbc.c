/* ------------------------------------------------------------------ */
/* clrgbc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Determine the RGB equivalent for a given JJU color number.
|
|     Access:
|       (void) clrgbc(int ncolor, int *ired, int *igrn, int *iblu)
|     int  ncolor,i-JJU color number for which RGB values are sought.
|     int *ired,  o-The red value for the given color   (0<ired<255).
|     int *igrn,  o-The green value for the given color (0<igrn<255).
|     int *iblu,  o-The blue value for the given color  (0<iblu<255).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The default JJU color numbers are:
|     no.  Hue  name        no.  hue  name       no.  hue  name
|      0   ---  black        6   180  yellow     11   330  a_blue
|      1   ---  white        7   210  y_green    12     0  blue
|      2   120  red          8   240  green      13    30  b_violet
|      3   140  r_orange     9   270  g_aqua     14    60  violet
|      4   160  orange      10   300  aqua       15    90  v_red
|      5   170  o_yellow
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef    ANSI
  void clrgbc(int ncolor, int *ired, int *igrn, int *iblu)
#else
  void clrgbc(ncolor, ired, igrn, iblu)
  int ncolor, *ired, *igrn, *iblu;
#endif
{
  static int khue[MXCOLOR] = { 0,   0, 120, 140, 160, 170, 180, 210,
                             240, 270, 300, 330,   0,  30,  60,  90 };
  int icolor, ihue, ilit, isat;
 
  icolor = abs(ncolor) % MXCOLOR;
  if (icolor == 0){
    ihue = 0;
    ilit = 0;
    isat = 0;
  } else if (icolor == 1){
    ihue = 0;
    ilit = 99;
    isat = 0;
  } else {
    ihue = khue[icolor];
    ilit = 50;
    isat = 99;
  }
  torgbc(ihue, ilit, isat, ired, igrn, iblu);
  return;
}

/* ------------------------------------------------------------------ */
/* drmnuc-01 Jan 00:03 Oct 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Draw and label the current menu.
|
|     Access:
|       (void) drmnuc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The menu headers must have been defined by a previous call to
|     ldhdrc(), and menu options must have been defined by a previous
|     call to ldmnuc().
|       The color of the menu boxes is set per the current value of
|     kmenu; the menu option text is set per the kmntxt value.  The
|     current menu header is highlighted in color KSHOW.  The pen and
|     text colors are reset to kfrgnd and ktext before exit.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void drmnuc()
{
# ifdef __WATCOMC__
#   include <graph.h>
# else
#   include "xglblc.h"
# endif
# define KSHOW  3      /* Color for highlighting current menu header. */
  int  i, kheadr, kolor, noptmx;
  real s, t, deltas, deltat, ds, sbox[4], tbox[4], s0, rows;
  static real tsave = 0.90;
 
/* Calculate menu spacing parameters. */
  xtrasz = min(max(1.0 /
    (((real) (menumx + MXGLOBAL)) * tsymbl) - 1.0, - 0.25), 0.0);
  deltas = 10.0 * ssymbl;
  deltat = (0.995 + xtrasz) * tsymbl;
  noptmx = (int) (1.0 / deltat - ((real) MXGLOBAL) - 0.01);
  menumx = min(noptmx, menumx);
  s0     = 1.0 - deltas;
  ds     = ssymbl;
 
/* Eliminate the previous menu box. */
  colrfc(kbkgnd);
  sbox[0] = 1.0;
  tbox[0] = 1.0;
  sbox[1] = s0;
  tbox[1] = 1.0;
  sbox[2] = s0;
  tbox[2] = tsave;
  sbox[3] = 1.0;
  tbox[3] = tsave;
  fillsc(4, sbox, tbox);
 
/* Fill the current menu box. */
  colrfc(kmenu);
  tsave = 1.0 - ((real) ((menumx + MXGLOBAL))) * deltat;
  sbox[0] = 1.0;
  tbox[0] = 1.0;
  sbox[1] = s0;
  tbox[1] = 1.0;
  sbox[2] = s0;
  tbox[2] = tsave;
  sbox[3] = 1.0;
  tbox[3] = tsave;
  fillsc(4, sbox, tbox);
 
/* Fill the header box. */
  rows = (real) imin;
  sbox[0] = s0;
  tbox[0] = 1.0;
  sbox[1] = 0.0;
  tbox[1] = 1.0;
  sbox[2] = 0.0;
  tbox[2] = 1.0 - rows * deltat;
  sbox[3] = s0;
  tbox[3] = tbox[2];
  fillsc(4, sbox, tbox);
 
/* Label the header option boxes. */
  colrfc(kmntxt);
  colrsc(kmntxt);
  t = 1.0;
  for (i=0; i<nhdrs; i++) {
    if ((i % MXHDRS) == 0) {
      s = ds;
      t -= deltat;
    }
    movasc(s, t);
    htextc(header[i]);
    s += deltas;
  }
 
/* Label the global option boxes. */
  s = s0 + ds;
  t = 1.0;
  for (i=0; i<MXGLOBAL; i++) {
    t -= deltat;
    movasc(s, t);
    htextc(global[i]);
  }
 
/* Label the current option boxes. */
  for (i=0; i<menumx; i++) {
    t -= deltat;
    movasc(s, t);
    htextc(menu[i]);
  }
 
/* Draw lines to separate option groups. */
  t = 1.0 - ((real) MXGLOBAL) * deltat;
  movasc(s0, 1.0);
  drwasc(s0, t);
  drwasc(1.0, t);
 
/* Highlight the current header label. */
  kolor = KSHOW;
  colrfc(kolor);
  colrsc(kolor);
  kheadr = khdr - 1;
  s = (kheadr % MXHDRS) * deltas + ds;
  t = 1.0 - ((real) (kheadr / MXHDRS + 1)) * deltat;
  movasc(s, t);
  htextc(header[kheadr]);
  ipen = max(ipen, line0 + imin);
# ifdef __WATCOMC__
    if (dspdvc == DT_GRAPHIC) _settextposition(ipen - line0 + 1, 1);
# endif
  colrsc(ktext);
  colrfc(kfrgnd);
  return;
# undef KSHOW
}

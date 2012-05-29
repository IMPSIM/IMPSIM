/* ------------------------------------------------------------------ */
/* qcolrc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Return the color numbers from the libcad colorc memory.
|
|     Access:
|       (void) qcolrc(int *nbkgnd, int *nfrgnd, int *nmenu, int *nmntxt,
|         int *ntext, int *npctbr, int *naxes, int *ndfgeo,int *nvface);
|     int *nbkgnd,i-Color number for display background.
|     int *nfrgnd,i-Color number for display foreground.
|     int *nmenu, i-Color number for menu box outlines.
|     int *nmntxt,i-Color number for text in menu boxes.
|     int *ntext, i-Color number for text.
|     int *npctbr,i-Color number for percent completed bar.
|     int *naxes, i-Color number for axes, scale factor, etc.
|     int *ndfgeo,i-Color number for new geometry.
|     int *nvface,i-Color number for virtual cut faces.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The color numbers returned fit the JJU definitions which define
|     their hues.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qcolrc(int *nbkgnd, int *nfrgnd, int *nmenu, int *nmntxt,
    int *ntext, int *npctbr, int *naxes, int *ndfgeo, int *nvface)
#else
  void qcolrc(nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes,
    ndfgeo, nvface)
  int *nbkgnd, *nfrgnd, *nmenu, *nmntxt, *ntext, *npctbr, *naxes,
    *ndfgeo, *nvface;
#endif
{
  *nbkgnd = kbkgnd;
  *nfrgnd = kfrgnd;
  *nmenu  = kmenu;
  *nmntxt = kmntxt;
  *ntext  = ktext;
  *npctbr = kpctbr;
  *naxes  = kaxes;
  *ndfgeo = kdfgeo;
  *nvface = kvface;
  return;
}

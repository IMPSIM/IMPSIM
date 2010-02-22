/* ------------------------------------------------------------------ */
/* ldclrc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Load the color numbers into the libcad colorc memory.
|
|     Access:
|       (void) ldclrc(int nbkgnd, int nfrgnd, int nmenu, int nmntxt,
|         int ntext, int npctbr, int naxes, int ndfgeo, int nvface);
|     int nbkgnd,i-Color number for display background.
|     int nfrgnd,i-Color number for display foreground.
|     int nmenu, i-Color number for menu box outlines.
|     int nmntxt,i-Color number for text in menu boxes.
|     int ntext, i-Color number for text.
|     int npctbr,i-Color number for percent completed bar.
|     int naxes, i-Color number for axes, scale factor, etc.
|     int ndfgeo,i-Color number for new geometry.
|     int nvface,i-Color number for virtual cut faces.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The color numbers must fit the JJU definitions which define
|     their hues.
|       Any color numbers set equal to kbkgnd (normally zero) will not
|     produce visible items on the display screen.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void ldclrc(int nbkgnd, int nfrgnd, int nmenu, int nmntxt, int ntext,
    int npctbr, int naxes, int ndfgeo, int nvface)
#else
  void ldclrc(nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes,
    ndfgeo, nvface)
  int nbkgnd, nfrgnd, nmenu, nmntxt, ntext, npctbr, naxes, ndfgeo,
    nvface;
#endif
{
  kbkgnd = nbkgnd;
  kfrgnd = nfrgnd;
  kmenu  = nmenu;
  kmntxt = nmntxt;
  ktext  = ntext;
  kpctbr = npctbr;
  kaxes  = naxes;
  kdfgeo = ndfgeo;
  kvface = nvface;
  return;
}

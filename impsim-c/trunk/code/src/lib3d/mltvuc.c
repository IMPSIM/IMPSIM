/* ------------------------------------------------------------------ */
/* mltvuc-11 Aug 03:25 Sep 07
|     (C)Copyright, JJU Research, 2003-2007.
|
|     Description:
|       Control the window settings and transformation parameters for
|     multiple-view drawing scenes.
|
|     Access:
|       (void) mltvuc(int mviews, int iviews[mviews], int *draw);
|     int  mviews,  i-Number of views to be drawn; mviews = 1, 2, or 4.
|     int  iviews[],i-view directory numbers for the views.
|     int *draw,    o-Flag indicating whether view is to be drawn.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       View directory numbers are defined as stored by vstorc().
|       The strategy which must be followed by the calling function is:
|            ...   ...   ...
|            newpgc();
|            do {
|              mltvuc(nviews, iviews, &draw);
|              if (draw) {
|                <call to local drawing function for the scene>;
|              }
|            } while (draw);
|            ...   ...   ...
|     The user must supply the local function which performs the actual
|     drawing logic for the scene.  This local function must use the 3-D
|     libcad drawing functions.  The same function is called multiple
|     times as the viewing parameters and transformations are modified
|     by the mltvuc() function.
|       System.title may be displayed at the bottom center of the screen 
|     after the last view is drawn.
*
*     History:
*     11 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void mltvuc(int mviews, int iviews[], int *draw)
#else
  void mltvuc(mviews, iviews, draw)
  int mviews, iviews[], *draw;
#endif
{
  int    i, jview, khdr, nhdrs;
  real   s1, s2, ssymbl, t1, t2, tsymbl, w2, wctr, wide;
  static int  kount, lldraw, lstart = TRUE;
  static real smx, smn, swide, tmx, tmn, uctr, uhlf, umx, umn, vctr,
    vmx, vmn, w3, xctr, yctr, zctr;
 
/* Copy view numbers to the viewc.h header array. */
  if (lstart) {
    nviews = mviews;
    for (i=1; i<=nviews; i++) {
      jviews[i] = iviews[i-1];
    }
  }

/* Save the original view parameters and window. */
  lldraw = TRUE;
  if (nviews <= 0) {
    if (lstart) {
      lstart = FALSE;
    } else {
      lstart = TRUE;
      lldraw = FALSE;
    }
    goto _RETURN;
  }
  if (lstart) {
    vstorc(0, "Saved current view");
    qhdrc(&khdr, &nhdrs);
    qfrmsc(&smn, &tmn, &smx, &tmx);
    qfrm2c(&umn, &vmn, &umx, &vmx);
    qchszc(&ssymbl, &tsymbl);
    wide = (nhdrs > 0) ? (1.0) : (1.0 - 10.0 * ssymbl);
    swide = wide;
    uctr = 0.5 * (umx + umn);
    vctr = 0.5 * (vmx + vmn);
    uhlf = 0.5 * (umx - umn);
    x2to3c(uctr, vctr, 0.0, 1.0, &xctr, &yctr, &zctr, &w3);
    kount  = 0;
    lstart = FALSE;
  }

/* Define the window transformation parameters. */
  kount++;
  if (nviews == 1) {                                     /* One view. */
    s1 = 0.0;
    t1 = 0.0;
    s2 = swide;
    t2 = 1.0;
  } else if (nviews == 2) {                             /* Two views. */
    if (kount == 1) {
      s1 = 0.0;
      s2 = 0.5 * swide;
    } else {
      s1 = 0.5 * swide;
      s2 = swide;
    }
    t1 = 0.25;
    t2 = 0.75;
  } else if (nviews == 4) {                            /* Four views. */
    if        (kount == 1) {
      s1 = 0.0;
      t1 = 0.5;
      s2 = 0.5 * swide;
      t2 = 1.0;
    } else if (kount == 2) {
      s1 = 0.0;
      t1 = 0.0;
      s2 = 0.5 * swide;
      t2 = 0.5;
    } else if (kount == 3) {
      s1 = 0.5 * swide;
      t1 = 0.0;
      s2 = swide;
      t2 = 0.5;
    } else if (kount == 4) {
      s1 = 0.5 * swide;
      t1 = 0.5;
      s2 = swide;
      t2 = 1.0;
    }
  }

/* Recall the appropriate view transformation. */
  if (kount <= nviews) {
    jview = jviews[kount];
    vreadc(jview);
    framsc(s1, t1, s2, t2);  /* Redefine the screen to 2-D transform. */
    x3to2c(xctr, yctr, zctr, w3, &uctr, &vctr, &wctr, &w2);
    fram2c(uctr - uhlf, vctr, uctr + uhlf, vctr);

/* Restore the original transformation. */
  } else {
    framsc(smn, tmn, smx, tmx);
    fram2c(umn, vmn, umx, vmx);
    jview = jviews[0];
    vreadc(jview);
    lstart = TRUE;
    lldraw = FALSE;
  }
_RETURN:
  *draw = lldraw;
  return;
}

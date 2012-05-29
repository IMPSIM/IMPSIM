/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:10 Jun 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* viewc-01 Aug 03:22 Sep 07
|    (C)Copyright, JJU Research, 2003-2007.
*
*     History:
*     01 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  VIEWC_INCLUDED
  extern real  szaxes;        /* Size of global 3-D axes to be drawn. */
  extern real  expand;/*Percent actual size for faces after expansion.*/
  extern real  crease;       /* Crease angle for 3-D edge visibility. */
  extern real  xresol;  /* Hidden/shaded image horizontal resolution. */
  extern real  yresol;  /* Hidden/shaded image vertical   resolution. */
  extern real  ambent; /* Coefficient of ambient  lighting intensity. */
  extern real  difuse; /* Coefficient of diffuse  lighting intensity. */
  extern real  spculr; /* Coefficient of specular lighting intensity. */
  extern real  shiny;  /* Exponent   for specular lighting intensity. */
  extern real  rlight[3];      /*Global position of the light source. */
  extern int   iexprt;     /* Expertise expected of interactive user. */
  extern int   ivrbos;     /* Detail desired  for interactive output. */
  extern int   nviews;      /* Number of views in a multi-view scene. */
  extern int   jviews[5];        /* View numbers for multiview scene. */
  extern int   khilit;/* Packed RGB highlite values for shaded image. */
  extern int   lsaved;      /* Flag set TRUE when geometry is stored. */
  extern int   ldraw; /* Flag set TRUE for redraw after each erasure. */
  extern int   lmenu;       /* Flag set TRUE for displaying the menu. */
  extern int   label;    /* Flag set TRUE for displaying face labels. */
  extern int   lpoor;        /* Flag set TRUE for poormans algorithm. */
  extern int   lhide;    /* Flag set TRUE for hidden surface removal. */
  extern int   l1pass;/* Flag set TRUE for single pass hidden images. */
  extern int   lshade;            /* Flag set TRUE for shaded images. */
  extern int   lrvsvd;    /* Flag set true for reversed video images. */
# define VIEWC_INCLUDED
#endif

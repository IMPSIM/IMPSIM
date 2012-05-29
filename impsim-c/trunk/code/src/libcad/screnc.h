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
/* screnc-01 Jan 00:22 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#ifndef SCRENC_INCLUDED
  extern int   lsmode;         /* Flag set TRUE when in graphic mode. */
  extern int   lspen;   /* Flag set TRUE when graphic pen is visible. */
  extern int   l2pen;        /* Flag set TRUE when 2D pen is updated. */
  extern int   l3pen;        /* Flag set TRUE when 3D pen is updated. */
  extern int   scroll_en; /* Flag set TRUE when scrolling is enabled. */
  extern int   atext_en; /* Flag set TRUE when alpha text is enabled. */
  extern int   imin; /* Row number of first printable line of screen. */
  extern int   ipen;         /* Row number of last string in textq[]. */
  extern int   jpen;      /* Number of last character in textq[ipen]. */
  extern int   imax;      /* Total available rows    on alpha screen. */
  extern int   jmax;      /* Total available columns on alpha screen. */
  extern char *global[MXGLOBAL];/* Global strings listed by drmnuc(). */
  extern int   menumx;    /* Number of menu items listed by drmnuc(). */
  extern char *menu[MXMENU]; /* Menu item strings listed by drmnuc(). */
  extern int   nhdrs;  /* Total number of headers listed by drmnuc(). */
  extern char *header[MXHEADER];/* Header strings listed by drmnuc(). */
  extern int   khdr;            /* Number of the current menu header. */
  extern int   icolra; /* Color number of current alpha text setting. */
  extern int   icolrb; /* Color number of current background setting. */
  extern int   icolrf;/* Color number of current graphic pen setting. */
  extern int   icolrs;/* Color number of current screen text setting. */
  extern int   iline;             /* Line style code for graphic pen. */
  extern int   idash;           /* Dash pattern code for graphic pen. */
  extern int   ndash;   /* Number of strokes in current dash pattern. */
  extern int   ldash;   /* Current stroke number within dash pattern. */
  extern real  dshtbl[MXDASH];/* Table defining dash pattern lengths. */
  extern real  dshseg; /* Percent of dash stroke left from last line. */
  extern real  xtrasz;    /* Increase of menu box height over tsymbl. */
  extern real  spen;/*Actual horizontal screen coord. of graphic pen. */
  extern real  tpen; /* Actual vertical screen coord. of graphic pen. */
  extern real  smin;  /* Minimum horizontal of current screen window. */
  extern real  tmin;    /* Minimum vertical of current screen window. */
  extern real  smax;  /* Maximum horizontal of current screen window. */
  extern real  tmax;    /* Maximum vertical of current screen window. */
  extern real  aspect;         /* Aspect ratio of the graphic screen. */
  extern real  sscale; /* Horizontal pixels per graphic screen width. */
  extern real  tscale;  /* Vertical pixels per graphic screen height. */
  extern real  ssymbl; /* Screen size of one graphic character width. */
  extern real  tsymbl;/* Screen size of one graphic character height. */
  extern real  stzero;    /* Screen tolerance smaller than one pixel. */
  extern real  zrogeo;        /* Tolerence value for geometric tests. */
# define SCRENC_INCLUDED
#endif

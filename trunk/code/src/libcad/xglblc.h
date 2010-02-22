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
/* xglblc-01 Jan 00:01 Jan 04
|     (C)Copyright, JJU Research, 2000-2004.
*
*     History:
*     01 Jan 00:JJU-Original.
*     16 Feb 03:JJU Renamed from globlx.h
* ------------------------------------------------------------------- */

#ifndef  XGLBLC_INCLUDED
  extern int           X_Initialized;/* Indicates xinitc() was called.*/
  extern Display      *dsp;
  extern int           screen;
  extern int           depth;
  extern Window        rootwin;
  extern Window        win;
  extern unsigned long event_mask;
  extern XEvent        report;
  extern Cursor        arrow_cursor;
  extern Cursor        watch_cursor;
  extern Pixmap        pixmap;
  extern Pixmap        txtmap;
  extern Colormap      cmap;
  extern int           colors[MXCOLOR];
  extern XColor        xcolors[MXCOLOR];
  extern GC            text_gc;          /* Graphic context for text. */
  extern GC            gtext_gc; /* Graphic context for graphic text. */
  extern GC            line_gc;         /* Graphic context for lines. */
  extern GC            fill_gc;  /* Graphic context for filled areas. */
  extern GC            bkgnd_gc;      /* Graphic context for erasing. */
  extern int           font_height;                   /* Font height. */
  extern XFontStruct  *font_info; /* Info about the font we're using. */
  extern int           xpos, ypos;        /* Current window position. */
  extern int           xpix, ypix;          /* Window size in pixels. */
  extern int           xwmin, ywmin;/* Minimum Window size in pixels. */
  extern char         *TitleBar;        /* Title Bar for new windows. */
  extern char          FontName[32];                  /* Font to use. */
  extern int           txt_drwn;  /* Any text on the graphics window? */
  extern int           pix_drwn;/* Any NEW pixels on graphics window? */
  extern char         *crsr;                      /* The text cursor. */
  extern int           crsron;          /* Is the text cursor in use? */
  extern int           crsrx, crsry;/* Text cursor position (if used).*/
  extern int           ctrl_indx;/* Indicates if Control key is held. */
  extern int           rev_video; /* Is the video currently reversed? */
# define XGLBLC_INCLUDED
#endif

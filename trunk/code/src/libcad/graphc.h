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
/* graphc-01 Jan 00:23 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  GRAPHC_INCLUDED
  extern int  kgrid;    /* Flag indicating linear/log axes for graph. */
  extern real sgmin;    /* Screen coordinates for left edge of graph. */
  extern real tgmin;  /* Screen coordinates for bottom edge of graph. */
  extern real sgmax;   /* Screen coordinates for right edge of graph. */
  extern real tgmax;     /* Screen coordinates for top edge of graph. */
  extern real pscale; /* Horizontal scale factor for graph to screen. */
  extern real qscale;   /* Vertical scale factor for graph to screen. */
  extern real p0;   /* Horizontal offset from graph to screen origin. */
  extern real q0;     /* Vertical offset from graph to screen origin. */
# define GRAPHC_INCLUDED
#endif

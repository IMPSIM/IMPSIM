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
/* colorc-01 Jan 00:23 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  COLORC_INCLUDED
  extern int kbkgnd;          /* Color number for display background. */
  extern int kfrgnd;          /* Color number for display foreground. */
  extern int kmenu;           /* Color number for menu box  outlines. */
  extern int kmntxt;          /* Color number for text in menu boxes. */
  extern int ktext;                         /* Color number for text. */
  extern int kpctbr;       /* Color number for percent completed bar. */
  extern int kaxes;      /* Color number for axes, scale factor, etc. */
  extern int kdfgeo;        /* Default color number for new geometry. */
  extern int kvface;          /* Color number for virtual  cut faces. */
# define COLORC_INCLUDED
#endif

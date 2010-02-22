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
/* viewsc-01 Jan 00:25 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  VIEWSC_INCLUDED
  extern char filvue[MXFLCH+1];   /* Name of direct access view file. */
  extern char idvue[MXVIEW+1][MXFLCH+1];  /* Titles for stored views. */
  extern real x32vue[MXVIEW+1][3][3]; /* Array of stored view xforms. */
  extern int  lvue[MXVIEW+1];     /* Array of flags for stored views. */
# define VIEWSC_INCLUDED
#endif

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
/* imagec-01 Jan 00:23 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  IMAGEC_INCLUDED
  extern real x3pen;      /* X-coordinate of current 3D pen location. */
  extern real y3pen;      /* Y-coordinate of current 3D pen location. */
  extern real z3pen;      /* Z-coordinate of current 3D pen location. */
  extern real w3pen; /* Homog. coordinate of current 3D pen location. */
  extern real x3to2[4][4]; /* 3D to page (4x4) transformation matrix. */
  extern real x2to3[4][4]; /* Page to 3D (4x4) transformation matrix. */
# define IMAGEC_INCLUDED
#endif

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
/* pagec-01 Jan 00:25 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  PAGEC_INCLUDED
  extern real x2pen;        /* Horizontal page coord of pen location. */
  extern real y2pen;     /* Vertical page coordinate of pen location. */
  extern real x2min;             /* Minimum horizontal page boundary. */
  extern real y2min;               /* Minimum vertical page boundary. */
  extern real z2min;                /* Minimum outward page boundary. */
  extern real x2max;             /* Maximum horizontal page boundary. */
  extern real y2max;               /* Maximum vertical page boundary. */
  extern real z2max;                /* Maximum outward page boundary. */
  extern real x2scal;      /* Horizontal page to screen scale factor. */
  extern real y2scal;        /* Vertical page to screen scale factor. */
  extern real x20;               /* Horizontal page to screen offset. */
  extern real y20;                 /* Vertical page to screen offset. */
  extern real eyeinv; /* Reciprocal of 3D eye distance from the page. */
# define PAGEC_INCLUDED
#endif

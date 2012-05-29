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
/* iodvc-01 Jan 00:23 Sep 07
|    (C)Copyright, JJU Research, 2000-2007.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  IODVC_INCLUDED
  extern int   intact;    /* Flag set TRUE for interactive execution. */
  extern int   lunin;                /* Stream number for input data. */
  extern int   lunio;               /* Stream number for output data. */
  extern int   lunerr;           /* Stream number for error messages. */
  extern int   luneco;   /* Stream number for echo of input commands. */
  extern int   lunpr;            /* Stream number for printed output. */
  extern int   lunrd;            /* Stream number for input commands. */
  extern int   lunwr;    /* Stream number for output of command file. */
  extern int   lunsmb;   /* Stream number for stroked character file. */
# define IODVC_INCLUDED
#endif

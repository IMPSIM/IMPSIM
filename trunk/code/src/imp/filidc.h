/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
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
/* filidc-01 Jan 00:17 Jan 04
|    (C)Copyright, JJU Research, 2000-2004.
*
*     History:
*     01 Jan 00:JJU-Original.
*     17 Jan 04:JJU-Moved filedir, helpdir, homedir to libcad diridc.h.
* ------------------------------------------------------------------- */

#ifndef  FILIDC_INCLUDED
  extern char *idfile[3];/* Names for imp list, plot and store files. */
  extern int   lunfil[3]; /* Stream no's for list, plot, store files. */
# define FILIDC_INCLUDED
#endif

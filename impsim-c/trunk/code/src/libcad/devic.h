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
/* devic-01 Jan 00:23 Jun 03
|    (C)Copyright, JJU Research, 2000-2003.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#ifndef  DEVIC_INCLUDED
  extern enum  Dsptyp dspdvc;              /* Current display device. */
  extern char *DspTyp[MXDSPLAY];        /* Display device type names. */
  extern enum  Chctyp chdvc;          /* Current choice input device. */
  extern char *ChcTyp[MXCHOICE];         /* Choice device type names. */
  extern enum  Loctyp lcdvc;         /* Current locator input device. */
  extern char *LocTyp[MXLOCATR];        /* Locator device type names. */
# define DEVIC_INCLUDED
#endif

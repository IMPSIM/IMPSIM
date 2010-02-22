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
/* dtimec-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Store data for incrementing time during the simulation.
|
|     Access:
|       (void) dtimec(real tfinal, real dtmin, real dtio);
|     real tfinal,i-Ending time for the simulation.
|     real dtmin, i-Minimum time step allowed during the simulation.
|     real dtio,  i-Time step between outputs in the simulation.
|
|     Error Conditions:
|       System.nerror = 4 indicates faulty data.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void dtimec(real tfinal, real dtmin, real dtio)
#else
  void dtimec(tfinal, dtmin, dtio)
  real tfinal, dtmin, dtio;
#endif
{

/* Check the data. */
  if (tfinal < 0.0) {
    echoc();
    textc("*** Data for final time is in error. ***", TRUE);
    System.nerror = 4;
  } else if (dtmin <= 0.0) {
    echoc();
    textc("*** Data for minimum time increment is in error. ***", TRUE);
    System.nerror = 4;
  } else if (dtio <= 0.0) {
    echoc();
    textc("*** Data for print interval is in error. ***", TRUE);
    System.nerror = 4;

/* Store the data. */
  } else {
    System.tfinal = tfinal;
    System.dtmin  = dtmin;
    System.dtio   = dtio;
  }
  return;
}

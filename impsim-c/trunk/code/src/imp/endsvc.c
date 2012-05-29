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
/* endsvc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Deactivate the imp store:input and recall:input file.
|
|     Access:
|       (void) endsvc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void endsvc()
{
  int lunwr;

  lunwr = lunitc("write");
  if (lunwr > 0){
    fbkspc(lunwr);
    fprintf(streams[lunwr], "RETURN\n               ");
    fseek(streams[lunwr], -15, SEEK_CUR);
    fflush(streams[lunwr]);
  }
  writrc("off");
  readrc("off");
  return;
}

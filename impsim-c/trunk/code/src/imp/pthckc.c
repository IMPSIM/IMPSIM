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
/* pthckc-01 Jan 00:12 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Check for and correct any conflicts between paths and loops.
|
|     Access:
|       (void) pthckc(int **loops, int **paths);
|     int loops[nloops][njnts],i/o-The loop/joint incidence matrix.
|     int paths[nbdys][njnts], i/o-The path/joint incidence matrix.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The paths[][] matrix shows the path from each body to ground.
|       The path/loop interactions are driven to all positive by
|     recombining pieces of different loops with the paths.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void pthckc(int **loops, int **paths)
#else
  void pthckc(loops, paths)
  int  **loops, **paths;
#endif
{
  int i, interact, j, k, ldone, minint, minlp;

/* Find and resolve any conflicts between paths and loops. */
  if (System.nloops) {
_2: for (i=0; i<System.nbdys; i++) {
      ldone = FALSE;
      while (!ldone) {
        minint = 0;
        for (j=0; j<System.nloops; j++){/*Find path/loop interaction. */
          interact = 0;
          for (k=0; k<System.njnts; k++) {
            interact += paths[i][k] * loops[j][k];
          }
          if (interact < minint) { /* Find most negative interaction. */
            minint = interact;
            minlp  = j;
          }
        }
        if (minint < 0) { /* Solve conflict by merging path and loop. */
          for (k=0; k<System.njnts; k++) {
            paths[i][k] += loops[minlp][k];
          }
          goto _2;
        } else {
          ldone = TRUE;                               /* No conflict. */
        }
      }
    }
  }

/* Remove any loops contained in paths. */
  for (i=0; i<System.nbdys; i++) {
    for (j=0; j<System.nloops; j++) {
      ldone = TRUE;
      for (k=0; k<System.njnts; k++) {
        if ((loops[j][k] != 0) && (loops[j][k] != paths[i][k])) {
          ldone = FALSE;
          break;
        }
      }
      if (ldone) {
        for (k=0; k<System.njnts; k++) {
          paths[i][k] -= loops[j][k];
        }
      }
    }
  }
  return;
}

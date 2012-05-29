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
/* lpchkc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Form the loop/loop interaction matrix; then drive it to a state
|     where all entries >= zero by reversing loops or recombining parts
|     of different loops.
|
|     Access:
|       (void) lpchkc(int **loops);
|     int loops[nloops][njnts],i/o-The loop/edge incidence matrix.
|
|     Error Conditions:
|       nerror = 6 indicates an irreconcilable error in topology.  A
|     message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void lpchkc(int **loops)
#else
  void lpchkc(loops)
  int  **loops;
#endif
{
  int i, ij, **interact, j, k;

/* Allocate working space. */
  interact = (int **) calloc(System.nloops, sizeof(int *));
  for (i=0; i<System.nloops; i++) {
    interact[i] = (int *) calloc(System.nloops, sizeof(int));
  }

/* Form the loop interaction matrix. */
_4:
  for (i=0; i<System.nloops; i++) {
    for (j=0; j<System.nloops; j++) {
      interact[i][j] = 0;
      for (k=0; k<System.njnts; k++) {
        interact[i][j] += loops[i][k] * loops[j][k];
      }
    }
  }

/* Look for conflicts with previously verified loop orientations. */
  for (i=1; i<System.nloops; i++) {    /* Consider loop 0 to be okay. */

/* Skip all loops with which this loop does not interact. */
    j = -1;
_2:
    j++;
    if (j != i) {
      if (interact[i][j] == 0) {
        goto _2;

/* Check for consistent signs for all interactions. */
      } else if (interact[i][j] > 0) {
        while (interact[i][j] >= 0) {
          j++;
          if (j == i) goto _3;
        }
      } else if (interact[i][j] < 0) {
        while (interact[i][j] <= 0) {
          j++;
          if (j == i) {
            for (j=0; j<System.njnts; j++) {
              loops[i][j] = -loops[i][j];
            }
            goto _4;
          }
        }
      }

/* Recombine loops to resolve inconsistent interactions. */
      ij = 0;
      for (j=0; j<i; j++) {
        if (interact[i][j] < ij) {
          ij = interact[i][j];
          k = j;
        }
      }
      for (j=0; j<System.njnts; j++) {
        loops[i][j] += loops[k][j];
      }
      goto _4;
    }
_3: continue;
  }

/* Remove any loops contained within other loops. */
  for (i=0; i<System.nloops; i++) {
    for (j=0; j<System.nloops; j++) {
      if (i != j) {
        for (k=0; k<System.njnts; k++) {
          if ((loops[j][k]!=0) && (loops[j][k]!=loops[i][k])) goto _5;
        }
        for (k=0; k<System.njnts; k++) {
          loops[i][k] -= loops[j][k];
        }
_5:     continue;
      }
    }
  }
  for (i=0; i<System.nloops; i++) {
    free(interact[i]);
  }
  free (interact);
  return;
}

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
/* lpbfsc-01 Jan 00:12 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the topological loops and paths in the system by a breadth-
|     first tree search algorithm.
|
|     Access:
|       (void) lpbfsc(int nroot, int **incdnc, int **loops,
|         int **paths);
|     int nroot,               i-The index of the chosen root vertex.
|     int incdnc[nbdys][njnts],i-The vertex/edge incidence matrix.
|     int loops[nloops][njnts],o-The loop/edge incidence matrix found.
|     int paths[nbdys][njnts], o-The vertex/edge path matrix found.
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
  void lpbfsc(int nroot, int **incdnc, int **loops, int **paths)
#else
  void lpbfsc(nroot, incdnc, loops, paths)
  int  nroot, **incdnc, **loops, **paths;
#endif
{
  int *edge, i, ilevel, *preved, *prevvx, iqtop, iqbotm, *ique, iroot,
       ivertx, j, jedge, k, leaf, *level, loop, nremain;

/* Allocate working space. */
  edge   = (int *) calloc(System.njnts, sizeof(int));
  ique   = (int *) calloc(System.nbdys, sizeof(int));
  level  = (int *) calloc(System.nbdys, sizeof(int));
  preved = (int *) calloc(System.nbdys, sizeof(int));
  prevvx = (int *) calloc(System.nbdys, sizeof(int));

/* Initialize various arrays. */
  for (i=0; i<System.nbdys; i++) {
    ique[i]   =  0;
    level[i]  =  0;
    prevvx[i] = -2;
    preved[i] = -1;
  }
  for (j=0; j<System.njnts; j++) {
    edge[j] = FALSE;
    for (i=0; i<System.nloops; i++) loops[i][j] = 0;
    for (i=0; i<System.nbdys; i++)  paths[i][j] = 0;
  }

/* Initialize the starting vertex and the queue pointers. */
  ivertx = nroot;
  iqtop  = 0;
  iqbotm = 1;

/* Initialize the loop, and remaining-vertex counters. */
  loop    = -1;
  nremain = System.nbdys - 1;

/* Set up the starting vertex. */
  ique[0]        = ivertx;
  level[ivertx]  = 0;
  prevvx[ivertx] = -1;

/* See if the search has finished, i.e., if the queue is empty. */
  while (iqtop != iqbotm) {

/* Process the next vertex in the queue. */
    ivertx = ique[iqtop];
    iqtop  = (iqtop + 1) % System.nbdys;
    ilevel = level[ivertx] + 1;

/* Look for an edge which is incident to the current vertex. */
    for (j=0; j<System.njnts; j++) {
      if (incdnc[ivertx][j] != 0) {

/* Skip this edge if it has already been visited. */
        if (edge[j]) {
        } else {
          edge[j] = TRUE;                     /* Mark edge j visited. */

/* Find the other vertex of this edge. */
          for (i=0; i<System.nbdys; i++) {
            if ((incdnc[i][j] != 0) && (ivertx != i)) {

/* Check whether it has been visited. */
              if(prevvx[i] < -1) {

/* The vertex is not yet visited.  Enter it into the queue. */
                ique[iqbotm] = i;
                iqbotm = (iqbotm + 1) % System.nbdys;

/* Set up the tree, predecessor, level, and path. */
                prevvx[i] = ivertx;           /* Mark body i visited. */
                preved[i] = j;
                level[i]  = ilevel;
                for (k=0; k<System.njnts; k++) {
                  paths[i][k] = paths[ivertx][k];
                }
                paths[i][j] = incdnc[i][j];
                nremain--;
                break;
              }

/* The vertex is already visited.  Set up for building a loop. */
              ++loop;
              loops[loop][j] = incdnc[ivertx][j];
              leaf  = i;
              iroot = ivertx;

/* For level[iroot] less than level[leaf]. */
_2:           if(level[iroot] < level[leaf]) {
                jedge = preved[leaf];
                loops[loop][jedge] = incdnc[leaf][jedge];
                leaf  = prevvx[leaf];

/* For level[iroot] equal to level[leaf]. */
              } else if (level[iroot] == level[leaf]) {
                while (iroot != leaf) {
                  jedge = preved[leaf];
                  loops[loop][jedge] = incdnc[leaf][jedge];
                  leaf  = prevvx[leaf];
                  jedge = preved[iroot];
                  loops[loop][jedge] = -incdnc[iroot][jedge];
                  iroot = prevvx[iroot];
                }
                continue;

/* For level[iroot] greater than level[leaf]. */
              } else {
                jedge = preved[iroot];
                loops[loop][jedge] = -incdnc[iroot][jedge];
                iroot = prevvx[iroot];
              }
              goto _2;
            }
          }
        }
      }
    }
  }

/* If there are vertices remaining or the wrong number of loops, print
     an error message and set the error flag. */
  if (nremain > 0){
    textc("*** Error:  More than one independent assembly. ***", TRUE);
    System.nerror = 6;
  } else if ((loop + 1) != System.nloops) {
    textc("*** Error:  Incorrect number of loops found. ***", TRUE);
    System.nerror = 6;
  }
  free (preved);
  free (prevvx);
  free (level);
  free (ique);
  free (edge);
  return;
}

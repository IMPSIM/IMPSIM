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
/* loopsc-01 Jan 00:12 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find any kinematic loops from the topology of the system.
|
|     Access:
|       (void) loopsc();
|
|     Error Conditions:
|       System.nerror = 3 indicates no bodies in the system.
|       System.nerror = 4 indicates no joints in the system.
|       System.nerror = 5 indicates that the fixed body is not defined.
|
|     Comments:
|       System.level = 1 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
  void loopsc()
{
  Axes  *axes, *axs;
  Body  *bdy, *body;
  Joint *joint;
  int  **incdnc, **loops, **paths;
  int    i, j;

/* Find the fixed body and put it last in the list of bodies. */
  System.level  = 0;
  System.ground = NULL;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    if (strcmp(body->name, System.base) == 0) System.ground = body;
  }
  if (System.ground == NULL) {
    textc("*** The fixed body (named '", FALSE);
    textc(System.base, FALSE);
    textc("') is not defined. ***", TRUE);
    System.nerror = 5;
    return;
  } else {
    if (System.sysBdy == System.ground) {
      System.sysBdy = System.ground->nxtBdy;
    } else {
      bdy = System.sysBdy;
      while (bdy->nxtBdy != System.ground) bdy = bdy->nxtBdy;
      bdy->nxtBdy = System.ground->nxtBdy;
    }
    bdy = System.sysBdy;
    while (bdy->nxtBdy) bdy = bdy->nxtBdy;
    bdy->nxtBdy = System.ground;
    System.ground->nxtBdy = NULL;
  }

/* Number all bodies and joints.  Reorient all joints to their user
   specified orientations.  Reset all loopflags to zero. */
  System.nbdys = 0;
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
      axes->loopflags = 0;
    }
    body->bdyno = System.nbdys;
    body->loopflags = 0;
    ++System.nbdys;
  }
  if (System.nbdys <= 0) {
    textc("*** There are no bodies defined. ***", TRUE);
    System.nerror = 3;
    return;
  }
  System.njnts  = 0;
  System.njvars = 0;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (joint->orient < 0) {          /* Orient joints as originally. */
      axes = joint->jntAxA;
      joint->jntAxA = joint->jntAxB;
      joint->jntAxB = axes;
    }
    joint->orient    = 0;   /* Mark orientations as unknown to start. */
    joint->jntno     = System.njnts;
    joint->loopflags = 0;
    ++System.njnts;
    System.njvars   += joint->njvars;
  }
  if (System.njnts <= 0) {
    textc("*** There are no joints defined. ***", TRUE);
    System.nerror = 4;
    return;
  }
  System.nloops = max(System.njnts - System.nbdys + 1, 0);

/* Allocate space for the incdnc, loop, and path matrices. */
  incdnc = (int **) calloc(System.nbdys, sizeof (int *));
  for (i=0; i<System.nbdys; i++) {
    incdnc[i] = (int *) calloc(System.njnts, sizeof (int));
  }
  loops = (int **) calloc(System.nloops, sizeof (int *));
  for (i=0; i<System.nloops; i++) {
    loops[i] = (int *) calloc(System.njnts, sizeof (int));
  }
  paths = (int **) calloc(System.nbdys, sizeof (int *));
  for (i=0; i<System.nbdys; i++) {
    paths[i] = (int *) calloc(System.njnts, sizeof (int));
  }

/* Form the body/joint incidence matrix. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    j = joint->jntno;
    for (i=0; i<System.nbdys; i++) {
      incdnc[i][j] = 0;
    }
    incdnc[joint->jntAxB->axsBdy->bdyno][j] =-1;/* Body Before Joint. */
    incdnc[joint->jntAxA->axsBdy->bdyno][j] = 1;/* Body After  Joint. */
  }

/* Do a breadth-first tree search, creating loop and path matrices. */
  lpbfsc(System.ground->bdyno, incdnc, loops, paths);
  if (System.nerror) return;

/* Check for and correct any loop or path inconsistencies. */
  lpchkc(loops);
  if (System.nerror) return;
  pthckc(loops, paths);
  if (System.nerror) return;

/* Set all joint orientations. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    j = joint->jntno;
    if (joint->orient == 0) {
      for (i=0; i<System.nloops; i++) {
        if (loops[i][j]) {
          joint->orient = loops[i][j];
          if (loops[i][j] < 0) {
            axes = joint->jntAxA;
            joint->jntAxA = joint->jntAxB;
            joint->jntAxB = axes;
          }
          break;
        }
      }
    }
    if (joint->orient == 0) {
      for (i=0; i<System.nbdys; i++) {
        if (paths[i][j]) {
          joint->orient = paths[i][j];
          if (paths[i][j] < 0) {
            axes = joint->jntAxA;
            joint->jntAxA = joint->jntAxB;
            joint->jntAxB = axes;
          }
          break;
        }
      }
    }
    if (joint->orient == 0) joint->orient = 1;
  }

/* Put the Axes of the joint preceeding each body at the head of the
     Axes on Body list. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    axes = joint->jntAxA;    /* Axes are on the body after the joint. */
    body = axes->axsBdy;   /* Therefore, the joint preceeds the body. */
    if (paths[body->bdyno][joint->jntno]) {
      axs = body->bdyAxs;
      if (axs != axes) {
        while (axs->nxtAxs != axes) axs = axs->nxtAxs;
        axs->nxtAxs = axes->nxtAxs;
        axes->nxtAxs = body->bdyAxs;
        body->bdyAxs = axes;
      }
    }
  }
        
/* Store the loops matrix information in the loopflag fields. */
  lpfilc(loops);

/* Free the working space. */
  for (i=0; i<System.nbdys; i++) free(incdnc[i]);
  free(incdnc);
  for (i=0; i<System.nloops; i++) free(loops[i]);
  free(loops);
  for (i=0; i<System.nbdys; i++) free(paths[i]);
  free(paths);

/* Set the level to show successful completion. */
  System.level = 1;
  return;
}

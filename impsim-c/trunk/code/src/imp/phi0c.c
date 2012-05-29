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
/* phi0c-01 Jan 00:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Find the joint variable estimates at the design position.
|
|     Access:
|       (void) phi0c();
|
|     Error Conditions:
|       System.nerror = 3 indicates a critical undefined model element.
|       System.nerror = 4 indicates missing or faulty data.
|       System.nerror = 5-7 indicates faulty system topology.
|       System.nerror = 10 indicates that the system will not assemble
|     at the design position.
|       An appropriate message is printed in each case.
|
|     Comments:
|       System.level = 3 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void phi0c()
{
  Axes  *axes;
  Body  *body;
  Joint *joint;
  Jvar  *jvar;
  int    lflag;
  real   phi[6], Phi[3][4];

/* Find the kinematic loops if not known. */
  if (System.level < 1) loopsc();
  if (System.nerror) return;
  System.level = 2;

/* Count the joint variables and assign them numbers. */
  System.nc = 0;
  System.njvars = 0;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    lflag = FALSE;
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      jvar->jvrnoS = System.njvars++;
      if (isnanc((void *) &jvar->design)) lflag = TRUE;
    }

/* Count the number of Euler parameter constraint equations. */
    switch (joint->jtype) {
    case SPHERE:
    case OPEN:
      System.nc++;
      break;
    }

/* Compute the user-oriented phi matrix. */
    if (lflag || (joint->jtype == RIGID)) {
      axes = joint->jntAxB;
      body = axes->axsBdy;
      mpyxxc(body->T0j, axes->S, Phi);
      invxc(Phi, Phi);
      axes = joint->jntAxA;
      body = axes->axsBdy;
      mpyxxc(Phi, body->T0j, Phi);
      mpyxxc(Phi, axes->S,  Phi);
      if (joint->orient < 0) invxc(Phi, Phi);

/* Find and store the joint variable estimates. */
      switch (joint->jtype) {
      case RIGID:
        lflag = phrgdc(Phi);
        break;
      case XPIN:
        lflag = phxrvc(Phi, phi);
        break;
      case YPIN:
        lflag = phyrvc(Phi, phi);
        break;
      case ZPIN:
        lflag = phzrvc(Phi, phi);
        break;
      case XSLIDE:
        lflag = phxprc(Phi, phi);
        break;
      case YSLIDE:
        lflag = phyprc(Phi, phi);
        break;
      case ZSLIDE:
        lflag = phzprc(Phi, phi);
        break;
      case SCREW:
        if (isnanc((void *) &joint->param[0])) {
          textc("*** DATA SCREW ('", FALSE);
          textc(joint->name, FALSE);
          textc("') statement is missing. ***", TRUE);
          System.nerror = 4;
        } else {
          lflag = phscrc(Phi, phi);
        }
        break;
      case GEAR:
        if  (isnanc((void *) &joint->param[0])) {
          textc("*** DATA GEAR ('", FALSE);
          textc(joint->name, FALSE);
          textc("') statement is missing. ***", TRUE);
          System.nerror = 4;
        } else {
          lflag = phgerc(Phi, joint->param[0], &joint->param[1], phi);
        }
        break;
      case RACK:
        if  (isnanc((void *) &joint->param[0])) {
          textc("*** DATA RACK ('", FALSE);
          textc(joint->name, FALSE);
          textc("') statement is missing. ***", TRUE);
          System.nerror = 4;
        } else {
          lflag = phrckc(Phi, &joint->param[0], joint->param[1], phi);
        }
        break;
      case BEVEL:
        if (isnanc((void *) &joint->param[0]) ||
            isnanc((void *) &joint->param[1])) {
          textc("*** DATA BEVEL ('", FALSE);
          textc(joint->name, FALSE);
          textc("') statement is missing. ***", TRUE);
          System.nerror = 4;
        } else {
          lflag = phbvlc(Phi, joint->param[0], joint->param[1], phi);
        }
        break;
      case CYLINDER:
        lflag = phcylc(Phi, phi);
        break;
      case UJOINT:
        lflag = phujtc(Phi, phi);
        break;
      case CAM:
        lflag = phcamc(Phi, phi);
        break;
      case SLOT:
        lflag = phsltc(Phi, phi);
        break;
      case FLAT:
        lflag = phfltc(Phi, phi);
        break;
      case PLANE:
        lflag = phplnc(Phi, phi);
        break;
      case SPHERE:
        lflag = phsphc(Phi, phi);
        break;
      case OPEN:
        phopnc(Phi, phi);
        lflag = FALSE;
        break;
      }
      if (lflag) {
        textc("*** The data for joint '", FALSE);
        textc(joint->name, FALSE);
        textc("' is in error. ***", TRUE);
        System.nerror = 0;
for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
  jvar->design = phi[jvar->jvrnoJ];
}
      } else {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          jvar->design = phi[jvar->jvrnoJ];
        }
      }
    }
  }
  if (System.nerror) return;

/* Assemble the system at the design position. */
  System.nsgc  = 0;
  System.nfgc  = 0;
  System.ndof  = 0;
  System.nfree = System.njvars;
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
      jvar->pos = jvar->design;
    }
  }
  System.level = 4;
  closec();
  if (System.nerror) {
    System.level = 2;
  } else {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
        jvar->design  = jvar->pos;
        jvar->lastpos = jvar->pos;
        jvar->lastvel = 0.0;
        jvar->lastacc = 0.0;
      }
    }
    System.level = 3;
  }
  return;
}

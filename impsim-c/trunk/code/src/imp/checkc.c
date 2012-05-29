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
/* checkc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Search the IMP data structure for missing or inconsistent data
|     at the beginning of execution of a simulation.
|
|     Access:
|       (void) checkc();
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
|       If System.level >= 3 then the kinematic loops, joint variable
|     estimates, and shape matrices are assumed valid as checked by a
|     previous execution.
|       Any springs, dampers, forces, or torques existing in the data
|     structure but without valid data are deleted before execution.
|       System.level = 4 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void checkc()
{
  Body   *body;
  Damper *damper;
  Force  *force;
  Spring *spring;
  Torque *torque;

/* Check for valid loops, shape matrices, joint variable estimates. */
  if (System.level < 3) phi0c();
  if (System.nerror) return;

/* Delete any Spring records with missing data. */
  spring = System.sysSpg;
  while (spring) {
    if (isnanc((void *) &spring->k)) {
      if (spring->spgVk == NULL) {
        textc("*** The spring named '", FALSE);
        textc(spring->name, FALSE);
        textc("', having no data, is deleted. ***", TRUE);
        xspngc(spring);
        spring = System.sysSpg;
        continue;
      }
    }
    if (isnanc((void *) &spring->freel)) {
      if (spring->spgVfl == NULL) {
        textc("*** The spring named '", FALSE);
        textc(spring->name, FALSE);
        textc("', having no data, is deleted. ***", TRUE);
        xspngc(spring);
        spring = System.sysSpg;
        continue;
      }
    }
    spring = spring->nxtSpg;
  }

/* Delete any Damper records with missing data. */
  damper = System.sysDmp;
  while (damper) {
    if (isnanc((void *) &damper->c)) {
      if (damper->dmpVc == NULL) {
        textc("*** The damper named '", FALSE);
        textc(damper->name, FALSE);
        textc("', having no data, is deleted. ***", TRUE);
        xdmprc(damper);
        damper = System.sysDmp;
        continue;
      }
    }
    damper = damper->nxtDmp;
  }

/* Delete any Force records with missing data. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    force = body->bdyFrc;
    while (force) {
      if (isnanc((void *) &force->f)) {
        if (force->frcVf == NULL) {
          textc("*** The force named '", FALSE);
          textc(force->name, FALSE);
          textc("', having no data, is deleted. ***", TRUE);
          xforc(force);
          force = body->bdyFrc;
          continue;
        }
      }
      force = force->nxtFrc;
    }
  }

/* Delete any Torque records with missing data. */
  for (body=System.sysBdy; body; body=body->nxtBdy) {
    torque = body->bdyTrq;
    while (torque) {
      if (isnanc((void *) &torque->t)) {
        if (torque->trqVt == NULL) {
          textc("*** The torque named '", FALSE);
          textc(torque->name, FALSE);
          textc("', having no data, is deleted. ***", TRUE);
          xtorqc(torque);
          torque = body->bdyTrq;
          continue;
        }
      }
      torque = torque->nxtTrq;
    }
  }
  if (System.nerror == 0) System.level = 4;
  return;
}

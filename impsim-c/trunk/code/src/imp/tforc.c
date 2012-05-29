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
/* tforc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Form the generalized forces for a specified transfer function.
|
|     Access:
|       (void) tforc(Word kindin, Word namein, int nin, real G[]);
|     Word kindin,   i-String "force" or "motion" for kind of input.
|     Word namein,   i-Name of the input Force, Torque, or Joint.
|     int  nin,      i-Joint variable number within a Joint for input.
|     real G[3*nfgc],o-Generalized force components formed.
|
|     Error Conditions:
|       If no Force, Torque, or Joint record is found with the name
|     namein, a message is printed and exit is made; System.nerror = 3.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void tforc(Word kindin, Word namein, int nin, real G[])
#else
  void tforc(kindin, namein, nin, G)
  Word kindin, namein;
  int  nin;
  real G[];
#endif
{
  Body   *body;
  Force  *force;
  Joint  *joint;
  Jvar   *jvar;
  Torque *torque;
  int    i, ngc;

/* Initialize. */
  if (System.nfgc <= 0) goto _1;
  for (i=0; i<3*System.nfgc; i++) {
    G[i] = 0.0;
  }
  lcasec(kindin);
  if (strncmp(kindin, "force", MAXCHR) == 0) {
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (force=body->bdyFrc; force; force=force->nxtFrc) {
        if (strncmp(namein, force->name, MAXCHR) == 0) {
          tfptfc(force, G);
          goto _1;
        }
      }
      for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
        if (strncmp(namein, torque->name, MAXCHR) == 0) {
          tfbdtc(torque, G);
          goto _1;
        }
      }
    }
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (strncmp(namein, joint->name, MAXCHR) == 0) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr){
          if (jvar->jvrnoJ+1 == nin) {
            tfjtfc(jvar, G);
            goto _1;
          }
        }
      }
    }
  } else if (strncmp(kindin, "motion", MAXCHR) == 0) {
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
      if (strncmp(namein, joint->name, MAXCHR) == 0) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr){
          if (jvar->jvrnoJ == nin) {
            ngc = jvar->jvrnoS - System.ndep;
            if (ngc >= System.nfgc) {
              tmdync(ngc, G);
              tmjtdc(ngc, G);
              tmptdc(ngc, G);
              tmjtsc(ngc, G);
              tmptsc(ngc, G);
              tmgvtc(ngc, G);
              tmjtfc(ngc, G);
              tmptfc(ngc, G);
              tmbdtc(ngc, G);
              goto _1;
            }
          }
        }
      }
    }
  }
  textc("*** There is no force, torque, or motion input named '",FALSE);
  textc(namein, FALSE);
  textc("'. ***", TRUE);
  System.nerror = 3;
_1:
  return;
}

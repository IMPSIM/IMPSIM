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
/* stforc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Write the requested force results on the store file.
|
|     Access:
|       (void) stforc(Token name[], int n);
|     Token name[],i-Array of tokens containing item names.
|     int   n,     i-Number of entries in the name[] array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If one or more of the items is not recognized, or if proper
|     force data cannot be found, no data is output.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void stforc(Token name[], int n)
#else
  void stforc(name, n)
  Token name[];
  int   n;
#endif
{
  Body   *body, *bodyi, *bodyo;
  Damper *damper;
  Force  *force;
  Joint  *joint;
  Spring *spring;
  Torque *torque;
  Word    word;
  int     i, j, lgoto, lun, m, nn;
  real    f[6], size;

  lun = lunfil[2];
  if (lun > 0) {
    m = 0;
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) m++;
    for (spring=System.sysSpg; spring; spring=spring->nxtSpg) m++;
    for (damper=System.sysDmp; damper; damper=damper->nxtDmp) m++;
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (force=body->bdyFrc; force; force=force->nxtFrc) m++;
      for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) m++;
    }
    nn = n;
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        if (strcmp(word, "all") == 0) nn += m - 1;
      } else {
        nn--;
      }
    }
    fprintf(streams[lun]," FORC ---- %#4i %#19.10e %#19.10e %#19.10e\n",
      nn, 0.0, 0.0, 0.0);

/* Sequence through the list of requested names. */
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        lgoto = (strcmp(word, "all") == 0);

/* Output the force in a named joint. */
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          if (lgoto) {
            jtforc(joint, f);
          } else if (strcmp(joint->name, name[i].data.text) == 0) {
            jtforc(joint, f);
          } else {
            continue;
          }
          if (System.nerror) {
            System.nerror = 0;
            if (lgoto) continue;
            break;
          }
          if (joint->orient < 0) {
            bodyi = joint->jntAxA->axsBdy;
            bodyo = joint->jntAxB->axsBdy;
          } else {
            bodyi = joint->jntAxB->axsBdy;
            bodyo = joint->jntAxA->axsBdy;
          }
          for (j=0; j<6; j++) {
            if (isnanc((void *) &System.pd[0][j])) {
              f[j] = UNDET;
            } else if (isnanc((void *) &f[j])) {
              f[j] = UNDET;
            }
          }
          fprintf(streams[lun],
            " JNT. %#4s    3 %#19.10e %#19.10e %#19.10e\n",
            joint->name, f[0], f[1], f[2]);
          fprintf(streams[lun],
            " %#4s %#4s    3 %#19.10e %#19.10e %#19.10e\n",
            bodyi->name, bodyo->name, f[3], f[4], f[5]);
          if (!lgoto) break;
        }
        if (joint) continue;

/* Output the force in a named spring. */
        for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
          if (lgoto) {
            size = sgforc(spring);
          } else if (strcmp(spring->name, name[i].data.text) == 0) {
            size = sgforc(spring);
          } else {
            continue;
          }
          if (isnanc((void *) &size)) size = UNDET;
          fprintf(streams[lun],
            " SPG. %#4s    1 %#19.10e %#19.10e %#19.10e\n",
            spring->name, size, 0.0, 0.0);
          if (!lgoto) break;
        }
        if (spring) continue;

/* Output the force in a named damper. */
        for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
          if (lgoto) {
            size = dmforc(damper);
          } else if (strcmp(damper->name, name[i].data.text) == 0) {
            size = dmforc(damper);
          } else {
            continue;
          }
          if (isnanc((void *) &size)) size = UNDET;
          fprintf(streams[lun],
            " DMP. %#4s    1 %#19.10e %#19.10e %#19.10e\n",
            damper->name, size, 0.0, 0.0);
          if (!lgoto) break;
        }
        if (damper) continue;

/* Output the size of a named force. */
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (force=body->bdyFrc; force; force=force->nxtFrc) {
            if (lgoto) {
              size = force->f;
            } else if (strcmp(force->name, name[i].data.text) == 0) {
              size = force->f;
            } else {
              continue;
            }
            if (isnanc((void *) &size)) size = UNDET;
            fprintf(streams[lun],
              " FORC %#4s    1 %#19.10e %#19.10e %#19.10e\n",
              force->name, size, 0.0, 0.0);
            if (!lgoto) break;
          }
          if (force && !lgoto) break;
        }
        if (force) continue;

/* Output the size of a named torque. */
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
            if (lgoto) {
              size = torque->t;
            } else if (strcmp(torque->name, name[i].data.text) == 0) {
              size = torque->t;
            } else {
              continue;
            }
            if (isnanc((void *) &size)) size = UNDET;
            fprintf(streams[lun],
              " TORQ %#4s    1 %#19.10e %#19.10e %#19.10e\n",
              torque->name, size, 0.0, 0.0);
            if (!lgoto) break;
          }
          if (torque && !lgoto) break;
        }
        if (torque) continue;
      }
    }
  }
  return;
}

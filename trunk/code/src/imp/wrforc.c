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
/* wrforc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Print the requested force results on the output file.
|
|     Access:
|       (void) wrforc(Token name[], int n);
|     Token name[],i-Array of tokens containing item names.
|     int   n,     i-Number of entries in the name[] array.
|
|     Error Conditions:
|       If one or more of the items is not recognized, or if proper
|     force data cannot be found, a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 May 00:JJU-Changed formats for overflow size values.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void wrforc(Token name[], int n)
#else
  void wrforc(name, n)
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
  Word    nameword, word;
  char    string[16];
  int     i, j, k, lgoto, m;
  real    f[6], size;

/* Print the headings. */
  textc("", TRUE);
  textc("Force Results:", TRUE);
  textc("                  Magnitude          X              Y", FALSE);
  textc("              Z", TRUE);

/* Sequence through the list of requested names. */
  for (i=0; i<n; i++) {
    if (name[i].kind == TK_CHAR) {
      strcpy(word, name[i].data.text);
      lcasec(word);
      lgoto = (strcmp(word, "all") == 0);

/* Print the force in a named joint. */
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
        textc("", TRUE);
        textc("  through Joint ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, joint->name);
        textc(nameword, FALSE);
        textc(" from Body ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, bodyi->name);
        textc(nameword, FALSE);
        textc(" onto Body ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, bodyo->name);
        textc(nameword, FALSE);
        textc(":", TRUE);
        for (k=0; k<2; k++) {
          size = 0.0;
          for (j=0; j<3; j++) {
            m = 3 * k + j;
            if (isnanc((void *) &System.pd[0][m])) {
            } else if (isnanc((void *) &f[m])) {
            } else {
              size += f[m] * f[m];
            }
          }
          size = sqrt(size);
          textc("        ", FALSE);
          switch (k) {
          case 0:
            textc("Forc", FALSE);
            break;
          case 1:
            textc("Torq", FALSE);
          }
          if (sprintf(string, "%#15.3f", size) <= 15) {
            textc(string, FALSE);
          } else {
            textc(" **************", FALSE);
          }
          for (j=0; j<3; j++) {
            m = 3 * k + j;
            if (isnanc((void *) &System.pd[0][m])) {
              textc("           ????", FALSE);
            } else if (isnanc((void *) &f[m])) {
              textc("           ????", FALSE);
            } else {
              if (sprintf(string, "%#15.3f", f[m]) <= 15) {
                textc(string, FALSE);
              } else {
                textc(" **************", FALSE);
              }
            }
          }
          textc("", TRUE);
        }
        if (!lgoto) break;
      }
      if (joint) continue;

/* Print the force in a named spring. */
      for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
        if (lgoto) {
          size =sgforc(spring);
        } else if (strcmp(spring->name, name[i].data.text) == 0) {
          size = sgforc(spring);
        } else {
          continue;
        }
        textc("", TRUE);
        textc("  Spg.  ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, spring->name);
        textc(nameword, FALSE);
        if (isnanc((void *) &size)) {
          textc("           ????", TRUE);
        } else {
          if (sprintf(string, "%#15.3f", size) <= 15) {
            textc(string, TRUE);
          } else {
            textc(" **************", TRUE);
          }
        }
        if (!lgoto) break;
      }
      if (spring) continue;

/* Print the force in a named damper. */
      for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
        if (lgoto) {
          size = dmforc(damper);
        } else if (strcmp(damper->name, name[i].data.text) == 0) {
          size = dmforc(damper);
        } else {
          continue;
        }
        textc("", TRUE);
        textc("  Dmp.  ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, damper->name);
        textc(nameword, FALSE);
        if (isnanc((void *) &size)) {
          textc("           ????", TRUE);
        } else {
          if (sprintf(string, "%#15.3f", size) <= 15) {
            textc(string, TRUE);
          } else {
            textc(" **************", TRUE);
          }
        }
        if (!lgoto) break;
      }
      if (damper) continue;

/* Print the size of a named force. */
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (force=body->bdyFrc; force; force=force->nxtFrc) {
          if (lgoto) {
            size = force->f;
          } else if (strcmp(force->name, name[i].data.text) == 0) {
            size = force->f;
          } else {
            continue;
          }
          textc("", TRUE);
          textc("  Forc  ", FALSE);
          sprintf(nameword, "%-*s\0", MAXCHR, force->name);
          textc(nameword, FALSE);
          if (isnanc((void *) &size)) {
            textc("           ????", TRUE);
          } else {
            if (sprintf(string, "%#15.3f", size) <= 15) {
              textc(string, TRUE);
            } else {
              textc(" **************", TRUE);
            }
          }
          if (!lgoto) break;
        }
      }
      if (force) continue;

/* Print the size of a named torque. */
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
          if (lgoto) {
            size = torque->t;
          } else if (strcmp(torque->name, name[i].data.text) == 0) {
            size = torque->t;
          } else {
            continue;
          }
          textc("", TRUE);
          textc("  Torq  ", FALSE);
          sprintf(nameword, "%-*s\0", MAXCHR, torque->name);
          textc(nameword, FALSE);
          if (isnanc((void *) &size)) {
            textc("           ????", TRUE);
          } else {
            if (sprintf(string, "%#15.3f", size) <= 15) {
              textc(string, TRUE);
            } else {
              textc(" **************", TRUE);
            }
          }
          if (!lgoto) break;
        }
      }
      if (lgoto || (torque != NULL)) continue;
      textc("*** Force in unknown '", FALSE);
      textc(name[i].data.text, FALSE);
      textc("' is not defined. ***", TRUE);
    }
  }
  return;
}

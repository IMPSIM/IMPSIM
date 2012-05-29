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
/* wracc-01 Jan 00:17 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Print the requested acceleration results on the output file.
|
|     Access:
|       (void) wracc(Token name[], int n);
|     Token name[],i-Array of tokens containing item names.
|     int   n,     i-Number of entries in the name[] array.
|
|     Error Conditions:
|       If one or more of the items is not recognized, or if proper
|     acceleration data cannot be found, a message is printed.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 May 00:JJU-Changed formats for overflow size values.
*     17 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void wracc(Token name[], int n)
#else
  void wracc(name, n)
  Token name[];
  int   n;
#endif
{
  Body   *body;
  Damper *damper;
  Joint  *joint;
  Point  *point;
  Spring *spring;
  Word    nameword, word;
  char    string[16];
  int     i, j, lgoto, m;
  real    acc[7], r[3], v[3];

/* Print the headings. */
  textc("", TRUE);
  textc("Acceleration Results:", TRUE);
  textc("  Item  Name      Magnitude          X              Y", FALSE);
  textc("              Z", TRUE);

/* Sequence through the list of requested names. */
  for (i=0; i<n; i++) {
    if (name[i].kind == TK_CHAR) {
      strcpy(word, name[i].data.text);
      lcasec(word);
      lgoto = (strcmp(word, "all") == 0);

/* Print the acceleration of a joint. */
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        if (lgoto) {
          jtacc(joint, acc, &m);
        } else if (strcmp(joint->name, name[i].data.text) == 0) {
          jtacc(joint, acc, &m);
        } else {
          continue;
        }
        for (j=0; j<3; j++) r[j] = 0.0;
        mpyxrc(joint->jntAxB->S, r, r);
        body = joint->jntAxB->axsBdy;
        mpyxrc(body->T0j, r, r);
        mpydrc(body->W, r, v);
        vcrosc(body->W, v, v);
        mpydrc(body->A, r, r);
        for (j=0; j<3; j++) {
          v[j] += r[j];
        }
        textc("", TRUE);
        textc("  Joint ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, joint->name);
        textc(nameword, FALSE);
        if (m > 0) {
          if (isnanc((void *) &acc[0])) {
            textc("           ????", FALSE);
          } else {
            if (sprintf(string, "%#15.3f", acc[0]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
        } else {
          textc("               ", FALSE);
        }
        for (j=0; j<3; j++) {
          if (isnanc((void *) &v[j])) {
            textc("           ????", FALSE);
          } else {
            if (sprintf(string, "%#15.3f", v[j]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
        }
        textc("", TRUE);
        for (j=1; j<m; j++) {
          if (isnanc((void *) &acc[j])) {
            textc("           ????", FALSE);
          } else {
            if (sprintf(string, "%#15.3f", acc[j]) <= 15) {
              textc(string, TRUE);
            } else {
              textc(" **************", TRUE);
            }
          }
        }
        if (!lgoto) break;
      }
      if (joint) continue;

/* Print the acceleration of a point. */
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (point=body->bdyPnt; point; point=point->nxtPnt) {
          if (point->master) {
            if (lgoto) {
              ptacc(point, r, v, &acc[1]);
            } else if (strcmp(point->name, name[i].data.text) == 0) {
              ptacc(point, r, v, &acc[1]);
            } else {
              continue;
            }
            acc[0] = vabsc(3, &acc[1]);
            textc("", TRUE);
            textc("  Point ", FALSE);
            sprintf(nameword, "%-*s\0", MAXCHR, point->name);
            textc(nameword, FALSE);
            for (j=0; j<4; j++) {
              if (isnanc((void *) &acc[j])) {
                textc("           ????", FALSE);
              } else {
                if (sprintf(string, "%#15.3f", acc[j]) <= 15) {
                  textc(string, FALSE);
                } else {
                  textc(" **************", FALSE);
                }
              }
            }
            textc("", TRUE);
            if (!lgoto) break;
          }
        }
        if (point) break;
      }
      if (body) continue;

/* Print the acceleration of a spring. */
      for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
        if (lgoto) {
          sgacc(spring, &acc[1]);
        } else if (strcmp(spring->name, name[i].data.text) == 0) {
          sgacc(spring, &acc[1]);
        } else {
          continue;
        }
        acc[0] = vabsc(3, &acc[1]);
        textc("", TRUE);
        textc("  Spg.  ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, spring->name);
        textc(nameword, FALSE);
        for (j=0; j<4; j++) {
          if (isnanc((void *) &acc[j])) {
            textc("           ????", FALSE);
          } else {
            if (sprintf(string, "%#15.3f", acc[j]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
        }
        textc("", TRUE);
        if (!lgoto) break;
      }
      if (spring) continue;

/* Print the acceleration of a damper. */
      for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
        if (lgoto) {
          dmacc(damper, &acc[1]);
        } else if (strcmp(damper->name, name[i].data.text) == 0) {
          dmacc(damper, &acc[1]);
        } else {
          continue;
        }
        acc[0] = vabsc(3, &acc[1]);
        textc("", TRUE);
        textc("  Dmp.  ", FALSE);
        sprintf(nameword, "%-*s\0", MAXCHR, damper->name);
        textc(nameword, FALSE);
        for (j=0; j<4; j++) {
          if (isnanc((void *) &acc[j])) {
            textc("           ????", FALSE);
          } else {
            if (sprintf(string, "%#15.3f", acc[j]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
        }
        textc("", TRUE);
        if (!lgoto) break;
      }
      if (damper) continue;

/* Print the acceleration of a body. */
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        if (strcmp(body->name, name[i].data.text) == 0) {
          textc("", TRUE);
          textc("  Body  ", FALSE);
          sprintf(nameword, "%-*s\0", MAXCHR, body->name);
          textc(nameword, FALSE);
          if (sprintf(string, "%#15.4f", vabsc(3, body->A)) <= 15) {
            textc(string, FALSE);
          } else {
            textc(" **************", FALSE);
          }
          for (j=0; j<3; j++) {
            if (sprintf(string, "%#15.3f", body->A[j]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
          textc("", TRUE);
          textc("            ", FALSE);
          if (sprintf(string, "%#15.3f", vabsc(3, &body->A[3])) <= 15) {
            textc(string, FALSE);
          } else {
            textc(" **************", FALSE);
          }
          for (j=3; j<6; j++) {
            if (sprintf(string, "%#15.3f", body->A[j]) <= 15) {
              textc(string, FALSE);
            } else {
              textc(" **************", FALSE);
            }
          }
          textc("", TRUE);
          break;
        } else {
          continue;
        }
      }
      if (lgoto || (body != NULL)) continue;
      textc("*** Acceleration of '", FALSE);
      textc(name[i].data.text, FALSE);
      textc("' is not defined. ***", TRUE);
    }
  }
  return;
}

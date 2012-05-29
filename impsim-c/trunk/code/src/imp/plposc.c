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
/* plposc-01 Jan 00:17 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Write the requested position results on the plot file.
|
|     Access:
|       (void) plposc(Token name[], int n);
|     Token name[],i-Array of tokens containing item names.
|     int   n,     i-Number of entries in the name[] array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       If one or more of the items is not recognized, or if proper 
|     posiition data cannot be found, no data is output.
*
*     History:
*     01 Jan 00:JJU-Original.
*     12 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void plposc(Token name[], int n)
#else
  void plposc(name, n)
  Token name[];
  int   n;
#endif
{
  Body   *body;
  Damper *damper;
  Joint  *joint;
  Point  *point;
  Spring *spring;
  Word    word;
  int     i, j, lgoto, lun, m, nn;
  real    pos[9];

  lun = lunfil[1];
  if (lun > 0) {
    m = 0;
    for (joint=System.sysJnt; joint; joint=joint->nxtJnt) m++;
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (point=body->bdyPnt; point; point=point->nxtPnt) {
        if (point->master) m++;
      }
    }
    for (spring=System.sysSpg; spring; spring=spring->nxtSpg) m++;
    for (damper=System.sysDmp; damper; damper=damper->nxtDmp) m++;
    nn = n;
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        if (strcmp(word, "all") == 0) nn += m - 1;
      }
    }
    fprintf(streams[lun]," POS. ---- %#4i %#19.10e %#19.10e %#19.10e\n",
      nn, 0.0, 0.0, 0.0);

/* Sequence through the list of requested names. */
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        lgoto = (strcmp(word, "all") == 0);

/* Output the position of a joint. */
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          if (lgoto) {
            jtposc(joint, pos, &m);
          } else if (strcmp(joint->name, name[i].data.text) == 0) {
            jtposc(joint, pos, &m);
          } else {
            continue;
          }
          for (j=0; j<m; j++) {
            if (isnanc((void *) &pos[j])) pos[j] = UNDET;
          }
          for (j=m; j<9; j++) pos[j] = 0.0;
          fprintf(streams[lun],
            " JNT. %#4s %#4i %#19.10e %#19.10e %#19.10e\n",
            joint->name, m, pos[0], pos[1], pos[2]);
          if (m > 3) {
            fprintf(streams[lun],
              " ---- ---- %#4i %#19.10e %#19.10e %#19.10e\n",
              m, pos[3], pos[4], pos[5]);
          }
          if (m > 6) {
            fprintf(streams[lun],
              " ---- ---- %#4i %#19.10e %#19.10e %#19.10e\n",
              m, pos[6], pos[7], pos[8]);
          }
          if (!lgoto) break;
        }
        if (joint) continue;

/* Output the position of a point. */
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (point=body->bdyPnt; point; point=point->nxtPnt) {
            if (point->master) {
              if (lgoto) {
                ptposc(point, pos);
              } else if (strcmp(point->name, name[i].data.text) == 0) {
                ptposc(point, pos);
              } else {
                continue;
              }
              for (j=0; j<3; j++) {
                if (isnanc((void *) &pos[j])) pos[j] = UNDET;
              }
              fprintf(streams[lun],
                " PNT. %#4s    3 %#19.10e %#19.10e %#19.10e\n",
                point->name, pos[0], pos[1], pos[2]);
              if (!lgoto) break;
            }
          }
          if (point) break;
        }
        if (body) continue;

/* Output the position of a spring. */
        for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
          if (lgoto) {
            sgposc(spring, pos);
          } else if (strcmp(spring->name, name[i].data.text) == 0) {
            sgposc(spring, pos);
          } else {
            continue;
          }
          for (j=0; j<3; j++) {
            if (isnanc((void *) &pos[j])) pos[j] = UNDET;
          }
          fprintf(streams[lun],
            " SPG. %#4s    3 %#19.10e %#19.10e %#19.10e\n",
            spring->name, pos[0], pos[1], pos[2]);
          if (!lgoto) break;
        }
        if (spring) continue;

/* Output the position of a damper. */
        for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
          if (lgoto) {
            dmposc(damper, pos);
          } else if (strcmp(damper->name, name[i].data.text) == 0) {
            dmposc(damper, pos);
          } else {
            continue;
          }
          for (j=0; j<3; j++) {
            if (isnanc((void *) &pos[j])) pos[j] = UNDET;
          }
          fprintf(streams[lun],
            " DMP. %#4s    3 %#19.10e %#19.10e %#19.10e\n",
            damper->name, pos[0], pos[1], pos[2]);
          if (!lgoto) break;
        }
        if (damper) continue;

/* Output the position of a body. */
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          if (strcmp(body->name, name[i].data.text) == 0) {
            fprintf(streams[lun],
              " BODY %#4s   12 %#19.10e %#19.10e %#19.10e\n",body->name,
              body->T0j[0][0], body->T0j[1][0], body->T0j[2][0]);
            for (j=1; j<4; j++) {
              fprintf(streams[lun],
                " ---- ----   12 %#19.10e %#19.10e %#19.10e\n",
                body->T0j[0][j], body->T0j[1][j], body->T0j[2][j]);
            }
            break;
          }
        }
      }
    }
  }
  return;
}

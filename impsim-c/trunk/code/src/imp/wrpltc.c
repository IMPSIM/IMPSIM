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
/* wrpltc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Plot the requested information on the output file.
|
|     Access:
|       (void) wrpltc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void wrpltc()
{
  enum Rectyp kind, ngoto;
  Body    *body;
  Damper  *damper;
  Force   *force;
  Joint   *joint;
  Point   *point;
  Request *request;
  Spring  *spring;
  Torque  *torque;
  Value   *value;
  Word     name, word;
  char     chdvc[8], dsplay[8], locdvc[8], number[3];
  int      i, j, k, lall, last, lgoto, mxdata, nchrs, nn;
  real    *data, schrsz, *t, tchrsz, xmax, xmin, y, ymax, ymin, zmax,
    zmin;

/* Initialize. */
  if (qkbic()) return;
  qdvc(dsplay, chdvc, locdvc);
  if (strncmp(dsplay, "graphic", MAXCHR) != 0) return;
  qchszc(&schrsz, &tchrsz);
  framgc(8.0*schrsz, 4.5*tchrsz, 1.0-4.0*schrsz, 1.0-3.0*tchrsz);
  nn = nint(System.tfinal / System.dtio) + 2;
  t    = (real *) calloc(   nn, sizeof(real));
  data = (real *) calloc(12*nn, sizeof(real));

/* Sequence through all output requests. */
  for (request=System.sysReq; request; request=request->nxtReq) {
    if (request->reqtyp != RQ_PLOT) continue;
    if (request->outtyp == OT_HDNG) continue;
    if (request->outtyp == OT_DYN)  continue;
    for (i=0; i<request->nitems; i++) {
      if (request->items[i].kind == TK_CHAR) {
        strcpy(name, request->items[i].data.text);
        ngoto = SYSTEM;
        strcpy(word, name);
        lcasec(word);
        lall = (strncmp(word, "all", MAXCHR) == 0);
        if (request->outtyp == OT_VAL) {
          for (value=System.sysVal; value; value=value->nxtVal) {
            if (strncmp(value->name, "", MAXCHR) == 0) continue;
            if (value->f == F_CONST) continue;
            if (value->f == F_TIME)  continue;
            if (lall) {
              strcpy(name, value->name);
              ngoto = VALUE;
              goto _DATA;
_VALUE:       continue;
            } else if (strncmp(name, value->name, MAXCHR) == 0) {
              goto _DATA;
            }
          }
          continue;
        }
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          if (lall) {
            strcpy(name, joint->name);
            ngoto = JOINT;
            goto _DATA;
_JOINT:     continue;
          } else if (strncmp(name, joint->name, MAXCHR) == 0) {
            goto _DATA;
          }
        }
        if (request->outtyp != OT_FORC) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            if (strncmp(name, body->name, MAXCHR) == 0) goto _DATA;
          }
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (point=body->bdyPnt; point; point=point->nxtPnt) {
              if (point->master) {
                if (lall) {
                  strcpy(name, point->name);
                  ngoto = POINT;
                  goto _DATA;
_POINT:           continue;
                } else if (strncmp(name, point->name, MAXCHR) == 0) {
                  goto _DATA;
                }
              }
            }
          }
        }
        for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
          if (lall) {
            strcpy(name, spring->name);
            ngoto = SPRING;
            goto _DATA;
_SPRING:    continue;
          } else if (strncmp(name, spring->name, MAXCHR) == 0) {
            goto _DATA;
          }
        }
        for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
          if (lall) {
            strcpy(name, damper->name);
            ngoto = DAMPER;
            goto _DATA;
_DAMPER:    continue;
          } else if (strncmp(name, damper->name, MAXCHR) == 0) {
            goto _DATA;
          }
        }
        if (request->outtyp == OT_FORC) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (force=body->bdyFrc; force; force=force->nxtFrc) {
              if (lall) {
                strcpy(name, force->name);
                ngoto = FORCE;
                goto _DATA;
_FORCE:         continue;
              } else if (strncmp(name, force->name, MAXCHR) == 0) {
                goto _DATA;
              }
            }
          }
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
              if (lall) {
                strcpy(name, torque->name);
                ngoto = TORQUE;
                goto _DATA;
_TORQUE:        continue;
              } else if (strncmp(name, torque->name, MAXCHR) == 0) {
                goto _DATA;
              }
            }
          }
        }
        goto _AGAIN;

/* Recover the data from the Plot file. */
_DATA:  kind = 0;
        rdfilc(lunfil[1], request->outtyp, name, &last, t, &kind,
          &mxdata, data);
        if (last <= 0) goto _AGAIN;
if (request->outtyp == OT_VAL) mxdata = 1;

/* Scale the data and draw the grid. */
        amnmxc(t, last, 1, &xmin, &xmax);
        ymin = data[0];
        ymax = ymin;
        for (k=0; k<mxdata; k++) {
          amnmxc(&data[k], last, 12, &zmin, &zmax);
          ymin = min(ymin, zmin);
          ymax = max(ymax, zmax);
        }
        newpgc();
        colrfc(kfrgnd);
        colrsc(kfrgnd);
        dashc(23);
        gridc(0, xmin, ymin, xmax, ymax);
        dashc(0);

/* Draw the graph. */
        for (k=0; k<mxdata; k++) {
          if (mxdata <= 6) {
            colrfc(2 + nint(2.333 * k));
          } else {
            colrfc(2 + k);
          } 
          lgoto = TRUE;
          for (j=0; j<last; j++) {
            y = data[12*j+k];
            if (lgoto || (fabs(y - UNDET) < 0.00000001)) {
              lgoto = (fabs(y - UNDET) < 0.00000001);
              if (lgoto) continue;
              movagc(t[j], y);
            } else {
              drwagc(t[j], y);
            }
            if (mxdata > 1) {
              if ((j % 8) == k) {
                sprintf(number, "%1i", k+1);
                htextc(number);
                movagc(t[j], y);
              }
            }
          }
        }
        colrfc(kfrgnd);

/* Print the title for this plot. */
        movasc(0.5 - 16.0 * schrsz, 1.5 * tchrsz);
        switch (request->outtyp) {
        case OT_VAL:
          htextc("Value of ");
          break;
        case OT_POS:
          htextc("Position of ");
          break;
        case OT_VEL:
          htextc("Velocity of ");
          break;
        case OT_ACC:
          htextc("Acceleration of ");
          break;
        case OT_FORC:
          htextc("Force in ");
        }
        switch (kind) {
        case BODY:
          htextc("body ");
          break;
        case JOINT:
          htextc("joint ");
          break;
        case POINT:
          htextc("point ");
          break;
        case SPRING:
          htextc("spring ");
          break;
        case DAMPER:
          htextc("damper ");
          break;
        case FORCE:
          htextc("force ");
          break;
        case TORQUE:
          htextc("torque ");
        }
        htextc(name);
        htextc(" vs. time");
        nchrs = lenc(System.title);
        if (nchrs > 0) {
          movasc(0.5 * (1.0 - nchrs * schrsz), 0.5 * tchrsz);
          htextc(System.title);
        }
        clrplc();
        if (qbitc(XQ_PAUSE, (void *) &System.xeqflags)) waitc();
        switch (ngoto) {
        case SYSTEM:
          goto _AGAIN;
        case VALUE:
          goto _VALUE;
        case JOINT:
          goto _JOINT;
        case POINT:
          goto _POINT;
        case SPRING:
          goto _SPRING;
        case DAMPER:
          goto _DAMPER;
        case FORCE:
          goto _FORCE;
        case TORQUE:
          goto _TORQUE;
        }
      }
_AGAIN:
      if (qkbic()) break;
    }
  }
  free (t);
  free (data);
  return;
}

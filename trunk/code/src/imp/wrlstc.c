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
/* wrlstc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       List the requested information on the output file.
|
|     Access:
|       (void) wrlstc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     10 May 00:JJU-Changed format for overflow value sizes.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void wrlstc()
{
  enum Rectyp kind, ngoto;
  Body    *body;
  Damper  *damper;
  Force   *force;
  Joint   *joint;
  Jvar    *jvar;
  Point   *point;
  Request *request;
  Spring  *spring;
  Torque  *torque;
  Value   *value;
  Word     name, word;
  char     string[12];
  int      i, j, k, lall, last, mxdata, nn;
  real    *data, *t;

/* Initialize. */
  if (qkbic()) return;
  nn = nint(System.tfinal / System.dtio) + 2;
  t    = (real *) calloc(     nn, sizeof(real));
  data = (real *) calloc(12 * nn, sizeof(real));

/* Sequence through all output requests. */
  for (request=System.sysReq; request; request=request->nxtReq) {
    if (request->reqtyp != RQ_LIST) continue;
    if (request->outtyp == OT_HDNG) continue;
    if (request->outtyp == OT_DYN) continue;
    for (i=0; i<request->nitems; i++) {
      if (request->items[i].kind == TK_CHAR) {
        strcpy(name, request->items[i].data.text);
        ngoto = SYSTEM;
        strcpy(word, name);
        lcasec(word);
        lall = (strcmp(word, "all") == 0);
        if (request->outtyp == OT_VAL) {
          for (value=System.sysVal; value; value=value->nxtVal) {
            if (strcmp(value->name, "") == 0) continue;
            if (value->f == F_CONST) continue;
            if (value->f == F_TIME)  continue;
            if (lall) {
              strcpy(name, value->name);
              ngoto = VALUE;
              goto _DATA;
_VALUE:       continue;
            } else if (strcmp(name, value->name) == 0) {
              goto _DATA;
            }
          }
        }
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          if (lall) {
            strcpy(name, joint->name);
            ngoto = JOINT;
            goto _DATA;
_JOINT:     continue;
          } else if (strcmp(name, joint->name) == 0) {
            goto _DATA;
          }
        }
        if (request->outtyp != OT_FORC) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            if (strcmp(name, body->name) == 0) goto _DATA;
          }
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (point=body->bdyPnt; point; point=point->nxtPnt) {
              if (point->master) {
                if (lall) {
                  strcpy(name, point->name);
                  ngoto = POINT;
                  goto _DATA;
_POINT:           continue;
                } else if (strcmp(name, point->name) == 0) {
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
          } else if (strcmp(name, spring->name) == 0) {
            goto _DATA;
          }
        }
        for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
          if (lall) {
            strcpy(name, damper->name);
            ngoto = DAMPER;
            goto _DATA;
_DAMPER:    continue;
          } else if (strcmp(name, damper->name) == 0) {
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
              } else if (strcmp(name, force->name) == 0) {
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
              } else if (strcmp(name, torque->name) == 0) {
                goto _DATA;
              }
            }
          }
        }
        goto _AGAIN;

/* Recover the data from the List file. */
_DATA:  kind = 0;
        rdfilc(lunfil[0], request->outtyp, name, &last, t, &kind,
          &mxdata, data);
        if (last <= 0) goto _AGAIN;

/* Print the page heading for this item. */
        newpgc();
        switch (request->outtyp) {
        case OT_VAL:
          if (kind == VALUE) {
            textc("", TRUE);
            textc("Listing of Value of ", FALSE);
            textc(name, TRUE);
            textc("  Time         Value  1st Deriv  2nd Deriv", TRUE);
          }
          break;
        case OT_POS:
        case OT_VEL:
        case OT_ACC:
          textc("", TRUE);
          textc("Listing of ", FALSE);
          switch (request->outtyp) {
          case OT_POS:
            textc("position", FALSE);
            break;
          case OT_VEL:
            textc("velocity", FALSE);
            break;
          case OT_ACC:
            textc("acceleration", FALSE);
          }
          switch (kind) {
          case JOINT:
            textc(" of joint ", FALSE);
            textc(name, TRUE);
            textc("  Time", FALSE);
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              textc("     JVar ", FALSE);
              itextc(jvar->jvrnoJ+1);
            }
            textc("", TRUE);
            break;
          case BODY:
            textc(" of body ", FALSE);
            textc(name, TRUE);
            switch (request->outtyp) {
            case OT_POS:
              textc("  Time         IX         IY         IZ",FALSE);
              textc("         JX         JY         JZ", TRUE);
              textc("               KX         KY         KZ",FALSE);
              textc("         X          Y          Z", TRUE);
              break;
            case OT_VEL:
              textc("  Time        OmegaX     OmegaY     OmegaZ",FALSE);
              textc("         VX         VY         VZ", TRUE);
              break;
            case OT_ACC:
              textc("  Time        AlphaX     AlphaY     AlphaZ",FALSE);
              textc("         AX         AY         AZ", TRUE);
            }
            break;
          case POINT:
          case SPRING:
          case DAMPER:
            textc(" of ", FALSE);
            switch (kind) {
            case POINT:
              textc("point ", FALSE);
              break;
            case SPRING:
              textc("spring ", FALSE);
              break;
            case DAMPER:
              textc("damper ", FALSE);
            }
            textc(name, TRUE);
            textc("  Time         X          Y          Z", TRUE);
          }
          break;
        case OT_FORC:
          textc("", TRUE);
          textc("Listing of force in ", FALSE);
          switch (kind) {
          case JOINT:
            textc("joint ", FALSE);
            textc(name, TRUE);
            textc("  Time         FX         FY         FZ", FALSE);
            textc("         MX         MY         MZ", TRUE);
            break;
          case SPRING:
            textc("spring ", FALSE);
            textc(name, TRUE);
            textc("  Time         FX         FY         FZ", TRUE);
            break;
          case DAMPER:
            textc("damper ", FALSE);
            textc(name, TRUE);
            textc("  Time         FX         FY         FZ", TRUE);
            break;
          default:
            textc(name, TRUE);
            textc("  Time         F", TRUE);
          }
        }

/* Print listings of the data. */
        for (j=0; j<last; j++) {
          if ((j > 0) && ((j % 5) == 0)) textc("", TRUE);
          sprintf(string, "%#9.6f", t[j]);
          textc(string, FALSE);
          for (k=0; k<mxdata; k++) {
            if (fabs(data[12*j+k] - UNDET) < 0.00000001) {
              textc("       ????", FALSE);
            } else {
              if (sprintf(string, "%#11.4f", data[12*j+k]) <= 11) {
                textc(string, FALSE);
              } else {
                textc(" **********", FALSE);
              }
            }
            if (mxdata > 6) {
              if (k == 5) {
                textc("", TRUE);
                textc("      ", FALSE);
              }
            }
          }
          textc("", TRUE);
        }
        if (qbitc(XQ_PAUSE, (void *) &System.xeqflags)) waitc();

/* Continue with the next item or the next request as appropriate. */
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

/* Free workspace. */
  free (t);
  free (data);
  return;
}

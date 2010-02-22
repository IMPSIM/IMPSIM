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
/* identc-01 Jan 00:16 Aug 09
|     (C)Copyright, JJU Research, 2000-2009
|
|     Description:
|       List the names of all items of specified types in the current
|     System model.
|
|     Access:
|       (void) identc(kinds[], nkinds);
|     Token kinds[],i-Array of input tokens telling types of items to be
|       listed.
|     int nkinds,i-Number of tokens in the kinds[] array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The kinds[] array of Tokens should each be of kind TK_CHAR and
|     each should contain a keyword telling the type of items to be
|     listed.  All items of the specified type are listed.
|       An unrecognized type keyword is ignored; a message is printed.
|       The keyword "all" requests that all items of all types be
|     listed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void identc(Token kinds[], int nkinds)
#else
  void identc(kinds, nkinds)
  Token kinds[];
  int   nkinds;
#endif
{
  Axes    *axes;
  Body    *body;
  Contact *cntact;
  Damper  *damper;
  Force   *force;
  Joint   *joint;
  Jvar    *jvar;
  Point   *point;
  Solid   *solid;
  Spring  *spring;
  Torque  *torque;
  Value   *value;
  Word    kind;
  char    spaces[9] = "        ";
  int     all, i, next;
  long    marks;

/* Loop through the kinds of items requested. */
  echoc();
  for (i=0; i<nkinds; i++) {
    if (kinds[i].kind == TK_CHAR) {
      lcasec(kinds[i].data.text);
      all = strncmp(kinds[i].data.text, "all", MAXCHR) == 0;
      if (all) {
        strncpy(kind, "values", MAXCHR);
      } else {
        strncpy(kind, kinds[i].data.text, MAXCHR);
      }
      kind[MAXCHR] = '\0';

/* List all Value names. */
_2:   if (strncmp(kind, "values", MAXCHR) == 0) {
        textc("The value names are:", TRUE);
        for (value=System.sysVal; value; value=value->nxtVal) {
          if (lenc(value->name) > 0) {
            textc("  value ", FALSE);
            textc(value->name, TRUE);
          }
        }
        if (all) {
          strncpy(kind, "bodies", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Body names. */
      } else if (strncmp(kind, "bodies", MAXCHR) == 0) {
        textc("The body names are:", TRUE);
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          textc("  body ", FALSE);
          textc(body->name, FALSE);
          textc(&spaces[strlen(body->name)+8-MAXCHR], FALSE);
          next = FALSE;
          for (solid=body->bdySld; solid; solid=solid->nxtSld) {
            if (next) {
              textc(" and ", FALSE);
            } else {
              textc(" with solid ", FALSE);
            }
            textc(solid->name, FALSE);
            textc(&spaces[strlen(solid->name)+8-MAXCHR], FALSE);
            next = TRUE;
          }
          textc("", TRUE);
        }
        if (all) {
          strncpy(kind, "contacts", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Contacts. */
      } else if (strncmp(kind, "contacts", MAXCHR) == 0) {
        textc("The contact names are:", TRUE);
        for (cntact=System.sysCnt; cntact; cntact=cntact->nxtCnt) {
          textc("  contact ", FALSE);
          textc(cntact->name, FALSE);
          textc(&spaces[strlen(cntact->name)+8-MAXCHR], FALSE);
          textc(" between solid ", FALSE);
          textc(cntact->cnSldB->name, FALSE);
          textc(&spaces[strlen(cntact->cnSldB->name)+8-MAXCHR], FALSE);
          textc(" on body ", FALSE);
          textc(cntact->cnSldB->sldBdy->name, FALSE);
          textc(&spaces[strlen(cntact->cnSldB->sldBdy->name)+8-MAXCHR], 
            FALSE);
          textc(" and solid ", FALSE);
          textc(cntact->cnSldA->name, FALSE);
          textc(&spaces[strlen(cntact->cnSldA->name)+8-MAXCHR], FALSE);
          textc(" on body ", FALSE);
          textc(cntact->cnSldA->sldBdy->name, TRUE);
        }
        if (all) {
          strncpy(kind, "joints", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Joint names. */
      } else if (strncmp(kind, "joints", MAXCHR) == 0) {
        textc("The joint names are:", TRUE);
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          textc("  joint ", FALSE);
          textc(joint->name, FALSE);
          textc(&spaces[strlen(joint->name)+8-MAXCHR], FALSE);
          textc(" connecting body ", FALSE);
          textc(joint->jntAxB->axsBdy->name, FALSE);
          textc(&spaces[strlen(joint->jntAxB->axsBdy->name)+8-MAXCHR],
            FALSE);
          textc(" to body ", FALSE);
          textc(joint->jntAxA->axsBdy->name, TRUE);
        }
        if (all) {
          strncpy(kind, "axes", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Axes names. */
      } else if (strncmp(kind, "axes", MAXCHR) == 0) {
        textc("The axes names are:", TRUE);
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
            if (strcmp(axes->name, "")) {
              textc("  axes ", FALSE);
              textc(axes->name, FALSE);
              textc(&spaces[strlen(axes->name)+8-MAXCHR], FALSE);
              textc(" on body ", FALSE);
              textc(body->name, TRUE);
            }
          }
        }
        if (all) {
          strncpy(kind, "points", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Point names. */
      } else if (strncmp(kind, "points", MAXCHR) == 0) {
        textc("The point names are:", TRUE);
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (point=body->bdyPnt; point; point=point->nxtPnt) {
            if (point->master) {
              textc("  point ", FALSE);
              textc(point->name, FALSE);
              textc(&spaces[strlen(point->name)+8-MAXCHR], FALSE);
              textc(" on body ", FALSE);
              textc(point->pntBdy->name, TRUE);
            }
          }
        }
        if (all) {
          strncpy(kind, "springs", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Spring names. */
      } else if (strncmp(kind, "springs", MAXCHR) == 0) {
        textc("The spring names are:", TRUE);
        for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
          textc("  spring ", FALSE);
          textc(spring->name, FALSE);
          textc(&spaces[strlen(spring->name)+8-MAXCHR], FALSE);
          textc(" from point ", FALSE);
          textc(spring->spgPtB->name, FALSE);
          textc(&spaces[strlen(spring->spgPtB->name)+8-MAXCHR], FALSE);
          textc(" to point ", FALSE);
          textc(spring->spgPtA->name, TRUE);
        }
        if (all) {
          strncpy(kind, "dampers", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Damper names. */
      } else if (strncmp(kind, "dampers", MAXCHR) == 0) {
        textc("The damper names are:", TRUE);
        for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
          textc("  damper ", FALSE);
          textc(damper->name, FALSE);
          textc(&spaces[strlen(damper->name)+8-MAXCHR], FALSE);
          textc(" from point ", FALSE);
          textc(damper->dmpPtB->name, FALSE);
          textc(&spaces[strlen(damper->dmpPtB->name)+8-MAXCHR], FALSE);
          textc(" to point ", FALSE);
          textc(damper->dmpPtA->name, TRUE);
        }
        if (all) {
          strncpy(kind, "forces", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Force names. */
      } else if (strncmp(kind, "forces", MAXCHR) == 0) {
        textc("The force names are:", TRUE);
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (force=body->bdyFrc; force; force=force->nxtFrc) {
            textc("  force ", FALSE);
            textc(force->name, FALSE);
            textc(&spaces[strlen(force->name)+8-MAXCHR], FALSE);
            textc(" onto body ", FALSE);
            textc(force->frcPtC->pntBdy->name, TRUE);
          }
        }
        if (all) {
          strncpy(kind, "torques", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Torque names. */
      } else if (strncmp(kind, "torques", MAXCHR) == 0) {
        textc("The torque names are:", TRUE);
        for (body=System.sysBdy; body; body=body->nxtBdy) {
          for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
            textc("  torque ", FALSE);
            textc(torque->name, FALSE);
            textc(&spaces[strlen(torque->name)+8-MAXCHR], FALSE);
            textc(" onto body ", FALSE);
            textc(torque->trqBdy->name, TRUE);
          }
        }
        if (all) {
          strncpy(kind, "inputs", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Sgcs. */
      } else if (strncmp(kind, "inputs", MAXCHR) == 0) {
        textc("The SGC's are:", TRUE);
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
            if (jvar->jvrSgc) {
              textc("  SGC ", FALSE);
              textc(joint->name, FALSE);
              textc(&spaces[strlen(joint->name)+8-MAXCHR], FALSE);
              itextc(jvar->jvrnoJ+1);
              textc("", TRUE);
            }
          }
        }
        if (all) {
          strncpy(kind, "ic", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all Ics. */
      } else if (strncmp(kind, "ic", MAXCHR) == 0) {
        textc("The IC's are:", TRUE);
        for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
          for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
            if (jvar->jvrIc) {
              textc("  IC ", FALSE);
              textc(joint->name, FALSE);
              textc(&spaces[strlen(joint->name)+8-MAXCHR], FALSE);
              itextc(jvar->jvrnoJ+1);
              textc("", TRUE);
            }
          }
        }
        if (all) {
          strncpy(kind, "", MAXCHR);
          kind[MAXCHR] = '\0';
        }

/* List all loop member names. */
      } else if (strncmp(kind, "loops", MAXCHR) == 0) {
        if (System.level < 1) loopsc();
        textc("The joint/loop membership is:", TRUE);
        if (System.nloops > 0) {
          textc(&spaces[8-MAXCHR], FALSE);
          for (i=1; i<=System.nloops; i++) {
            textc("  ", FALSE);
            itextc(i);                  /* List loop heading numbers. */
          }
          textc("", TRUE);
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            textc(joint->name, FALSE);
            textc(&spaces[strlen(joint->name)+8-MAXCHR], FALSE);
            marks = joint->loopflags;
            while (marks) {
              if (marks % 2) {
                if (joint->orient < 0) {
                  textc(" -X", FALSE);
                }  else {
                  textc("  X", FALSE);
                }
              } else {
                textc("   ", FALSE);
              }
              marks /= 2;
            }
            textc("", TRUE);
          }
        }

/* List all tolerance values. */
      } else if (strncmp(kind, "zeroes", MAXCHR) == 0) {
        textc("The tolerances are:", TRUE);
        textc("  unit(mass)    = ", FALSE);
        gtextc(System.gc);
        textc("", TRUE);
        textc("  zero(force)   = ", FALSE);
        gtextc(System.ferr);
        textc(", ", FALSE);
        gtextc(System.pferr);
        textc("", TRUE);
        textc("  zero(data)    = ", FALSE);
        gtextc(System.dtoll);
        textc("", TRUE);
        textc("  zero(position)= ", FALSE);
        gtextc(System.ptoll);
        textc(", ", FALSE);
        itextc(System.cn);
        textc("", TRUE);
        textc("  zero(equilib) = ", FALSE);
        gtextc(System.etoll);
        textc(", ", FALSE);
        itextc(System.en);
        textc("", TRUE);
        textc("  zero(system)  = ", FALSE);
        gtextc(System.fjtol);
        textc("", TRUE);
        textc("  zero(inertia) = ", FALSE);
        gtextc(System.dytol);
        textc("", TRUE);
        textc("  zero(spring)  = ", FALSE);
        gtextc(System.fktol);
        textc("", TRUE);
        textc("  zero(zero)    = ", FALSE);
        gtextc(System.zero);
        textc("", TRUE);

/* Print a message for an unrecognized type. */
      } else {
        textc("*** Identify '", FALSE);
        textc(kind, FALSE);
        textc("' is not defined; ignored. ***", TRUE);
      }
      if (all && (lenc(kind) > 0)) goto _2;
    }
  }
  return;
}

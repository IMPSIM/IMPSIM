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
/* deletc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete specified records from the IMP data structure.
|
|     Access:
|       void deletc()
|
|     Error Conditions:
|       System.nerror = 2 indicates an unrecognized type of DELETE
|     statement; a message is printed.
|
|     Comments:
|       The type and list of items to be deleted is assumed to be stored
|     in the token[] array of inputc.h by readc() before entry.  The
|     formats of all tokens are assumed to be TK_CHAR, but have not yet
|     been checked.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void deletc()
{
  Body    *body;
  Contact *contact;
  Damper  *damper;
  Force   *force;
  Joint   *joint;
  Jvar    *jvar;
  Point   *point;
  Request *rqst;
  Solid   *solid;
  Spring  *spring;
  Torque  *torque;
  Value   *value;
  Word     string;
  int      i, j, njvar;
  real     undef;

/* Check the format of the second word of the DELETE statement. */
  frmatc(1, 1, TK_CHAR);
  if (System.nerror) return;
  lcasec(token[1].data.text);

/* Treat a DELETE BODY statement. */
  if ((strncmp(token[1].data.text, "body", MAXCHR) == 0) ||
      (strncmp(token[1].data.text, "link", MAXCHR) == 0)) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          while (System.sysBdy) xbodyc(System.sysBdy);
          continue;
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            if (strcmp(body->name, token[i].data.text) == 0) {
              xbodyc(body);
              break;
            }
          }
          if (body) continue;
        }
      }
      echoc();
      textc("*** Unknown body '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE CONTACT statement. */
  } else if (strncmp(token[1].data.text, "contact", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          while (System.sysCnt) xcntc(System.sysCnt);
          continue;
        } else {
          for (contact=System.sysCnt; contact; contact=contact->nxtCnt){
            if (strcmp(contact->name, token[i].data.text) == 0) {
              xcntc(contact);
              break;
            }
          }
          if (contact) continue;
        }
      }
      echoc();
      textc("*** Unknown contact '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE DAMPER statement. */
  } else if (strncmp(token[1].data.text, "damper", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              ldnanc((void *) &(jvar->c));
            }
          }
          while (System.sysDmp) xdmprc(System.sysDmp);
          continue;
        } else {
          for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
            if (strcmp(damper->name, token[i].data.text) == 0) {
              xdmprc(damper);
              break;
            }
          }
          if (damper) continue;
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              i++;
              frmatc(i, 1, TK_INT);
              if (System.nerror) break;
              njvar = token[i].data.number;
              if ((njvar > 0) && (njvar <= joint->njvars)) {
                jvar = joint->jntJvr;
                for (j=0; j<njvar; j++) {
                  jvar=jvar->nxtJvr;
                }
                ldnanc((void *) &jvar->c);
              }
              break;
            }
          }
          if (joint || System.nerror) continue;
        }
      }
      echoc();
      textc("*** Unknown damper '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE DYNAMICS statement. */
  } else if (strncmp(token[1].data.text, "dynamics", MAXCHR) == 0) {
    xdync();

/* Treat a DELETE EQUILIBRIUM statement. */
  } else if (strncmp(token[1].data.text, "equilibrium", MAXCHR) == 0) {
    if (System.mode == MD_STAT) {
      for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
        for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
          if (jvar->jvrSgc) xsgc(jvar->jvrSgc);
        }
      }
      System.mode = MD_UNDEF;
    } else {
      echoc();
      textc("*** Static mode is not defined. ***", TRUE);
      System.nerror = 5;
    }

/* Treat a DELETE FORCE statement. */
  } else if (strncmp(token[1].data.text, "force", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              ldnanc((void *) &(jvar->force));
            }
          }
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            while (body->bdyFrc) xforc(body->bdyFrc);
          }
          continue;
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (force=body->bdyFrc; force; force=force->nxtFrc) {
              if (strcmp(force->name, token[i].data.text) == 0) {
                xforc(force);
                break;
              }
            }
            if (force) break;
          }
          if (force) continue;
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              i++;
              frmatc(i, 1, TK_INT);
              if (System.nerror) break;
              njvar = token[i].data.number;
              if ((njvar > 0) && (njvar <= joint->njvars)) {
                jvar = joint->jntJvr;
                for (j=0; j<njvar; j++) {
                  jvar=jvar->nxtJvr;
                }
                ldnanc((void *) &(jvar->force));
              }
              break;
            }
          }
          if (joint || System.nerror) continue;
        }
      }
      echoc();
      textc("*** Unknown force '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE GRAVITY statement. */
  } else if (strncmp(token[1].data.text, "gravity", MAXCHR) == 0) {
    ldnanc((void *) &undef);
    dgravc(undef, undef, undef);

/* Treat a DELETE IC statement. */
  } else if (strncmp(token[1].data.text, "ic", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              if (jvar->jvrIc) xic(jvar->jvrIc);
            }
          }
          continue;
        } else {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              i++;
              frmatc(i, 1, TK_INT);
              if (System.nerror) break;
              njvar = token[i].data.number;
              if ((njvar > 0) && (njvar <= joint->njvars)) {
                jvar = joint->jntJvr;
                for (j=0; j<njvar; j++) {
                  jvar=jvar->nxtJvr;
                }
                if (jvar->jvrIc) xic(jvar->jvrIc);
              }
              break;
            }
          }
          if (joint || System.nerror) continue;
        }
      }
      echoc();
      textc("*** Unknown joint '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE JOINT statement. */
  } else if (strncmp(token[1].data.text, "joint", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          while (System.sysJnt) xjntc(System.sysJnt);
          continue;
        } else {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              xjntc(joint);
              break;
            }
          }
          if (joint) continue;
        }
      }
      echoc();
      textc("*** Unknown joint '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE LIST statement. */
  } else if (strncmp(token[1].data.text, "list", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          rqst = System.sysReq;
          while (rqst) {
            if (rqst->reqtyp == RQ_LIST) {
              xrqstc(rqst);
              rqst = System.sysReq;
            } else {
              rqst = rqst->nxtReq;
            }
          }
          continue;
        } else {
          for (rqst=System.sysReq; rqst; rqst=rqst->nxtReq) {
            if (rqst->reqtyp == RQ_LIST) {
              if ((strncmp(string, "value", MAXCHR) == 0)
                && (rqst->outtyp == OT_VAL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "position", MAXCHR) == 0)
                && (rqst->outtyp == OT_POS)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "velocity", MAXCHR) == 0)
                && (rqst->outtyp == OT_VEL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "acceleration", MAXCHR) == 0)
                && (rqst->outtyp == OT_ACC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "force", MAXCHR) == 0)
                && (rqst->outtyp == OT_FORC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "heading", MAXCHR) == 0)
                && (rqst->outtyp == OT_HDNG)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "frequency", MAXCHR) == 0)
                && (rqst->outtyp == OT_FREQ)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "dynamics", MAXCHR) == 0)
                && (rqst->outtyp == OT_DYN)) {
                xrqstc(rqst);
                break;
              }
            }
          }
          if (rqst) continue;
        }
      }
      echoc();
      textc("*** Unknown item '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE MASS statement. */
  } else if (strncmp(token[1].data.text, "mass", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            if (body->bdyMas) xmassc(body->bdyMas);
          }
          continue;
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            if (strcmp(body->name, token[i].data.text) == 0) {
              if (body->bdyMas) {
                xmassc(body->bdyMas);
                break;
              }
            }
          }
          if (body) continue;
        }
      }
      echoc();
      textc("*** Unknown body '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE MOTION or DELETE INPUT statement. */
  } else if ((strncmp(token[1].data.text, "motion", MAXCHR) == 0)
          || (strncmp(token[1].data.text, "input",  MAXCHR) == 0)) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              if (jvar->jvrSgc) xsgc(jvar->jvrSgc);
            }
          }
          if (System.mode != MD_DYN) System.mode = MD_UNDEF;
          continue;
        } else {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              i++;
              frmatc(i, 1, TK_INT);
              if (System.nerror) break;
              njvar = token[i].data.number;
              if ((njvar > 0) && (njvar <= joint->njvars)) {
                jvar = joint->jntJvr;
                for (j=0; j<njvar; j++) {
                  jvar=jvar->nxtJvr;
                }
                if (jvar->jvrSgc) xsgc(jvar->jvrSgc);
              }
              break;
            }
          }
          if (joint || System.nerror) continue;
        }
      }
      echoc();
      textc("*** Unknown joint '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE PLOT statement. */
  } else if (strncmp(token[1].data.text, "plot", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          rqst = System.sysReq;
          while (rqst) {
            if (rqst->reqtyp == RQ_PLOT) {
              xrqstc(rqst);
              rqst = System.sysReq;
            } else {
              rqst = rqst->nxtReq;
            }
          }
          continue;
        } else {
          for (rqst=System.sysReq; rqst; rqst=rqst->nxtReq) {
            if (rqst->reqtyp == RQ_PLOT) {
              if ((strncmp(string, "value", MAXCHR) == 0)
                && (rqst->outtyp == OT_VAL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "position", MAXCHR) == 0)
                && (rqst->outtyp == OT_POS)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "velocity", MAXCHR) == 0)
                && (rqst->outtyp == OT_VEL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "acceleration", MAXCHR) == 0)
                && (rqst->outtyp == OT_ACC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "force", MAXCHR) == 0)
                && (rqst->outtyp == OT_FORC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "dynamics", MAXCHR) == 0)
                && (rqst->outtyp == OT_DYN)) {
                xrqstc(rqst);
                break;
              }
            }
          }
          if (rqst) continue;
        }
      }
      echoc();
      textc("*** Unknown item '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE POINT statement. */
  } else if (strncmp(token[1].data.text, "point", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            while (body->bdyPnt) xpntc(body->bdyPnt);
          }
          continue;
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (point=body->bdyPnt; point; point=point->nxtPnt) {
              if (strcmp(point->name, token[i].data.text) == 0) {
                xpntc(point);
                break;
              }
            }
            if (point) break;
          }
          if (point) continue;
        }
      }
      echoc();
      textc("*** Unknown point '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE PRINT statement. */
  } else if (strncmp(token[1].data.text, "print", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          rqst = System.sysReq;
          while (rqst) {
            if (rqst->reqtyp == RQ_PRINT) {
              xrqstc(rqst);
              rqst = System.sysReq;
            } else {
              rqst = rqst->nxtReq;
            }
          }
          continue;
        } else {
          for (rqst=System.sysReq; rqst; rqst=rqst->nxtReq) {
            if (rqst->reqtyp == RQ_PRINT) {
              if ((strncmp(string, "value", MAXCHR) == 0)
                && (rqst->outtyp == OT_VAL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "position", MAXCHR) == 0)
                && (rqst->outtyp == OT_POS)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "velocity", MAXCHR) == 0)
                && (rqst->outtyp == OT_VEL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "acceleration", MAXCHR) == 0)
                && (rqst->outtyp == OT_ACC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "force", MAXCHR) == 0)
                && (rqst->outtyp == OT_FORC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "heading", MAXCHR) == 0)
                && (rqst->outtyp == OT_HDNG)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "frequency", MAXCHR) == 0)
                && (rqst->outtyp == OT_FREQ)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "dynamics", MAXCHR)
                  == 0) && (rqst->outtyp == OT_DYN)) {
                xrqstc(rqst);
                break;
              }
            }
          }
          if (rqst) continue;
        }

/* Treat a DELETE PRINT INPUT statement. */
        if (strncmp(string, "input", MAXCHR) == 0) {
          echonc(0);
          break;;
        }
      }
      echoc();
      textc("*** Unknown item '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE SOLID statement. */
  } else if (strncmp(token[1].data.text, "solid", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            while (body->bdySld) xsldc(body->bdySld);
          }
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (solid=body->bdySld; solid; solid=solid->nxtSld) {
              if (strcmp(solid->name, token[i].data.text) == 0) {
                xsldc(solid);
                break;
              }
            }
            if (solid) break;
          }
          if (body) continue;
        }
      }
      echoc();
      textc("*** Unknown solid '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE SPRING statement. */
  } else if (strncmp(token[1].data.text, "spring", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            for (jvar=joint->jntJvr; jvar; jvar=jvar->nxtJvr) {
              ldnanc((void *) &(jvar->k));
              ldnanc((void *) &(jvar->freepos));
            }
          }
          while (System.sysSpg) xspngc(System.sysSpg);
          continue;
        } else {
          for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
            if (strcmp(spring->name, token[i].data.text) == 0) {
              xspngc(spring);
              break;
            }
          }
          if (spring) continue;
          for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
            if (strcmp(joint->name, token[i].data.text) == 0) {
              i++;
              frmatc(i, 1, TK_INT);
              if (System.nerror) break;
              njvar = token[i].data.number;
              if ((njvar > 0) && (njvar <= joint->njvars)) {
                jvar = joint->jntJvr;
                for (j=0; j<njvar; j++) {
                  jvar=jvar->nxtJvr;
                }
                ldnanc((void *) &(jvar->k));
                ldnanc((void *) &(jvar->freepos));
              }
              break;
            }
          }
          if (joint || System.nerror) continue;
        }
      }
      echoc();
      textc("*** Unknown spring '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE STORE statement. */
  } else if (strncmp(token[1].data.text, "store", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          rqst = System.sysReq;
          while (rqst) {
            if (rqst->reqtyp == RQ_STORE) {
              xrqstc(rqst);
              rqst = System.sysReq;
            } else {
              rqst = rqst->nxtReq;
            }
          }
          continue;
        } else {
          for (rqst=System.sysReq; rqst; rqst=rqst->nxtReq) {
            if (rqst->reqtyp == RQ_STORE) {
              if ((strncmp(string, "value", MAXCHR) == 0)
                && (rqst->outtyp == OT_VAL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "position", MAXCHR) == 0)
                && (rqst->outtyp == OT_POS)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "velocity", MAXCHR) == 0)
                && (rqst->outtyp == OT_VEL)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "acceleration", MAXCHR) == 0)
                && (rqst->outtyp == OT_ACC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "force", MAXCHR) == 0)
                && (rqst->outtyp == OT_FORC)) {
                xrqstc(rqst);
                break;
              } else if ((strncmp(string, "dynamics", MAXCHR) == 0)
                && (rqst->outtyp == OT_DYN)) {
                xrqstc(rqst);
                break;
              }
            }
          }
          if (rqst) continue;
        }

/* Treat a DELETE STORE INPUT statement. */
        if (strncmp(string, "input", MAXCHR) == 0) {
          endsvc();
          break;
        }
      }
      echoc();
      textc("*** Unknown item '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE TORQUE statement. */
  } else if (strncmp(token[1].data.text, "torque", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            while (body->bdyTrq) xtorqc(body->bdyTrq);
          }
          continue;
        } else {
          for (body=System.sysBdy; body; body=body->nxtBdy) {
            for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
              if (strcmp(torque->name, token[i].data.text) == 0) {
                xtorqc(torque);
                break;
              }
            }
            if (torque) break;
          }
          if (torque) continue;
        }
      }
      echoc();
      textc("*** Unknown torque '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE TITLE statement. */
  } else if (strncmp(token[1].data.text, "title", MAXCHR) == 0) {
    ldttlc("\0");

/* Treat a DELETE VALUE statement. */
  } else if (strncmp(token[1].data.text, "value", MAXCHR) == 0) {
    for (i=2; i<ntokns; i++) {
      frmatc(i, 1, TK_CHAR);
      if (System.nerror == 0) {
        strcpy(string, token[i].data.text);
        lcasec(string);
        if (strcmp(string, "all") == 0) {
          while (System.sysVal) xvaluc(System.sysVal);
          continue;
        } else {
          for (value=System.sysVal; value; value=value->nxtVal) {
            if (strcmp(value->name, token[i].data.text) == 0) {
              xvaluc(value);
              break;
            }
          }
          if (value) continue;
        }
      }
      echoc();
      textc("*** Unknown value '", FALSE);
      textc(token[i].data.text, FALSE);
      textc("' ignored. ***", TRUE);
    }

/* Treat a DELETE VIEW statement. */
  } else if (strncmp(token[1].data.text, "view", MAXCHR) == 0) {
    vdelc(0);

/* Print a diagnostic for an unrecognized DELETE statement. */
  } else {
    echoc();
    textc("*** The DELETE '", FALSE);
    textc(token[1].data.text, FALSE);
    textc("' statement is not defined. ***", TRUE);
    System.nerror = 2;
  }
  return;
}

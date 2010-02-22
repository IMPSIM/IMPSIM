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
/* jointc-07 May 00:21 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Add a joint of specified type and perhaps bodies to the system
|     model.
|
|     Access:
|       (void) jointc(enum Jnttyp jttype, Word jtname, Word bdbefr,
|         Word bdaftr);
|     enum Jnttyp jttype,i-Flag indicating the type of joint.
|     Word jtname,i-Name of the joint.
|     Word bdbefr,i-Name of the body preceeding the joint.
|     Word bdaftr,i-Name of the body following the joint.
|
|     Error Conditions:
|       System.nerror = 5 indicates a self loop.
|
|     Comments:
|       System.level = 0 on successful completion.
*
*     History:
*     01 Jan 00:JJU-Original.
*     09 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void jointc(enum Jnttyp jttype, Word jtname, Word bdbefr, Word bdaftr)
#else
  void jointc(jttype, jtname, bdbefr, bdaftr)
  enum Jnttyp jttype;
  Word jtname, bdbefr, bdaftr;
#endif
{
  Axes  *axes, *axs;
  Body  *bodya, *bodyb;
  Joint *joint, *jnt;
  Jvar  *jvar, *jvr;
  Word   bdname;
  int    i, j, njvars;

/* Check for a self loop. */
  if (strncmp(bdbefr, bdaftr, MAXCHR) == 0) {
    System.nerror = 5;
    echoc();
    textc("*** Error: A joint cannot connect a body to itself. ***",
      TRUE);
    return;
  }

/* Delete any previous joint with the same name. */
  for (joint=System.sysJnt; joint; joint=joint->nxtJnt) {
    if (strncmp(joint->name, jtname, MAXCHR) == 0) {
      xjntc(joint);
      echoc();
      textc("*** The former joint '", FALSE);
      textc(jtname, FALSE);
      textc("' is replaced. ***", TRUE);
      break;
    }
  }

/* Form the joint record. */
  joint = (Joint *) malloc(sizeof(Joint));
  strcpy(joint->name, jtname);
  joint->nxtJnt = NULL;
  if (System.sysJnt) {        /* Add new Joint to end of linked list. */
    jnt = System.sysJnt;
    while (jnt->nxtJnt) jnt = jnt->nxtJnt;
    jnt->nxtJnt = joint;
  } else {
    System.sysJnt = joint;
  }
  joint->jntAxB = NULL;
  joint->jntAxA = NULL;
  joint->jntJvr = NULL;
  joint->jtype  = jttype;
  joint->orient = 0;
  joint->jntno  = System.njnts++;
  joint->loopflags = 0;
  ldnanc((void *) &(joint->param[0]));
  ldnanc((void *) &(joint->param[1]));
  ldnanc((void *) &(joint->param[2]));
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++) {
      joint->Phi[i][j] = 0.0;
    }
    joint->Phi[i][i] = 1.0;
  }
  joint->axsize   = 0.0;

/* Determine the number of joint variables. */
  switch (jttype) {
  case RIGID:
    njvars = 0;
    break;
  case XPIN:
  case YPIN:
  case ZPIN:
  case XSLIDE:
  case YSLIDE:
  case ZSLIDE:
  case SCREW:
    njvars = 1;
    break;
  case CYLINDER:
  case UJOINT:
  case BEVEL:
    njvars = 2;
    break;
  case FLAT:
  case PLANE:
  case GEAR:
  case RACK:
  case CAM:
  case SLOT:
    njvars = 3;
    break;
  case SPHERE:
    njvars = 4;
    break;
  case OPEN:
    njvars = 7;
  }
  joint->njvars = njvars;

/* Form the joint variable records. */
  for (i=0; i<njvars; i++) {
    jvar = (Jvar *) malloc(sizeof(Jvar));
    jvar->type = JVAR;
    jvar->nxtJvr = NULL;
    if (joint->jntJvr) {       /* Add new Jvar to end of linked list. */
      jvr = joint->jntJvr;
      while (jvr->nxtJvr) jvr = jvr->nxtJvr;
      jvr->nxtJvr = jvar;
    } else {
      joint->jntJvr = jvar;
    }
    jvar->jvrJnt = joint;
    jvar->jvrSgc = NULL;
    jvar->jvrIc  = NULL;
    jvar->jvrnoJ = i;
    jvar->jvrnoS = 0;
    switch (jttype) {
    case XPIN:
    case YPIN:
    case ZPIN:
    case BEVEL:
    case UJOINT:
      jvar->jvrtyp = JV_ANGULAR;
      break;
    case XSLIDE:
    case YSLIDE:
    case ZSLIDE:
    case SCREW:
    case RACK:
    case CAM:
      jvar->jvrtyp = JV_LINEAR;
      break;
    case CYLINDER:
    case GEAR:
      if (i == 0) {
        jvar->jvrtyp = JV_ANGULAR;
      } else {
        jvar->jvrtyp = JV_LINEAR;
      }
      break;
    case SLOT:
      if (i == 1) {
        jvar->jvrtyp = JV_ANGULAR;
      } else {
        jvar->jvrtyp = JV_LINEAR;
      }
      break;
    case FLAT:
      if (i == 1) {
        jvar->jvrtyp = JV_LINEAR;
      } else {
        jvar->jvrtyp = JV_ANGULAR;
      }
      break;
    case PLANE:
      if (i < 2) {
        jvar->jvrtyp = JV_LINEAR;
      } else {
        jvar->jvrtyp = JV_ANGULAR;
      }
      break;
    case SPHERE:
      jvar->jvrtyp = JV_EULER;
      break;
    case OPEN:
      if (i < 3) {
        jvar->jvrtyp = JV_LINEAR;
      } else {
        jvar->jvrtyp = JV_EULER;
      }
      break;
    }
    ldnanc((void *) &(jvar->D[0]));
    jvar->jvrVk  = NULL;
    ldnanc((void *) &(jvar->k));
    jvar->jvrVfp = NULL;
    ldnanc((void *) &(jvar->freepos));
    jvar->jvrVc  = NULL;
    ldnanc((void *) &(jvar->c));
    jvar->jvrVf  = NULL;
    ldnanc((void *) &(jvar->force));
    jvar->jvrVup = NULL;
    jvar->jvrVvp = NULL;
    ldnanc((void *) &(jvar->design));
    ldnanc((void *) &(jvar->lastpos));
    ldnanc((void *) &(jvar->lastvel));
    ldnanc((void *) &(jvar->lastacc));
    ldnanc((void *) &(jvar->pos));
    ldnanc((void *) &(jvar->vel));
    ldnanc((void *) &(jvar->acc));
  }

/* Locate or form the body records. */
  strcpy(bdname, bdbefr);
  bodyb  = NULL;
_2:
  for (bodya=System.sysBdy; bodya; bodya=bodya->nxtBdy) {
    if (strncmp(bodya->name, bdname, MAXCHR) == 0) {
      break;
    }
  }
  if (bodya == NULL) bodya = mkbdyc(bdname);

/* Form the axes record for this body at this joint. */
  axes = (Axes *) malloc(sizeof(Axes));
  axes->type  = AXES;
  strcpy(axes->name, "");
  axes->nxtAxs = NULL;
  if (bodya->bdyAxs) {         /* Add new Axes to end of linked list. */
    axs = bodya->bdyAxs;
    while (axs->nxtAxs) axs = axs->nxtAxs;
    axs->nxtAxs = axes;
  } else {
    bodya->bdyAxs = axes;
  }
  axes->axsBdy = bodya;
  axes->axsJnt = joint;
  ldnanc((void *) &(axes->loopflags));
  axes->kcolor = kbkgnd;
  for (i=0; i<3; i++) {
    for (j=0; j<4; j++) {
      axes->S[i][j] = 0.0;
    }
    axes->S[i][i] = 1.0;
  }
  if (bodyb == NULL) {
    joint->jntAxB = axes;
    bodyb = bodya;
    strcpy(bdname, bdaftr);
    goto _2;
  } else {
    joint->jntAxA = axes;
  }
  return;
}

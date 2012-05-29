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
/* showc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Set the visibility and color flags for the named items.
|
|     Access:
|       (void) showc(int color, Token names[], int n);
|     int color,i-Color number for the items named.
|     Token names[n],i-Array of names of the items to be set.
|     int n,i-Count of the items in the names array.
|
|     Error Conditions:
|       If a named item is not found, it is ignored; no message is
|     printed.
|
|     Comments:
|       If n <= 0, then names[0] is treated as "all".
|       A names[] entry of "all" sets the visibility of all bodies,
|     springs, dampers, forces, and torques.
|       A negative color number is taken as a signal to set all color
|     and visibility flags negative to imply invisible.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void showc(int color, Token names[], int n)
#else
  void showc(color, names, n)
  int   color;
  Token names[];
  int   n;
#endif
{
  Axes   *axes;
  Body   *body;
  Damper *damper;
  Force  *force;
  Spring *spring;
  Torque *torque;
  Word    name;
  int     i, kolor, lgoto;
  long    mask;

/* Treat a SHOW or ERASE statement (with implicit "all"). */
  lgoto = TRUE;
  i = 0;
  do {
    if (i < n) {
      strcpy(name, names[i].data.text);
      lcasec(name);
      lgoto = (strcmp(name, "all") == 0);

/* Treat a SHOW or ERASE LOOP statement. */
    } else if (strncmp(names[i].data.text, "loop", 4) == 0) {
      if (System.level < 1) loopsc();
      if (System.nerror) return;
      if (names[i+1].kind == TK_INT) {
        if ((names[i+1].data.number >= 0) &&
            (names[i+1].data.number <= System.nloops))
              mask = 1 << (names[i+1].data.number-1);
        i++;
      } else {
        mask = (1 << System.nloops) - 1;
      }
      for (body=System.sysBdy; body; body=body->nxtBdy) {
        for (axes=body->bdyAxs; axes; axes=axes->nxtAxs) {
          if (iandc((void *) &(axes->loopflags), (void *) &mask)) {
            kolor = color;
            if (kolor < 0) kolor = -abs(axes->kcolor);
            axes->kcolor = kolor;
          }
        }
      }
      continue;
    }

/* Treat a SHOW or ERASE body->name statement. */
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      if (lgoto) {
        kolor = color;
        if (kolor < 0) kolor = -abs(body->kcolor);
        body->kcolor = kolor;
      } else if (strcmp(names[i].data.text, body->name) == 0) {
        kolor = color;
        if (kolor < 0) kolor = -abs(body->kcolor);
        body->kcolor = kolor;
        break;
      }
    }

/* Treat a SHOW or ERASE spring->name statement. */
    for (spring=System.sysSpg; spring; spring=spring->nxtSpg) {
      if (lgoto) {
        kolor = color;
        if (kolor < 0) kolor = -abs(spring->kcolor);
        spring->kcolor = kolor;
      } else if (strcmp(names[i].data.text, spring->name) == 0) {
        kolor = color;
        if (kolor < 0) kolor = -abs(spring->kcolor);
        spring->kcolor = kolor;
        break;
      }
    }

/* Treat a SHOW or ERASE damper->name statement. */
    for (damper=System.sysDmp; damper; damper=damper->nxtDmp) {
      if (lgoto) {
        kolor = color;
        if (kolor < 0) kolor = -abs(damper->kcolor);
        damper->kcolor = kolor;
      } else if (strcmp(names[i].data.text, damper->name) == 0) {
        kolor = color;
        if (kolor < 0) kolor = -abs(damper->kcolor);
        damper->kcolor = kolor;
        break;
      }
    }

/* Treat a SHOW or ERASE force->name statement. */
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (force=body->bdyFrc; force; force=force->nxtFrc) {
        if (lgoto) {
          kolor = color;
          if (kolor < 0) kolor = -abs(force->kcolor);
          force->kcolor = kolor;
        } else if (strcmp(names[i].data.text, force->name) == 0) {
          kolor = color;
          if (kolor < 0) kolor = -abs(force->kcolor);
          force->kcolor = kolor;
          break;
        }
      }
    }

/* Treat a SHOW or ERASE torque->name statement. */
    for (body=System.sysBdy; body; body=body->nxtBdy) {
      for (torque=body->bdyTrq; torque; torque=torque->nxtTrq) {
        if (lgoto) {
          kolor = color;
          if (kolor < 0) kolor = -abs(torque->kcolor);
          torque->kcolor = kolor;
        } else if (strcmp(names[i].data.text, torque->name) == 0) {
          kolor = color;
          if (kolor < 0) kolor = -abs(torque->kcolor);
          torque->kcolor = kolor;
          break;
        }
      }
    }
    i++;
  } while (i < n);
  return;
}

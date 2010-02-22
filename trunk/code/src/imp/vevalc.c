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
/* vevalc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Find the current numeric values for the specified Value record.
|
|     Access:
|       (void) vevalc(Value *value, real val[3]);
|     Value *value,i-Pointer to the Value record to be evaluated.
|     real val[3], o-Values found for the record and its derivatives.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The keyboard interrupt flag is set if a Value expression results
|     in a value of F_RETURN.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void vevalc(Value *value, real val[3])
#else
  void vevalc(value, val)
  Value *value;
  real   val[3];
#endif
{
  Value   *arg[4], *valu;
  Word     string[MAXCHR+1];
  enum Rectyp kind;
  complex *coeff;
  int      i, m, mark, mask, n, np, nv;
  real     ddy, dy, pos[12], temp, vals[12], vel[12], xmin, xmax, y;

/* Loop through the Value records. */
  for (i=0; i<3; i++) {
    ldnanc((void *) &val[i]);
  }
  for (valu=System.sysVal; valu; valu=valu->nxtVal) {
    if (!isnanc((void *) &valu->v) && !isnanc((void *) &valu->d1) &&
        !isnanc((void *) &valu->d2)) goto _3;

/* Gather arguments and test their values. */
    mask = 0;
    mark = 1;
    for (i=0; i<4; i++) {
      arg[i] = valu->arg[i];
      if (valu->arg[i]) {
        if (isnanc((void *) &valu->arg[i]->v )) mask +=     mark;
        if (isnanc((void *) &valu->arg[i]->d1)) mask += 2 * mark;
        if (isnanc((void *) &valu->arg[i]->d2)) mask += 4 * mark;
      } else {
        mask += 7 * mark;
      }
      mark *= 8;
    }

/* Treat an undefined function. */
    switch (valu->f) {
    case F_UNDEF:
      break;

/* Treat an equate operation. */
    case F_EQUAL:
      if ((mask & 1) == 0) valu->v  = arg[0]->v;
      if ((mask & 2) == 0) valu->d1 = arg[0]->d1;
      if ((mask & 4) == 0) valu->d2 = arg[0]->d2;
      break;

/* Treat an addition operation. */
    case F_PLUS:
      if ((mask &  9) == 0) valu->v  = arg[0]->v  + arg[1]->v;
      if ((mask & 18) == 0) valu->d1 = arg[0]->d1 + arg[1]->d1;
      if ((mask & 36) == 0) valu->d2 = arg[0]->d2 + arg[1]->d2;
      break;

/* Treat a subtraction operation. */
    case F_MINUS:
      if ((mask &  9) == 0) valu->v  = arg[0]->v  - arg[1]->v;
      if ((mask & 18) == 0) valu->d1 = arg[0]->d1 - arg[1]->d1;
      if ((mask & 36) == 0) valu->d2 = arg[0]->d2 - arg[1]->d2;
      break;

/* Treat a multiplication operation. */
    case F_MULT:
      if ((mask &  9) == 0) valu->v  = arg[0]->v  * arg[1]->v;
      if ((mask & 27) == 0) valu->d1 = arg[0]->d1 * arg[1]->v
                                     + arg[0]->v  * arg[1]->d1;
      if ((mask & 63) == 0) valu->d2 = arg[0]->d2 + arg[1]->v
        + 2.0 * arg[0]->d1 * arg[1]->d1 + arg[0]->v  * arg[1]->d2;
      break;

/* Treat a division operation. */
    case F_DIVIDE:
      if (fabs(arg[1]->v) > System.zero) {
        if ((mask &  9) == 0) valu->v  =  arg[0]->v  / arg[1]->v;
        if ((mask & 27) == 0) valu->d1 = (arg[0]->d1 * arg[1]->v
          - arg[0]->v  * arg[1]->d1) / (arg[1]->v  * arg[1]->v);
        if ((mask & 63) == 0) valu->d2 = (arg[0]->d2 + arg[1]->v
                      - 2.0 * valu->d1 * arg[1]->v * arg[1]->d1
          - arg[0]->v  * arg[1]->d2) / (arg[1]->v  * arg[1]->v);
      }
      break;

/* Treat a power operation. */
    case F_POWER:
      if (arg[1]->v > System.zero) {
        if ((mask &  9) == 0) valu->v  = pow(arg[0]->v, arg[1]->v);
        if ((mask & 27) == 0) valu->d1 = valu->v * arg[1]->d1
          * (arg[0]->d1 * arg[1]->v / arg[0]->v + log(arg[0]->v));
        if ((mask & 63) == 0) valu->d2 = valu->d1 * valu->d1 / valu->v
          + ((arg[0]->d2 * arg[1]->v  + arg[0]->d1 * (arg[1]->d1
          +  arg[1]->d1 - arg[0]->d1 * arg[1]->v  /  arg[0]->v))
          /  arg[0]->v  + log(arg[0]->v) * arg[1]->d2) * valu->v;
      }
      break;

/* Treat a constant. */
    case F_CONST:
      break;

/* Treat the time function. */
    case F_TIME:
      if (isnanc((void *) &System.t)) {
        valu->v = -0.000001;
      } else {
        valu->v = System.t;
      }
      valu->d1 = 1.0;
      valu->d2 = 0.0;
      break;

/* Treat an absolute value function. */
    case F_ABS:
      if ((arg[0]->v < 0.0) && ((mask & 7) == 0)) {
        valu->v  = -arg[0]->v;
        valu->d1 = -arg[0]->d1;
        valu->d2 = -arg[0]->d2;
      } else {
        if ((mask & 1) == 0) valu->v  = arg[0]->v;
        if ((mask & 2) == 0) valu->d1 = arg[0]->d1;
        if ((mask & 4) == 0) valu->d2 = arg[0]->d2;
      }
      break;

/* Treat an acceleration function. */
    case F_ACCEL:
      if ((mask & 8) == 0) {
        m = nint(arg[1]->v);
        temp = System.ascale;
        System.ascale = 1.0; /* F_POSITION should not return degrees. */
        if (m > 0) {
          nmacc(arg[0]->name, &kind, vals, &n);
          if (m <= n) valu->v = vals[m-1];
        }
        System.ascale = temp;
      }
      break;

/* Treat an arc cosine finction. */
    case F_ACOS:
      if ((mask & 1) == 0) {
        if (fabs(arg[0]->v) <= 1.0) {
          valu->v = acos(arg[0]->v);
          if (fabs(arg[0]->v) < 1.0) {
            temp = 1.0 / sqrt(1.0 - arg[0]->v * arg[0]->v);
            if ((mask & 3) == 0) valu->d1 = -temp * arg[0]->d1;
            if ((mask & 7) == 0) valu->d2 = -temp *
              (arg[0]->d2 + valu->d1 * valu->d1 * arg[0]->v);
          }
        }
      }
      break;

/* Treat an arc sine function. */
    case F_ASIN:
      if ((mask & 1) == 0) {
        if (fabs(arg[0]->v) <= 1.0) {
          valu->v = asin(arg[0]->v);
          if (fabs(arg[0]->v) < 1.0) {
            temp = 1.0 / sqrt(1.0 - arg[0]->v * arg[0]->v);
            if ((mask & 3) == 0) valu->d1 = temp * arg[0]->d1;
            if ((mask & 7) == 0) valu->d2 = temp *
              (arg[0]->d2 + valu->d1 * valu->d1 * arg[0]->v);
          }
        }
      }
      break;

/* Treat an arc tangent function. */
    case F_ATAN:
      if ((mask & 9) == 0) {
        if ((fabs(arg[0]->v) > System.zero) ||
            (fabs(arg[1]->v) > System.zero)) {
          valu->v = atan2(arg[0]->v, arg[1]->v);
          temp = 1.0 / (arg[0]->v * arg[0]->v + arg[1]->v * arg[1]->v);
          if ((mask & 27) == 0) valu->d1 = temp *
            (arg[0]->d1 * arg[1]->v - arg[0]->v * arg[1]->d1);
          if ((mask & 63) == 0) valu->d2 = temp *
            (arg[0]->d2 * arg[1]->v - arg[0]->v * arg[1]->d2 - 2.0 *
            valu->d1*(arg[0]->v * arg[0]->d1 + arg[1]->v * arg[1]->d1));
        }
      }
      break;

/* Treat a cosine function. */
    case F_COS:
      if ((mask & 1) == 0) valu->v  = cos(arg[0]->v);
      if ((mask & 3) == 0) valu->d1 = -arg[0]->d1 * sin(arg[0]->v);
      if ((mask & 7) == 0) valu->d2 = -arg[0]->d2 * sin(arg[0]->v)
                                      -arg[0]->d1 * arg[0]->d1*valu->v;
      break;

/* Treat an exponential function. */
    case F_EXP:
      if ((mask & 1) == 0) valu->v  = exp(arg[0]->v);
      if ((mask & 3) == 0) valu->d1 = arg[0]->d1 * valu->v;
      if ((mask & 7) == 0) valu->d2 = arg[0]->d2 * valu->v
                                    + arg[0]->d1 * valu->d1;
      break;

/* Treat a force function. */
    case F_FORCE:
      if ((mask & 8) == 0) {
        m = nint(arg[1]->v);
        if (m > 0) {
          nmforc(arg[0]->name, &kind, vals, &n);
          if (m <= n) valu->v = vals[m-1];
        }
      }
      break;

/* Treat an if function. */
    case F_IF:
      if ((mask & 1) == 0) {
        if (arg[0]->v < 0.0) {
          i = 1;
        } else if (arg[0]->v == 0.0) {
          i = 2;
        } else {
          i = 3;
        }
        valu->v  = arg[i]->v;
        valu->d1 = arg[i]->d1;
        valu->d2 = arg[i]->d2;
      }
      break;

/* Treat a natural logarithmic function. */
    case F_LOG:
      if (((mask & 1) == 0) && (arg[0]->v > System.zero)) {
        valu->v = log(arg[0]->v);
        if ((mask & 3) == 0) valu->d1 = arg[0]->d1 / arg[0]->v;
        if ((mask & 7) == 0) valu->d2 = arg[0]->d2 / arg[0]->v
                                        - valu->d1 * valu->d1;
      }
      break;

/* Treat a base-10 logarithmic function. */
    case F_LOG10:
      if (((mask & 1) == 0) && (arg[0]->v > System.zero)) {
        valu->v = log10(arg[0]->v);
        if ((mask & 3) == 0) valu->d1=0.4342944818*arg[0]->d1/arg[0]->v;
        if ((mask & 7) == 0) valu->d2=0.4342944818*arg[0]->d2/arg[0]->v
                                     - valu->d1*valu->d1/0.4342944818;
      }
      break;

/* Treat a position function. */
    case F_POSITION:
      if ((mask & 8) == 0) {
        m = nint(arg[1]->v);
        temp = System.ascale;
        System.ascale = 1.0; /* F_POSITION should not return degrees. */
        if (m > 0) {
          nmacc(arg[0]->name, &kind, vals, &n);    /* Find in reverse */
          nmvelc(arg[0]->name, &kind, vel, &nv);    /* to avoid being */
          nmposc(arg[0]->name, &kind, pos, &np);    /* reinitialized. */
          if (m <= np) valu->v  = pos[m-1];
          if (m <= nv) valu->d1 = vel[m-1];
          if (m <= n)  valu->d2 = vals[m-1];
        }
        System.ascale = temp;
      }
      break;

/* Treat a sine function. */
    case F_SIN:
      if ((mask & 1) == 0) valu->v  = sin(arg[0]->v);
      if ((mask & 3) == 0) valu->d1 = arg[0]->d1 * cos(arg[0]->v);
      if ((mask & 7) == 0) valu->d2 = arg[0]->d2 * cos(arg[0]->v)
                                    - arg[0]->d1 * arg[0]->d1 * valu->v;
      break;

/* Treat a square root function. */
    case F_SQRT:
      if (((mask & 1) == 0) && (arg[0]->v >= 0.0)) {
        valu->v = sqrt(arg[0]->v);
        if (arg[0]->v > System.zero) {
          if ((mask & 3) == 0) valu->d1 = 0.5 * arg[0]->d1 / valu->v;
          if ((mask & 7) == 0) valu->d2 = 0.5 * arg[0]->d2 / valu->v
            + valu->d1 * valu->d1 / arg[0]->v;
        }
      }
      break;

/* Treat a table function. */
    case F_TABLE:
      if ((mask & 1) == 0) {
        coeff = (complex *) valu->arg[1];
        n     = nint(coeff[0].r) / 2;
        xmin  = coeff[1].r;
        xmax  = coeff[1].i;
        fservc(arg[0]->v, xmin, xmax, &coeff[2], n, &y, &dy, &ddy);
        valu->v  = y;
        if ((mask & 3) == 0) valu->d1 = dy * arg[0]->d1;
        if ((mask & 7) == 0) valu->d2 = dy * arg[0]->d2
          + ddy * arg[0]->d1 * arg[0]->d1;
      }
      break;

/* Treat a tangent function. */
    case F_TAN:
      if ((mask & 1) == 0) {
        temp = cos(arg[0]->v);
        if (fabs(temp) > System.zero) {
          valu->v = tan(arg[0]->v);
          temp = 1.0 / (temp * temp);
          if ((mask & 3) == 0) valu->d1 = temp * arg[0]->d1;
          if ((mask & 7) == 0) valu->d2 = temp * (arg[0]->d2
            + 2.0 * valu->v * arg[0]->v * arg[0]->v);
        }
      }
      break;

/* Treat a user-defined function. */
    case F_USER:
      if (isnanc((void *) &System.t)) {
        temp = -0.000001;
      } else {
        temp = System.t;
      }
      valu->d2 = userc(arg[0]->name, temp, 2);
      valu->d1 = userc(arg[0]->name, temp, 1);
      valu->v  = userc(arg[0]->name, temp, 0);
      break;

/* Treat a velocity function. */
    case F_VELOCITY:
      if ((mask & 8) == 0) {
        m = nint(arg[1]->v);
        temp = System.ascale;
        System.ascale = 1.0; /* F_POSITION should not return degrees. */
        if (m > 0) {
          nmacc(arg[0]->name, &kind, vals, &n);/* Do in reverse order */
          nmvelc(arg[0]->name, &kind, vel, &nv); /* to avoid redoing. */
          if (m <= nv) valu->v  = vel[m-1];
          if (m <= n)  valu->d1 = vals[m-1];
        }
        System.ascale = temp;
      }
    }
_3: if (valu == value) break;
  }
  strcpy(string, value->name);
  lcasec(string);
  if ((strncmp(string, "return", MAXCHR) == 0)||(value->f == F_RETURN)){
    skbic();
    textc("*** RETURN requested by value. ***", TRUE);
  } else if((strncmp(string, "end", MAXCHR) == 0)||(value->f == F_END)){
    textc("*** END requested by value. ***", TRUE);
    endc();
  }
  val[0] = value->v;
  val[1] = value->d1;
  val[2] = value->d2;
  return;
}

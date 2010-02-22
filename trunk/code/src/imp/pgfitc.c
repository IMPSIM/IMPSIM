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
/* pgfitc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Scale the 2-d window boundaries to fit the IMP system modelled.
|
|     Access:
|       (void) pgfitc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       A border of two character widths is added on each side of the
|     figure, with two character heights at the top and four at the
|     bottom.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void pgfitc()
{
# define  BIG  1.0e10
  int i, j, k;
  real schsiz, smax, smin, tchsiz, tmax, tmin, w2, x2, x2max, x2min, y2,
    y2max, y2min, z2, x3lim[2], y3lim[2],z3lim[2];

/* Find the 3D bounds of the IMP system modelled. */
  sizec(&x3lim[0], &y3lim[0], &z3lim[0], &x3lim[1],&y3lim[1],&z3lim[1]);

/* Convert 3D coordinates to 2D screen limits. */
  x2max = -BIG;                     /* Set impossible initial values. */
  x2min =  BIG;
  y2max = -BIG;
  y2min =  BIG;
  for (i=0; i<2; i++){   /* Loop through all corners of bounding box. */
    for (j=0; j<2; j++){
      for (k=0; k<2; k++){
        x3to2c(x3lim[i], y3lim[j], z3lim[k], 1.0, &x2, &y2,&z2,&w2);
        x2 /= w2;             /* Transform 3D to 2D page coordinates. */
        y2 /= w2;
        z2 /= w2;
        x2max = max(x2, x2max);      /* Save limiting 2D page values. */
        x2min = min(x2, x2min);
        y2max = max(y2, y2max);
        y2min = min(y2, y2min);
      }
    }
  }

/* Set the screen limits to provide a border around the model. */
  qchszc(&schsiz, &tchsiz);         /* Get screen size of characters. */
  smax = (1.0 - 2.0 * schsiz);
  smin = (      2.0 * schsiz);
  tmax = (1.0 - 2.0 * tchsiz);
  tmin = (      4.0 * tchsiz);
  framsc(smin, tmin, smax, tmax);

/* Find the 2D coordinates of the center of the model. */
  x2 = 0.5 * (x2min + x2max);
  y2 = 0.5 * (y2min + y2max);

/* Adjust page limit values to let fram2c() fit screen aspect ratio. */
  if ((y2max-y2min) < qaspsc() * (x2max-x2min)){
    y2min = y2;
    y2max = y2;
  } else {
    x2min = x2;
    x2max = x2;
  }

/* Set the 2D page and screen limits. */
  fram2c(x2min, y2min, x2max, y2max);           /* Set 2D page frame. */
  framsc(0.0, 0.0, 1.0, 1.0);                 /* Set 2D screen frame. */
  return;
# undef BIG
}

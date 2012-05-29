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
/* sldstc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This function finds the nearest point to the convex hull of four 
|     or less points in 3-D.
|
|     Access:
|       (void) sldstc(int *nvxs, int irs[4], int jrs[4], real y[12], 
|         real del[16], real zsol[3], real als[4], real *dstsq, 
|         int *lbackup);
|     int  *nvxs,   i/o-Number of points; 1 <= *nvxs <= 4.
|     int  irs[4],  i/o-Index of coordinates of y[.,k] in polytope-i.
|     int  jrs[4],  i/o-Index of coordinates of y[.,k] in polytope-j.
|     real y[3,4],  i/o-Array containing the coordinates of the points;
|                       set difference y[.,k] = z[.,irs[k]]-z[.,jrs[k]].
|     real del[4,4],i/o-Dot products del[i,j] = y[.,i] * y[.,j].
|     real zsol[3],   o-Nearest point to the convex hull of y[3,4].
|     real als[4],    o-Barycentric coordinates of zsol[3].
|     real *dstsq,    o-Norm of zsol[3].
|     int  *lbackup,i/o-Flag showing if subalgorithm was/will be done
|                         using the backup procedure.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This function implements, in a very efficient way, the distance 
|     subalgorithm of finding the nearest point to the convex hull of 
|     four or less points in 3-D space.  The procedure and its efficient 
|     implementation are both due to D.W.Johnson.  Although this subrou-
|     tine is quite long, only a very small part of it is executed on 
|     each call.  Refer to sections 5 and 6 of the report mentioned in 
|     routine mndstc() for details concerning the distance subalgorithm.
|       sldstc() also determines an affinely independent subset of the
|     points such that zsol[] is the near point to the affine hull of 
|     the points in the subset.  The values *nvxs, y[3,4], irs[4], 
|     jrs[4], and del[4,4] are modified so that, on output, they corres-
|     pond to this subset of points.
|       On output als[4] holds barycentric coordinates of zsol[3], i.e.,
|     zsol[.] = als[0]*y[.,0] + ... + als[*nvxs-1]*y[.,*nvxs-1] and 
|     als[k] > 0 for k=1,...,*nvxs-1, and als[0]+...+als[*nvxs-1] = 1.0.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void sldstc(int *nvxs, int irs[4], int jrs[4], real y[12], 
    real del[16], real zsol[3], real als[4], real *dstsq, int *lbackup)
#else
  void sldstc(nvxs, irs, jrs, y, del, zsol, als, dstsq, lbackup)
  int  *nvxs, irs[4], jrs[4]; 
  real y[12], del[16], zsol[3], als[4], *dstsq;
  int  *lbackup;
#endif
{
  int  iord[4], irsd[4], jrsd[4], k, kk, kl, l, nvxsd;
  real alsd[4], deld[16], dstsqd, d1[15], d2[15], d3[15], d4[15], e123, 
         e124, e132, e134, e142, e143, e213, e214, e234, e243, e314, 
         e324, sum, yd[12], zsold[3];

/* Initialize. */
  d1[0] = d2[1] = d3[3] = d4[7] = 1.0;

/* See if the backup subalgorithm is requested on input. */
  if (!*lbackup) {

/* The regular distance subalgorithm starts here. */
    switch (*nvxs) {
    case 1:                                /* Case of a single point. */
      als[0]  = d1[0];
      zsol[0] = y[0];
      zsol[1] = y[4];
      zsol[2] = y[8];
      *dstsq  = del[0];
      goto DONE;
    case 2:                                    /* Case of two points. */
      d2[2] = del[0] - del[4];    /* Check the optimality of point 1. */
      if (d2[2] <= 0.0) {
        *nvxs   = 1;
        als[0]  = d1[0];
        zsol[0] = y[0];
        zsol[1] = y[4];
        zsol[2] = y[8];
        *dstsq  = del[0];
        goto DONE;
      }
      d1[2] = del[5] - del[4];    /* Check the optimality of line 12. */
      if ((d1[2] > 0.0) && (d2[2] > 0.0)) {
        sum = d1[2] + d2[2];
        als[0]  = d1[2] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[1] + als[0] * (y[0] - y[1]);
        zsol[1] = y[5] + als[0] * (y[4] - y[5]);
        zsol[2] = y[9] + als[0] * (y[8] - y[9]);
        *dstsq  = vdotc(3, zsol, zsol);
        goto DONE;
      }
      if (d1[2] <= 0.0) {         /* Check the optimality of point 2. */
        *nvxs   = 1;
        irs[0]  = irs[1];
        jrs[0]  = jrs[1];
        zsol[0] = y[1];
        zsol[1] = y[5];
        zsol[2] = y[9];
        *dstsq  = del[5];
        y[0]    = y[1];
        y[4]    = y[5];
        y[8]    = y[9];
        del[0]  = del[5];
        goto DONE;
      }
      goto BACKUP;  /* Go for the backup procedure; without new di[]. */
    case 3:                                  /* Case of three points. */
      d2[2] = del[0] - del[4];        /* Check optimality of point 1. */
      d3[4] = del[0] - del[8];
      if ((d2[2] <= 0.0) && (d3[4] <= 0.0)) {
        *nvxs   = 1;
        als[0]  = d1[0];
        zsol[0] = y[0];
        zsol[1] = y[4];
        zsol[2] = y[8];
        *dstsq  = del[0];
        goto DONE;
      }
      e132  = del[4] - del[9];    /* Check the optimality of line 12. */
      d1[2] = del[5] - del[4];
      d3[6] = d1[2] * d3[4] + d2[2] * e132;
      if ((d1[2] > 0.0) && (d2[2] > 0.0) && (d3[6] <= 0.0)) {
        *nvxs   = 2;
        sum     = d1[2] + d2[2];
        als[0]  = d1[2] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[1] + als[0] * (y[0] - y[1]);
        zsol[1] = y[5] + als[0] * (y[4] - y[5]);
        zsol[2] = y[9] + als[0] * (y[8] - y[9]);
        *dstsq  = vdotc(3, zsol, zsol);
        goto DONE;
      }
      e123  = del[8]  - del[9];   /* Check the optimality of line 13. */
      d1[4] = del[10] - del[8];
      d2[6] = d1[4] * d2[2] + d3[4] * e123;
      if ((d1[4] > 0.0) && (d2[6] <= 0.0) && (d3[4] > 0.0)) {
        *nvxs   = 2;
        irs[1]  = irs[2];
        jrs[1]  = jrs[2];
        sum = d1[4] + d3[4];
        als[0]  = d1[4] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[2]  + als[0] * (y[0] - y[2]);
        zsol[1] = y[6]  + als[0] * (y[4] - y[6]);
        zsol[2] = y[10] + als[0] * (y[8] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[1]    = y[2];
        y[5]    = y[6];
        y[9]    = y[10];
        del[4]  = del[8];
        del[5]  = del[10];
        goto DONE;
      }
      e213 = -e123;              /* Check the optimality of face 123. */
      d2[5] = del[10] - del[9];
      d3[5] = del[5]  - del[9];
      d1[6] = d2[5] * d1[2] + d3[5] * e213;
      if ((d1[6] > 0.0) && (d2[6] > 0.0) && (d3[6] > 0.0)) {
        sum = d1[6] + d2[6] + d3[6];
        als[0]  = d1[6] / sum;
        als[1]  = d2[6] / sum;
        als[2]  = 1.0 - als[0] - als[1];
        zsol[0] = y[2]  + als[0] * (y[0] - y[2] )
                        + als[1] * (y[1] - y[2] );
        zsol[1] = y[6]  + als[0] * (y[4] - y[6] )
                        + als[1] * (y[5] - y[6] );
        zsol[2] = y[10] + als[0] * (y[8] - y[10])
                        + als[1] * (y[9] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        goto DONE;
      }
      if ((d1[2] <= 0.0) && (d3[5] <= 0.0)) {   /* Check for point 2. */
        *nvxs   = 1;
        irs[0]  = irs[1];
        jrs[0]  = jrs[1];
        als[0]  = d2[1];
        zsol[0] = y[1];
        zsol[1] = y[5];
        zsol[2] = y[9];
        *dstsq  = del[5];
        y[0]    = y[1];
        y[4]    = y[5];
        y[8]    = y[9];
        del[0]  = del[5];
        goto DONE;
      }
      if ((d1[4] <= 0.0) && (d2[5] <= 0.0)) {   /* Check for point 3. */
        *nvxs   = 1;
        irs[0]  = irs[2];
        jrs[0]  = jrs[2];
        als[0]  = d3[3];
        zsol[0] = y[2];
        zsol[1] = y[6];
        zsol[2] = y[10];
        *dstsq  = del[10];
        y[0]    = y[2];
        y[4]    = y[6];
        y[8]    = y[10];
        del[0]  = del[10];
        goto DONE;
      }
      if ((d1[6]<=0.0)&&(d2[5]>0.0)&&(d3[5]>0.0)){  /* Check line 23. */
        *nvxs   = 2;
        irs[0]  = irs[2];
        jrs[0]  = jrs[2];
        sum = d2[5] + d3[5];
        als[1]  = d2[5] / sum;
        als[0]  = 1.0 - als[1];
        zsol[0] = y[2]  + als[1] * (y[1] - y[2]);
        zsol[1] = y[6]  + als[1] * (y[5] - y[6]);
        zsol[2] = y[10] + als[1] * (y[9] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[0]    = y[2];
        y[4]    = y[6];
        y[8]    = y[10];
        del[4]  = del[9];
        del[0]  = del[10];
        goto DONE;
      }
      goto BACKUP;  /* Go for the backup procedure; without new di[]. */
    case 4:                                   /* Case of four points. */
      d2[2] = del[0] - del[4];    /* Check the optimality of point 1. */
      d3[4] = del[0] - del[8];
      d4[8] = del[0] - del[12];
      if ((d2[2] <= 0.0) && (d3[4] <= 0.0) && (d4[8] <= 0.0)) {
        *nvxs   = 1;
        als[0]  = d1[0];
        zsol[0] = y[0];
        zsol[1] = y[4];
        zsol[2] = y[8];
        *dstsq  = del[0];
        goto DONE;
      }
      e132   = del[4] - del[9];   /* Check the optimality of line 12. */
      e142   = del[4] - del[13];
      d1[2]  = del[5] - del[4];
      d3[6]  = d1[2] * d3[4] + d2[2] * e132;
      d4[11] = d1[2] * d4[8] + d2[2] * e142;
      if ((d1[2]>0.0)&&(d2[2]>0.0)&&(d3[6]<=0.0)&&(d4[11]<=0.0)) {
        *nvxs   = 2;
        sum     = d1[2] + d2[2];
        als[0]  = d1[2] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[1] + als[0] * (y[0] - y[1]);
        zsol[1] = y[5] + als[0] * (y[4] - y[5]);
        zsol[2] = y[9] + als[0] * (y[8] - y[9]);
        *dstsq  = vdotc(3, zsol, zsol);
        goto DONE;
      }
      e123   = del[8]  - del[9];  /* Check the optimality of line 13. */
      e143   = del[8]  - del[14];
      d1[4]  = del[10] - del[8];
      d2[6]  = d1[4] * d2[2] + d3[4] * e123;
      d4[12] = d1[4] * d4[8] + d3[4] * e143;
      if ((d1[4]>0.0)&&(d2[6]<=0.0)&&(d3[4]>0.0)&&(d4[12]<=0.0)) {
        *nvxs   = 2;
        irs[1]  = irs[2];
        jrs[1]  = jrs[2];
        sum = d1[4] + d3[4];
        als[0]  = d1[4] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[2]  + als[0] * (y[0] - y[2]);
        zsol[1] = y[6]  + als[0] * (y[4] - y[6]);
        zsol[2] = y[10] + als[0] * (y[8] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[1]    = y[2];
        y[5]    = y[6];
        y[9]    = y[10];
        del[4]  = del[8];
        del[5]  = del[10];
        goto DONE;
      }
      d2[5]  = del[10] - del[9]; /* Check the optimality of face 123. */
      d3[5]  = del[5]  - del[9];
      e213   = -e123;
      d1[6]  = d2[5] * d1[2] + d3[5] * e213;
      d4[14] = d1[6] * d4[8] + d2[6] * e142 + d3[6] * e143;
      if ((d1[6]>0.0)&&(d2[6]>0.0)&&(d3[6]>0.0)&&(d4[14]<=0.0)) {
        *nvxs   = 3;
        sum = d1[6] + d2[6] + d3[6];
        als[0]  = d1[6] / sum;
        als[1]  = d2[6] / sum;
        als[2]  = 1.0 - als[0] - als[1];
        zsol[0] = y[2]  + als[0] * (y[0] - y[2] )
                        + als[1] * (y[1] - y[2] );
        zsol[1] = y[6]  + als[0] * (y[4] - y[6] )
                        + als[1] * (y[5] - y[6] );
        zsol[2] = y[10] + als[0] * (y[8] - y[10])
                        + als[1] * (y[9] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        goto DONE;
      }
      e124   = del[12] - del[13]; /* Check the optimality of line 14. */
      e134   = del[12] - del[14];
      d1[8]  = del[15] - del[12];
      d2[11] = d1[8] * d2[2] + d4[8] * e124;
      d3[12] = d1[8] * d3[4] + d4[8] * e134;
      if ((d1[8]>0.0)&&(d2[11]<=0.0)&&(d3[12]<=0.0)&&(d4[8]>0.0)) {
        *nvxs   = 2;
        irs[1]  = irs[3];
        jrs[1]  = jrs[3];
        sum = d1[8] + d4[8];
        als[0]  = d1[8] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[3]  + als[0] * (y[0] - y[3]);
        zsol[1] = y[7]  + als[0] * (y[4] - y[7]);
        zsol[2] = y[11] + als[0] * (y[8] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[1]    = y[3];
        y[5]    = y[7];
        y[9]    = y[11];
        del[4]  = del[12];
        del[5]  = del[15];
        goto DONE;
      }
      d2[9]  = del[15] - del[13];/* Check the optimality of face 124. */
      d4[9]  = del[5]  - del[13];
      e214   = -e124;
      d1[11] = d2[9]  * d1[2] + d4[9]  * e214;
      d3[14] = d1[11] * d3[4] + d2[11] * e132 + d4[11] * e134;
      if ((d1[11]>0.0)&&(d2[11]>0.0)&&(d3[14]<=0.0)&&(d4[11]>0.0)) {
        *nvxs   = 3;
        irs[2]  = irs[3];
        jrs[2]  = jrs[3];
        sum = d1[11] + d2[11] + d4[11];
        als[0]  = d1[11] / sum;
        als[1]  = d2[11] / sum;
        als[2]  = 1.0 - als[0] - als[1];
        zsol[0] = y[3]  + als[0] * (y[0] - y[3] )
                        + als[1] * (y[1] - y[3] );
        zsol[1] = y[7]  + als[0] * (y[4] - y[7] )
                        + als[1] * (y[5] - y[7] );
        zsol[2] = y[11] + als[0] * (y[8] - y[11])
                        + als[1] * (y[9] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[2]    = y[3];
        y[6]    = y[7];
        y[10]   = y[11];
        del[8]  = del[12];
        del[9]  = del[13];
        del[10] = del[15];
        goto DONE;
      }
      d3[10] = del[15] - del[14];/* Check the optimality of face 134. */
      d4[10] = del[10] - del[14];
      e314   = -e134;
      d1[12] = d3[10] * d1[4] + d4[10] * e314;
      d2[14] = d1[12] * d2[2] + d3[12] * e123 + d4[12] * e124;
      if ((d1[12]>0.0)&&(d2[14]<=0.0)&&(d3[12]>0.0)&&(d4[12]>0.0)) {
        *nvxs   = 3;
        irs[1]  = irs[3];
        jrs[1]  = jrs[3];
        sum = d1[12] + d3[12] + d4[12];
        als[0]  = d1[12] / sum;
        als[2]  = d3[12] / sum;
        als[1]  = 1.0 - als[0] - als[2];
        zsol[0] = y[3]  + als[0] * (y[0]  - y[3] )
                        + als[2] * (y[2]  - y[3] );
        zsol[1] = y[7]  + als[0] * (y[4]  - y[7] )
                        + als[2] * (y[6]  - y[7] );
        zsol[2] = y[11] + als[0] * (y[8]  - y[11])
                        + als[2] * (y[10] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[1]    = y[3];
        y[5]    = y[7];
        y[9]    = y[11];
        del[4]  = del[12];
        del[5]  = del[15];
        del[9]  = del[14];
        goto DONE;
      }
      e243   = del[9] - del[14];/* Check the hull of all four points. */
      d4[13] = d2[5]  * d4[9] + d3[5]  * e243;
      e234   = del[13] - del[14];
      d3[13] = d2[9]  * d3[5] + d4[9]  * e234;
      e324   = -e234;
      d2[13] = d3[10] * d2[5] + d4[10] * e324;
      d1[14] = d2[13] * d1[2] + d3[13] * e213 + d4[13] * e214;
      if ((d1[14]>0.0)&&(d2[14]>0.0)&&(d3[14]>0.0)&&(d4[14]>0.0)) {
        sum = d1[14] + d2[14] + d3[14] + d4[14];
        als[0]  = d1[14] / sum;
        als[1]  = d2[14] / sum;
        als[2]  = d3[14] / sum;
        als[3]  = 1.0 - als[0] - als[1] - als[2];
        zsol[0] = als[0] * y[0]  + als[1] * y[1]
                + als[2] * y[2]  + als[3] * y[3];
        zsol[1] = als[0] * y[4]  + als[1] * y[5]
                + als[2] * y[6]  + als[3] * y[7];
        zsol[2] = als[0] * y[8]  + als[1] * y[9]
                + als[2] * y[10] + als[3] * y[11];
        *dstsq  = vdotc(3, zsol, zsol);
      }
      if((d1[2]<=0.0)&&(d3[5]<=0.0)&&(d4[9]<=0.0)){ /* Check point 2. */
        *nvxs   = 1;
        irs[0]  = irs[1];
        jrs[0]  = jrs[1];
        als[0]  = d2[1];
        zsol[0] = y[1];
        zsol[1] = y[5];
        zsol[2] = y[9];
        *dstsq  = del[5];
        y[0]    = y[1];
        y[4]    = y[5];
        y[8]    = y[9];
        del[0]  = del[5];
        goto DONE;
      }
      if((d1[4]<=0.0)&&(d2[5]<=0.0)&&(d4[10]<=0.0)){ /* Check point 3.*/
        *nvxs   = 1;
        irs[0]  = irs[2];
        jrs[0]  = jrs[2];
        als[0]  = d3[3];
        zsol[0] = y[2];
        zsol[1] = y[6];
        zsol[2] = y[10];
        *dstsq  = del[10];
        y[0]    = y[2];
        y[4]    = y[6];
        y[8]    = y[10];
        del[0]  = del[10];
        goto DONE;
      }
      if((d1[8]<=0.0)&&(d2[9]<=0.0)&&(d3[10]<=0.0)){ /* Check point 4.*/
        *nvxs   = 1;
        irs[0]  = irs[3];
        jrs[0]  = jrs[3];
        als[0]  = d4[7];
        zsol[0] = y[3];
        zsol[1] = y[7];
        zsol[2] = y[11];
        *dstsq  = del[15];
        y[0]    = y[3];
        y[4]    = y[7];
        y[8]    = y[11];
        del[0]  = del[15];
        goto DONE;
      }
      if ((d1[6] <= 0.0) && (d2[5] > 0.0) && (d3[5] > 0.0) &&
         (d4[13] <= 0.0)) {       /* Check the optimality of line 23. */
        *nvxs   = 2;
        irs[0]  = irs[2];
        jrs[0]  = jrs[2];
        sum = d2[5] + d3[5];
        als[1]  = d2[5] / sum;
        als[0]  = 1.0 - als[1];
        zsol[0] = y[2]  + als[1] * (y[1] - y[2]);
        zsol[1] = y[6]  + als[1] * (y[5] - y[6]);
        zsol[2] = y[10] + als[1] * (y[9] - y[10]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[0]    = y[2];
        y[4]    = y[6];
        y[8]    = y[10];
        del[4]  = del[9];
        del[0]  = del[10];
        goto DONE;
      }
      if ((d1[11] <= 0.0) && (d2[9] > 0.0) && (d3[13] <= 0.0) &&
          (d4[9] > 0.0)) {        /* Check the optimality of line 24. */
        *nvxs   = 2;
        irs[0]  = irs[3];
        jrs[0]  = jrs[3];
        sum = d2[9] + d4[9];
        als[1]  = d2[9] / sum;
        als[0]  = 1.0 - als[1];
        zsol[0] = y[3]  + als[1] * (y[1] - y[3]);
        zsol[1] = y[7]  + als[1] * (y[5] - y[7]);
        zsol[2] = y[11] + als[1] * (y[9] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[0]    = y[3];
        y[4]    = y[7];
        y[8]    = y[11];
        del[4]  = del[13];
        del[0]  = del[15];
        goto DONE;
      }
      if ((d1[12] <= 0.0) && (d2[13] <= 0.0) && (d3[10] > 0.0) &&
          (d4[10] > 0.0)) {       /* Check the optimality of line 34. */
        *nvxs   = 2;
        irs[0]  = irs[2];
        irs[1]  = irs[3];
        jrs[0]  = jrs[2];
        jrs[1]  = jrs[3];
        sum = d3[10] + d4[10];
        als[0]  = d3[10] / sum;
        als[1]  = 1.0 - als[0];
        zsol[0] = y[3]  + als[0] * (y[2]  - y[3]);
        zsol[1] = y[7]  + als[0] * (y[6]  - y[7]);
        zsol[2] = y[11] + als[0] * (y[10] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[0]    = y[2];
        y[4]    = y[6];
        y[8]    = y[10];
        y[1]    = y[3];
        y[5]    = y[7];
        y[9]    = y[11];
        del[0]  = del[10];
        del[4]  = del[14];
        del[5]  = del[15];
        goto DONE;
      }
      if ((d1[14] <= 0.0) && (d2[13] > 0.0) && (d3[13] > 0.0) &&
          (d4[13] > 0.0)) {      /* Check the optimality of face 234. */
        *nvxs   = 3;
        irs[0]  = irs[3];
        jrs[0]  = jrs[3];
        sum = d2[13] + d3[13] + d4[13];
        als[1]  = d2[13] / sum;
        als[2]  = d3[13] / sum;
        als[0]  = 1.0 - als[1] - als[2];
        zsol[0] = y[3]  + als[1] * (y[1]  - y[3] )
                        + als[2] * (y[2]  - y[3] );
        zsol[1] = y[7]  + als[1] * (y[5]  - y[7] )
                        + als[2] * (y[6]  - y[7] );
        zsol[2] = y[11] + als[1] * (y[9]  - y[11])
                        + als[2] * (y[10] - y[11]);
        *dstsq  = vdotc(3, zsol, zsol);
        y[0]    = y[3];
        y[4]    = y[7];
        y[8]    = y[11];
        del[0]  = del[15];
        del[4]  = del[13];
        del[8]  = del[14];
        goto DONE;
      }
      goto BACKUP;  /* Go for the backup procedure; without new di[]. */
    }
  }

/* The backup procedure begins here. */
  switch (*nvxs) {
  case 1:                                  /* Case of a single point. */
    break;
  case 2:                                      /* Case of two points. */
    d2[2]  = del[0]  - del[4];
    d1[2]  = del[5]  - del[4];
    break;
  case 3:                                    /* Case of three points. */
    d2[2]  = del[0]  - del[4];
    d3[4]  = del[0]  - del[8];
    e132   = del[4]  - del[9];
    d1[2]  = del[5]  - del[4];
    d3[6]  = d1[2] * d3[4] + d2[2] * e132;
    e123   = del[8]  - del[9];
    d1[4]  = del[10] - del[8];
    d2[6]  = d1[4] * d2[2] + d3[4] * e123;
    e213   = -e123;
    d2[5]  = del[10] - del[9];
    d3[5]  = del[5]  - del[9];
    d1[6]  = d2[5] * d1[2] + d3[5] * e213;
    break;
  case 4:                                     /* Case of four points. */
    d2[2]  = del[0]  - del[4];
    d3[4]  = del[0]  - del[8];
    d4[8]  = del[0]  - del[12];
    e132   = del[4]  - del[9];
    e142   = del[4]  - del[13];
    d1[2]  = del[5]  - del[4];
    d3[6]  = d1[2] * d3[4] + d2[2] * e132;
    d4[11] = d1[2] * d4[8] + d2[2] * e142;
    e123   = del[8]  - del[9];
    e143   = del[8]  - del[14];
    d1[4]  = del[10] - del[8];
    d2[6]  = d1[4] * d2[2] + d3[4] * e123;
    d4[12] = d1[4] * d4[8] + d3[4] * e143;
    d2[5]  = del[10] - del[9];
    d3[5]  = del[5]  - del[9];
    e213   = -e123;
    d1[6]  = d2[5] * d1[2] + d3[5] * e213;
    d4[14] = d1[6] * d4[8] + d2[6] * e142 + d3[6] * e143;
    e124   = del[12] - del[13];
    e134   = del[12] - del[14];
    d1[8]  = del[15] - del[12];
    d2[11] = d1[8] * d2[2] + d4[8] * e124;
    d3[12] = d1[8] * d3[4] + d4[8] * e134;
    d2[9]  = del[15] - del[13];
    d4[9]  = del[5]  - del[13];
    e214   = -e124;
    d1[11] = d2[9]  * d1[2] + d4[9]  * e214;
    d3[14] = d1[11] * d3[4] + d2[11] * e132 + d4[11] * e134;
    d3[10] = del[15] - del[14];
    d4[10] = del[10] - del[14];
    e314   = -e134;
    d1[12] = d3[10] * d1[4] + d4[10] * e314;
    d2[14] = d1[12] * d2[2] + d3[12] * e123 + d4[12] * e124;
    e243   = del[9]  - del[14];
    d4[13] = d2[5]  * d4[9] + d3[5]  * e243;
    e234   = del[13] - del[14];
    d3[13] = d2[9]  * d3[5] + d4[9]  * e234;
    e324   = -e234;
    d2[13] = d3[10] * d2[5] + d4[10] * e324;
    d1[14] = d2[13] * d1[2] + d3[13] * e213 + d4[13] * e214;
    break;
  }

BACKUP:;        /* If the di[] values are already available, then ... */
  switch (*nvxs) {
  case 1:                                  /* Case of a single point. */
    *dstsq   = del[0];
    als[0]   = d1[0];
    zsol[0]  = y[0];
    zsol[1]  = y[4];
    zsol[2]  = y[8];
    *lbackup = TRUE;
    goto DONE;
  case 2:                                      /* Case of two points. */
    *dstsq   = del[0];                              /* Check point 1. */
    nvxsd    = 1;
    als[0]   = d1[0];
    zsol[0]  = y[0];
    zsol[1]  = y[4];
    zsol[2]  = y[8];
    iord[0]  = 1;
    if ((d1[2] > 0.0) && (d2[2] > 0.0)) {   /* Check line segment 12. */
      sum       = d1[2] + d2[2];
      alsd[0]   = d1[2] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[1]  + alsd[0] * (y[0]  - y[1]);
      zsold[1]  = y[5]  + alsd[0] * (y[4]  - y[5]);
      zsold[2]  = y[9]  + alsd[0] * (y[8]  - y[9]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
      }
    }
    if (del[5] < *dstsq) {                          /* Check point 2. */
      *dstsq   = del[5];
      nvxsd    = 1;
      als[0]   = d2[1];
      zsol[0]  = y[1];
      zsol[1]  = y[5];
      zsol[2]  = y[9];
      iord[0]  = 2;
    }
    break;
  case 3:                                    /* Case of three points. */
    *dstsq   = del[0];                              /* Check point 1. */
    nvxsd    = 1;
    als[0]   = d1[0];
    zsol[0]  = y[0];
    zsol[1]  = y[4];
    zsol[2]  = y[8];
    iord[0]  = 1;
    if ((d1[2] > 0.0) && (d2[2] > 0.0)) {   /* Check line segment 12. */
      sum       = d1[2] + d2[2];
      alsd[0]   = d1[2] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[1]  + alsd[0] * (y[0]  - y[1]);
      zsold[1]  = y[5]  + alsd[0] * (y[4]  - y[5]);
      zsold[2]  = y[9]  + alsd[0] * (y[8]  - y[9]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
      }
    }
    if ((d1[4] > 0.0) && (d3[4] > 0.0)) {   /* Check line segment 13. */
      sum       = d1[4] + d3[4];
      alsd[0]   = d1[4] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[2]  + alsd[0] * (y[0]  - y[2]);
      zsold[1]  = y[6]  + alsd[0] * (y[4]  - y[6]);
      zsold[2]  = y[10] + alsd[0] * (y[8]  - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 3;
      }
    }
    if ((d1[6]>0.0) && (d2[6]>0.0) && (d3[6]>0.0)){/* Check face 123. */
      sum       = d1[6] + d2[6] + d3[6];
      alsd[0]   = d1[6] / sum;
      alsd[1]   = d2[6] / sum;
      alsd[2]   = 1.0 - als[0] - als[1];
      zsold[0]  = y[2]  + alsd[0] * (y[0] - y[2] )
                        + alsd[1] * (y[1] - y[2] );
      zsold[1]  = y[6]  + alsd[0] * (y[4] - y[6] )
                        + alsd[1] * (y[5] - y[6] );
      zsold[2]  = y[10] + alsd[0] * (y[8] - y[10])
                        + alsd[1] * (y[9] - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 3;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
        iord[2] = 3;
      }
    }
    if (del[5] < *dstsq) {                          /* Check point 2. */
      nvxsd     = 1;
      *dstsq    = del[5];
      als[0]    = d2[1];
      zsol[0]   = y[1];
      zsol[1]   = y[5];
      zsol[2]   = y[9];
      iord[0]   = 2;
    }
    if (del[10] < *dstsq) {                         /* Check point 3. */
      nvxsd     = 1;
      *dstsq    = del[10];
      als[0]    = d3[3];
      zsol[0]   = y[2];
      zsol[1]   = y[6];
      zsol[2]   = y[10];
      iord[0]   = 3;
    }
    if ((d2[5] > 0.0) && (d3[5] > 0.0)) {   /* Check line segment 23. */
      sum       = d2[5] + d3[5];
      alsd[1]   = d2[5] / sum;
      alsd[0]   = 1.0 - alsd[1];
      zsold[0]  = y[2]  + alsd[1] * (y[1]  - y[2]);
      zsold[1]  = y[6]  + alsd[1] * (y[5]  - y[6]);
      zsold[2]  = y[10] + alsd[1] * (y[9]  - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 3;
        iord[1] = 2;
      }
    }
    break;
  case 4:                                     /* Case of four points. */
    *dstsq   = del[0];                              /* Check point 1. */
    nvxsd    = 1;
    als[0]   = d1[0];
    zsol[0]  = y[0];
    zsol[1]  = y[4];
    zsol[2]  = y[8];
    iord[0]  = 1;
    if ((d1[2] > 0.0) && (d2[2] > 0.0)) {   /* Check line segment 12. */
      sum       = d1[2] + d2[2];
      alsd[0]   = d1[2] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[1]  + alsd[0] * (y[0]  - y[1]);
      zsold[1]  = y[5]  + alsd[0] * (y[4]  - y[5]);
      zsold[2]  = y[9]  + alsd[0] * (y[8]  - y[9]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
      }
    }
    if ((d1[4] > 0.0) && (d3[4] > 0.0)) {   /* Check line segment 13. */
      sum       = d1[4] + d3[4];
      alsd[0]   = d1[4] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[2]  + alsd[0] * (y[0]  - y[2]);
      zsold[1]  = y[6]  + alsd[0] * (y[4]  - y[6]);
      zsold[2]  = y[10] + alsd[0] * (y[8]  - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 3;
      }
    }
    if ((d1[6]>0.0) && (d2[6]>0.0) && (d3[6]>0.0)){/* Check face 123. */
      sum       = d1[6] + d2[6] + d3[6];
      alsd[0]   = d1[6] / sum;
      alsd[1]   = d2[6] / sum;
      alsd[2]   = 1.0 - als[0] - als[1];
      zsold[0]  = y[2]  + alsd[0] * (y[0] - y[2] )
                        + alsd[1] * (y[1] - y[2] );
      zsold[1]  = y[6]  + alsd[0] * (y[4] - y[6] )
                        + alsd[1] * (y[5] - y[6] );
      zsold[2]  = y[10] + alsd[0] * (y[8] - y[10])
                        + alsd[1] * (y[9] - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 3;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
        iord[2] = 3;
      }
    }
    if ((d1[8] > 0.0) && (d4[8] > 0.0)) {   /* Check line segment 14. */
      sum       = d1[8] + d4[8];
      alsd[0]   = d1[8] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[3]  + alsd[0] * (y[0]  - y[3]);
      zsold[1]  = y[7]  + alsd[0] * (y[4]  - y[7]);
      zsold[2]  = y[11] + alsd[0] * (y[8]  - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 4;
      }
    }
    if ((d1[11]>0.0)&&(d2[11]>0.0)&&(d4[11]>0.0)){ /* Check face 124. */
      sum       = d1[11] + d2[11] + d4[11];
      alsd[0]   = d1[11] / sum;
      alsd[1]   = d2[11] / sum;
      alsd[2]   = 1.0 - als[0] - als[1];
      zsold[0]  = y[3]  + alsd[0] * (y[0] - y[3] )
                        + alsd[1] * (y[1] - y[3] );
      zsold[1]  = y[7]  + alsd[0] * (y[4] - y[7] )
                        + alsd[1] * (y[5] - y[7] );
      zsold[2]  = y[11] + alsd[0] * (y[8] - y[11])
                        + alsd[1] * (y[9] - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 3;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
        iord[2] = 4;
      }
    }
    if ((d1[12]>0.0)&&(d3[12]>0.0)&&(d4[12]>0.0)){ /* Check face 134. */
      sum       = d1[12] + d3[12] + d4[12];
      alsd[0]   = d1[11] / sum;
      alsd[1]   = d3[11] / sum;
      alsd[2]   = 1.0 - als[0] - als[1];
      zsold[0]  = y[3]  + alsd[0] * (y[0]  - y[3] )
                        + alsd[2] * (y[2]  - y[3] );
      zsold[1]  = y[7]  + alsd[0] * (y[4]  - y[7] )
                        + alsd[2] * (y[6]  - y[7] );
      zsold[2]  = y[11] + alsd[0] * (y[8]  - y[11])
                        + alsd[2] * (y[10] - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 3;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 4;
        iord[2] = 3;
      }
    }
    if ((d1[14] > 0.0) && (d2[14] > 0.0) && (d3[14] > 0.0) &&
        (d4[14] > 0.0)) {       /* Check the hull of all four points. */
      sum       = d1[14] + d2[14] + d3[14] + d4[14];
      alsd[0]   = d1[14] / sum;
      alsd[1]   = d2[14] / sum;
      alsd[2]   = d3[14] / sum;
      alsd[3]   = 1.0 - alsd[0] - alsd[1] - alsd[2];
      zsold[0]  = alsd[0] * y[0]  + alsd[1] * y[1] 
                + alsd[2] * y[2]  + alsd[3] * y[3];
      zsold[1]  = alsd[0] * y[4]  + alsd[1] * y[5] 
                + alsd[2] * y[6]  + alsd[3] * y[7];
      zsold[2]  = alsd[0] * y[8]  + alsd[1] * y[9]
                + alsd[2] * y[10] + alsd[3] * y[11];
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 4;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        als[3]  = alsd[3];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 1;
        iord[1] = 2;
        iord[2] = 3;
        iord[3] = 4;
      }
    }
    if (del[5] < *dstsq) {                          /* Check point 2. */
      nvxsd     = 1;
      *dstsq    = del[5];
      als[0]    = d2[1];
      zsol[0]   = y[1];
      zsol[1]   = y[5];
      zsol[2]   = y[9];
      iord[0]   = 2;
    }
    if (del[10] < *dstsq) {                         /* Check point 3. */
      nvxsd     = 1;
      *dstsq    = del[10];
      als[0]    = d3[3];
      zsol[0]   = y[2];
      zsol[1]   = y[6];
      zsol[2]   = y[10];
      iord[0]   = 3;
    }
    if (del[15] < *dstsq) {                         /* Check point 4. */
      nvxsd     = 1;
      *dstsq    = del[15];
      als[0]    = d4[7];
      zsol[0]   = y[3];
      zsol[1]   = y[7];
      zsol[2]   = y[11];
      iord[0]   = 4;
    }
    if ((d2[5] > 0.0) && (d3[5] > 0.0)) {   /* Check line segment 23. */
      sum       = d2[5] + d3[5];
      alsd[1]   = d2[5] / sum;
      alsd[0]   = 1.0 - alsd[1];
      zsold[0]  = y[2]  + alsd[1] * (y[1]  - y[2]);
      zsold[1]  = y[6]  + alsd[1] * (y[5]  - y[6]);
      zsold[2]  = y[10] + alsd[1] * (y[9]  - y[10]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 3;
        iord[1] = 2;
      }
    }
    if ((d2[9] > 0.0) && (d4[9] > 0.0)) {   /* Check line segment 24. */
      sum       = d2[9] + d4[9];
      alsd[1]   = d2[9] / sum;
      alsd[0]   = 1.0 - alsd[1];
      zsold[0]  = y[3]  + alsd[1] * (y[1]  - y[3]);
      zsold[1]  = y[7]  + alsd[1] * (y[5]  - y[7]);
      zsold[2]  = y[11] + alsd[1] * (y[9]  - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 4;
        iord[1] = 2;
      }
    }
    if ((d3[10] > 0.0) && (d4[10] > 0.0)) { /* Check line segment 34. */
      sum       = d3[10] + d4[10];
      alsd[0]   = d3[10] / sum;
      alsd[1]   = 1.0 - alsd[0];
      zsold[0]  = y[3]  + alsd[1] * (y[2]  - y[3]);
      zsold[1]  = y[7]  + alsd[1] * (y[6]  - y[7]);
      zsold[2]  = y[11] + alsd[1] * (y[10] - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 2;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 3;
        iord[1] = 4;
      }
    }
    if ((d2[13]>0.0)&&(d3[13]>0.0)&&(d4[13]>0.0)) {/* Check face 234. */
      sum       = d2[13] + d3[13] + d4[13];
      alsd[1]   = d2[13] / sum;
      alsd[2]   = d3[13] / sum;
      alsd[0]   = 1.0 - als[1] - als[2];
      zsold[0]  = y[3]  + alsd[1] * (y[1]  - y[3] )
                        + alsd[2] * (y[2]  - y[3] );
      zsold[1]  = y[7]  + alsd[1] * (y[5]  - y[7] )
                        + alsd[2] * (y[6]  - y[7] );
      zsold[2]  = y[11] + alsd[1] * (y[9]  - y[11])
                        + alsd[2] * (y[10] - y[11]);
      dstsqd    = vdotc(3, zsold, zsold);
      if (dstsqd < *dstsq) {
        *dstsq  = dstsqd;
        nvxsd   = 3;
        als[0]  = alsd[0];
        als[1]  = alsd[1];
        als[2]  = alsd[2];
        zsol[0] = zsold[0];
        zsol[1] = zsold[1];
        zsol[2] = zsold[2];
        iord[0] = 4;
        iord[1] = 2;
        iord[2] = 3;
      }
    }
    break;
  }

/* Perform the final reordering. */
  for (k=0; k<*nvxs; k++) {
    irsd[k] = irs[k];
    jrsd[k] = jrs[k];
    yd[  k] = y[  k];
    yd[4+k] = y[4+k];
    yd[8+k] = y[8+k];
    for (l=0; l<k; l++) {
      kl = 4 * k + l;
      deld[kl] = del[kl];
      kl = 4 * l + k;
      deld[kl] = del[kl];
    }
  }
  *nvxs = nvxsd;
  for (k=0; k<*nvxs; k++) {
    kk = iord[k];
    irs[k] = irsd[kk];
    jrs[k] = jrsd[kk];
    y[  k] = yd[  kk];
    y[4+k] = yd[4+kk];
    y[8+k] = yd[8+kk];
    for (l=0; l<k; l++) {
     del[k*4+l] = deld[kk*4+iord[k]];
    }
  }
  *lbackup = TRUE;
DONE:;
  return;
}

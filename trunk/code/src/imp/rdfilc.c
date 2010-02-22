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
/* rdfilc-01 Jan 00:17 Mar 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Read an array of analysis results for a named item from an IMP
|     post-processing file.
|
|     Access:
|       (void) rdfilc(int lun, enum Outtyp outtyp, Word name, int *last,
|         real *t, enum Rectyp *kind, int *mxdata, real *data);
|     int          lun,    i-Logical unit number for reading the file.
|     enum Outtyp  outtyp, i-Type of data sought, (OT_POS, etc.).
|     Word         name,   i-Name of the item for which data is sought.
|     int         *last,   o-Number of time values (sets of data) found.
|     real         t[last],o-Array of time values for the data found.
|     enum Rectyp *kind,   o-Type of the named item, (JOINT, etc.).
|     int         *mxdata, o-Number of components found at each time.
|     real   data[last,12],o-Components of data found at all times.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       It is assumed that a file has been previously written by IMP
|     List, Plot, or Store requests, and that the file is still open and
|     assigned to FILE *streams[lun].
*
*     History:
*     01 Jan 00:JJU-Original.
*     12 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void rdfilc(int lun, enum Outtyp outtyp, Word name, int *last,
    real *t, enum Rectyp *kind, int *mxdata, real *data)
#else
  void rdfilc(lun, outtyp, name, last, t, kind, mxdata, data)
  int          lun;
  enum Outtyp  outtyp;
  Word         name;
  int         *last;
  real        *t;
  enum Rectyp *kind;
  int         *mxdata;
  real        *data;
#endif
{
  Word   word1, word2;
  char   format[] = "%5s%5s%5i%20le%20le%20le";
  double values[3];
  int    i, iword, n, ngoto;
  real   time;

  rewind(streams[lun]);
  n = 0;
  *kind = 0;
  *mxdata = 0;
  ngoto = -1;
  while (!feof(streams[lun])) {
    fscanf(streams[lun], format, word1, word2, &iword, &values[0], 
      &values[1], &values[2]);
    if (ferror(streams[lun])) {
      textc("*** Error reading file ", FALSE);
      for (i=0; i<3; i++) {
        if (lun == lunfil[i]) {
          textc(idfile[i], FALSE);
          break;
        }
      }
      textc(" ***", TRUE);
      break;
    }
    if (strcmp(word1, "END") == 0) {
      ngoto = -1;
    } else {
      if (ngoto < 0) {
        if (strcmp(word1, "TIME") == 0) {
          time = values[0];
          for (i=0; i<12; i++) {
            data[12*n+i] = 0.0;
          }
          ngoto = 0;
        }
      } else if (ngoto == 0) {
        switch (outtyp) {
        case OT_VAL:
          if (strcmp(word1, "VAL.") == 0) ngoto = 1;
          break;
        case OT_POS:
          if (strcmp(word1, "POS.") == 0) ngoto = 1;
          break;
        case OT_VEL:
          if (strcmp(word1, "VEL.") == 0) ngoto = 1;
          break;
        case OT_ACC:
          if (strcmp(word1, "ACC.") == 0) ngoto = 1;
          break;
        case OT_FORC:
          if (strcmp(word1, "FORC") == 0) ngoto = 1;
        }
      } else {
        if (strcmp(name, word2) == 0) {
          if (strcmp(word1, "VAL.") == 0) {
            *kind = VALUE;
          } else if (strcmp(word1, "BODY") == 0) {
            *kind = BODY;
          } else if (strcmp(word1, "JNT.") == 0) {
            *kind = JOINT;
          } else if (strcmp(word1, "PNT.") == 0) {
            *kind = POINT;
          } else if (strcmp(word1, "SPG.") == 0) {
            *kind = SPRING;
          } else if (strcmp(word1, "DMP.") == 0) {
            *kind = DAMPER;
          } else if (strcmp(word1, "FORC") == 0) {
            *kind = FORCE;
          } else if (strcmp(word1, "TORQ") == 0) {
            *kind = TORQUE;
          }
          *mxdata = iword;
          for (i=0; i<iword; i++) {
            data[12*n+i] = values[i];
          }
          if (*kind == BODY) {
            *mxdata = 6;
            fscanf(streams[lun], format, word1, word2, &iword, 
              &values[0], &values[1], &values[2]);
            for (i=0; i<3; i++) {
              data[12*n+i+3] = values[i];
            }
            if (outtyp == OT_POS) {
              *mxdata = 12;
              fscanf(streams[lun], format, word1, word2, &iword, 
                &values[0], &values[1], &values[2]);
              for (i=0; i<3; i++) {
                data[12*n+i+6] = values[i];
              }
              fscanf(streams[lun], format, word1, word2, &iword, 
                &values[0], &values[1], &values[2]);
              for (i=0; i<3; i++) {
                data[12*n+i+9] = values[i];
              }
            }
          } else if (*kind == JOINT) {
            if (outtyp == OT_POS) {
              if (*mxdata > 3) {
                fscanf(streams[lun], format, word1, word2, &iword, 
                  &values[0], &values[1], &values[2]);
                for (i=0; i<3; i++) {
                  data[12*n+i+3] = values[i];
                }
              }
              if (*mxdata > 6) {
                fscanf(streams[lun], format, word1, word2, &iword, 
                  &values[0], &values[1], &values[2]);
                for (i=0; i<3; i++) {
                  data[12*n+i+6] = values[i];
                }
              }
            } else if (outtyp == OT_FORC) {
              *mxdata = 6;
              fscanf(streams[lun], format, word1, word2, &iword, 
                &values[0], &values[1], &values[2]);
              for (i=0; i<3; i++) {
                data[12*n+i+3] = values[i];
              }
            }
          }
          t[n] = time;
          n++;
          ngoto = -1;
        }
      }
    }
  }
  *last = n;
  rewind(streams[lun]);
  return;
}

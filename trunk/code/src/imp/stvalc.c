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
/* stvalc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Write the requested Value results on the store file.
|
|     Access:
|       (void) stvalc(Token name[], int n);
|     Token name[],i-Array of tokens containing Value names.
|     int   n,     i-Number of entries in the name[] array.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The keyboard interrupt flag is set if a Value expression results
|     in a value of RETURN.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void stvalc(Token name[], int n)
#else
  void stvalc(name, n)
  Token name[];
  int   n;
#endif
{
  Value *value;
  Word   word;
  int    i, j, lgoto, lun, m, nn;
  real   val[3];

  lun = lunfil[2];
  if (lun > 0) {
    m = 0;
    for (value=System.sysVal; value; value=value->nxtVal) {
      if (value->f == F_CONST) {
      } else if (value->f == F_TIME) {
      } else if (strlen(value->name)) {
        m++;
      }
    }
    nn = n;
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        if (strcmp(word, "all") == 0) nn += m - 1;
      }
    }
    fprintf(streams[lun]," VAL. ---- %#4i %#19.10e %#19.10e %#19.10e\n",
      nn, 0.0, 0.0, 0.0);
    for (i=0; i<n; i++) {
      if (name[i].kind == TK_CHAR) {
        strcpy(word, name[i].data.text);
        lcasec(word);
        lgoto = (strcmp(word, "all") == 0);
        for (value=System.sysVal; value; value=value->nxtVal) {
          if (value->f == F_CONST) {
          } else if (value->f == F_TIME) {
          } else if (strlen(value->name)) {
            if (lgoto) {
              vevalc(value, val);
            } else if (strcmp(value->name, name[i].data.text) == 0) {
              vevalc(value, val);
            } else {
              continue;
            }
            for (j=0; j<3; j++) {
              if (isnanc((void *) &val[j])) val[j] = UNDET;
            }
            fprintf(streams[lun],
              " VAL. %#4s    3 %#19.10e %#19.10e %#19.10e\n",
              value->name, val[0], val[1], val[2]);
            if (!lgoto) break;
          }
        }
      }
    }
  }
  return;
}

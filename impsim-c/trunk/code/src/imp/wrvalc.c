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
/* wrvalc-01 Jan 00:14 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Print the requested Value results on the output file.
|
|     Access:
|       (void) wrvalc(Token name[], int n);
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
*     10 May 00:JJU-Changed format for overflow size values.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void wrvalc(Token name[], int n)
#else
  void wrvalc(name, n)
  Token name[];
  int   n;
#endif
{
  Value *value;
  Word   nameword, word;
  char   string[16];
  int    i, j, lgoto;
  real   val[3];

  textc("", TRUE);
  textc("Value Results:", TRUE);
  textc("  Name          Value      1st Deriv      2nd Deriv", TRUE);
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
          textc("", TRUE);
          textc("  ", FALSE);
          sprintf(nameword, "%-*s\0", MAXCHR, value->name);
          textc(nameword, FALSE);
          if (qkbic()) {
            textc("         RETURN", FALSE);
          } else {
            for (j=0; j<3; j++) {
              if (isnanc((void *) &val[j])) {
                textc("           ????", FALSE);
              } else {
                if (sprintf(string, "%#15.3f", val[j]) <= 15) {
                  textc(string, FALSE);
                } else {
                  textc(" **************", FALSE);
                }
              }
            }
          }
          textc("", TRUE);
          if (!lgoto) break;
        }
      }
    }
  }
  return;
}

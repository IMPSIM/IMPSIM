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
/* datac-01 Jan 00:22 Jun 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       This routine is the extension of the IMP interpreter to receive
|     and store the data in an IMP DATA input statement.
|
|     Access:
|       (void) datac();
|
|     Error Conditions:
|       System.nerror = 2 indicates a format error in the data.
|       System.nerror = 3 indicates an unrecognized type of statement.
|
|     Comments:
|       A non-fatal warning message is issued if more data are found in
|     a data statement than expected; extra data are ignored.
|       A non-fatal warning message is issued if less data are found in
|     a data statement than expected; additional zeroes are assumed for
|     the missing data.
*
*     History:
*     01 Jan 00:JJU-Original.
*     22 Mar 03:JJU-Incorporated new itextc() function.
*     22 Mar 09:JJU-Implemented Euler parameters.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void datac()
{
  real out[3], vert[3];
  int i, nview;

/* Initialize. */
  frmatc(1, 1, TK_CHAR);
  if (System.nerror == 0) {
    lcasec(token[1].data.text);

/* Check and store data for a DATA ACCELERATION statement. */
    if (strncmp(token[1].data.text, "acceleration", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        token[3].kind = TK_REAL;
        token[3].data.word = 0.0;
      }
      frmatc(3, 1, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 4) {
        echoc();
        textc("*** Word 5 on are extra and ignored. ***", TRUE);
      }
      dacc(token[2].data.text, token[3].data.word);

/* Check and store data for a DATA BEVEL statement. */
    } else if (strncmp(token[1].data.text, "bevel", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<5; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 2, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      dbvlc(token[2].data.text, token[3].data.word, token[4].data.word);

/* Check and store data for a DATA BODY statement. */
    } else if ((strncmp(token[1].data.text, "body", MAXCHR) == 0)
            || (strncmp(token[1].data.text, "link", MAXCHR) == 0)) {
      frmatc(2, 2, TK_CHAR);
      frmatc(4, 3, TK_XYZ);
      if (ntokns < 13) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(13-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<13; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 13) {
        echoc();
        textc("*** Word 14 on are extra and ignored. ***", TRUE);
      }
      dbodyc(token[2].data.text, token[3].data.text, &token[4], 
        &token[7], &token[10]);

/* Check and store data for a DATA CAM statement. */
    } else if (strncmp(token[1].data.text, "cam", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        token[3].kind = TK_REAL;
        token[3].data.word = 0.0;
      }
      frmatc(3, 2, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      dcamc(token[2].data.text, token[3], token[4]);

/* Check and store data for a DATA CONTACT statement. */
    } else if (strncmp(token[1].data.text, "contact", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 8) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(8-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<9; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (ntokns > 8) {
        echoc();
        textc("*** Word 9 on are extra and ignored. ***", TRUE);
      }
      dcontc(token[2].data.text, token[3].data.word, token[4].data.word, 
        token[5].data.word, token[6].data.word, token[7].data.word);

/* Check and store data for a DATA CYLINDER statement. */
    } else if (strncmp(token[1].data.text, "cylinder", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dcylc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA DAMPER statement. */
    } else if (strncmp(token[1].data.text, "damper", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 7, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      ddampc(token[2].data.text, &token[3]);

/* Check and store data for a DATA DENSITY statement. */
    } else if (strncmp(token[1].data.text, "density", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        token[3].kind = TK_REAL;
        token[3].data.word = 0.0;
      }
      frmatc(3, 1, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 4) {
        echoc();
        textc("*** Word 5 on are extra and ignored. ***", TRUE);
      }
      dmprpc(token[2].data.text, token[3].data.word);

/* Check and store data for a DATA DRAW statement. */
    } else if (strncmp(token[1].data.text, "draw", MAXCHR) == 0) {
      if (ntokns < 3) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(3-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        token[2].kind = TK_REAL;
        token[2].data.word = 0.0;
      }
      frmatc(2, 1, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 3) {
        echoc();
        textc("*** Word 4 on are extra and ignored. ***", TRUE);
      }
      perspc(token[2].data.word);
      pgfitc();

/* Check and store data for a DATA FORCE statement. */
    } else if (strncmp(token[1].data.text, "force", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 7, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      dforc(token[2].data.text, &token[3]);

/* Check and store data for a DATA GEAR statement. */
    } else if (strncmp(token[1].data.text, "gear", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<5; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 2, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dgearc(token[2].data.text, token[3].data.word,
        token[4].data.word, token[5].data.word);

/* Check and store data for a DATA GRAVITY statement. */
    } else if (strncmp(token[1].data.text, "gravity", MAXCHR) == 0) {
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<5; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(2, 3, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      dgravc(token[2].data.word, token[3].data.word,token[4].data.word);

/* Check and store data for a DATA IC statement. */
    } else if (strncmp(token[1].data.text, "ic", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<17; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 14, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 17) {
        echoc();
        textc("*** Word 18 on are extra and ignored. ***", TRUE);
      }
      dic(token[2].data.text, &token[3]);

/* Check and store data for a DATA INERTIA statement. */
    } else if (strncmp(token[1].data.text, "inertia", MAXCHR) == 0) {
      frmatc(2, 2, TK_CHAR);
      if (ntokns < 10) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(10-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(4, 6, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      dinrtc(token[2].data.text, token[3].data.text, token[4].data.word, 
        token[5].data.word, token[6].data.word, token[7].data.word, 
        token[8].data.word, token[9].data.word);

/* Check and store data for a DATA MASS statement. */
    } else if (strncmp(token[1].data.text, "mass", MAXCHR) == 0) {
      frmatc(2, 2, TK_CHAR);
      frmatc(4, 1, TK_REAL);
      frmatc(5, 1, TK_XYZ);
      if (ntokns < 8) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(8-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<8; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 8) {
        echoc();
        textc("*** Word 9 on are extra and ignored. ***", TRUE);
      }
      dmassc(token[2].data.text, token[3].data.text, token[4].data.word, 
        &token[5]);

/* Check and store data for a DATA MOTION statement. */
    } else if (strncmp(token[1].data.text, "motion", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 7, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      dmotnc(token[2].data.text, &token[3]);

/* Check and store data for a DATA PAIR statement. */
    } else if (strncmp(token[1].data.text, "pair", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 7, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      djvarc(token[2].data.text, &token[3]);

/* Check and store data for a DATA POINT statement. */
    } else if (strncmp(token[1].data.text, "point", MAXCHR) == 0) {
      frmatc(2, 2, TK_CHAR);
      frmatc(4, 1, TK_XYZ);
      if (ntokns < 7) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(7-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<7; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 7) {
        echoc();
        textc("*** Word 8 on are extra and ignored. ***", TRUE);
      }
      for (i=0; i<3; i++) {
        out[i] = token[i+4].data.word;
      }
      dpntc(token[2].data.text, token[3].data.text, out);

/* Check and store data for a DATA POSITION statement. */
    } else if (strncmp(token[1].data.text, "position", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(6-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<6; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 2, TK_REAL);
      frmatc(5, 1, TK_INT);
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dpostc(token[2].data.text, token[3].data.word, token[4].data.word,
        token[5].data.number);

/* Check and store data for a DATA PRISM statement. */
    } else if (strncmp(token[1].data.text, "prism", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dprmc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA RACK statement. */
    } else if (strncmp(token[1].data.text, "rack", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<5; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 2, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      drckc(token[2].data.text, token[3].data.word, token[4].data.word);

/* Check and store data for a DATA REVOLUTE statement. */
    } else if (strncmp(token[1].data.text, "revolute", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 4, TK_XYZ);
      if (ntokns < 15) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(15-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<15; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 15) {
        echoc();
        textc("*** Word 16 on are extra and ignored. ***", TRUE);
      }
      drevc(token[2].data.text, &token[3], &token[6], &token[9], 
        &token[12]);

/* Check and store data for a DATA RIGID statement. */
    } else if (strncmp(token[1].data.text, "rigid", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      drgdc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA SCREW statement. */
    } else if (strncmp(token[1].data.text, "screw", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<4; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 1, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 4) {
        echoc();
        textc("*** Word 5 on are extra and ignored. ***", TRUE);
      }
      dscrwc(token[2].data.text, token[3].data.word);

/* Check and store data for a DATA SLOT statement. */
    } else if (strncmp(token[1].data.text, "slot", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<4; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 2, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      dsltc(token[2].data.text, token[3], token[4]);

/* Check and store data for a DATA SPHERE statement. */
    } else if (strncmp(token[1].data.text, "sphere", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 1, TK_XYZ);
      if (ntokns < 6) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(6-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<6; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dsphc(token[2].data.text, &token[3]);

/* Check and store data for a DATA SPRING statement. */
    } else if (strncmp(token[1].data.text, "spring", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<17; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 14, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 17) {
        echoc();
        textc("*** Word 18 on are extra and ignored. ***", TRUE);
      }
      dspngc(token[2].data.text, &token[3]);

/* Check and store data for a DATA TIME statement. */
    } else if (strncmp(token[1].data.text, "time", MAXCHR) == 0) {
      if (ntokns < 5) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(5-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<5; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(2, 3, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 5) {
        echoc();
        textc("*** Word 6 on are extra and ignored. ***", TRUE);
      }
      dtimec(token[2].data.word, token[3].data.word,token[4].data.word);

/* Check and store data for a DATA TORQUE statement. */
    } else if (strncmp(token[1].data.text, "torque", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<10; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      frmatc(3, 7, TK_VALUE);
      if (System.nerror) return;
      if (ntokns > 10) {
        echoc();
        textc("*** Word 11 on are extra and ignored. ***", TRUE);
      }
      dtorqc(token[2].data.text, &token[3]);

/* Check and store data for a DATA UJOINT statement. */
    } else if (strncmp(token[1].data.text, "ujoint", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dujtc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA VELOCITY statement. */
    } else if (strncmp(token[1].data.text, "velocity", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      if (ntokns < 4) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(4-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        token[3].kind = TK_REAL;
        token[3].data.word = 0.0;
      }
      frmatc(3, 1, TK_REAL);
      if (System.nerror) return;
      if (ntokns > 4) {
        echoc();
        textc("*** Word 5 on are extra and ignored. ***", TRUE);
      }
      dvelc(token[2].data.text, token[3].data.word);

/* Check and store data for a DATA VIEW statement. */
    } else if (strncmp(token[1].data.text, "view", MAXCHR) == 0) {
      if (token[2].kind == TK_INT) {
        if (token[2].data.number == 0) {
          vdirc();
        } else {
          vreadc(token[2].data.number);
          pgfitc();
        }
      } else if (token[2].kind == TK_CHAR) {
        nview = 0;
        lcasec(token[2].data.text);
        if (strncmp(token[2].data.text, "front", MAXCHR) == 0) {
          nview = -1;
        } else if (strncmp(token[2].data.text, "back", MAXCHR) == 0) {
          nview = -2;
        } else if (strncmp(token[2].data.text, "left", MAXCHR) == 0) {
          nview = -3;
        } else if (strncmp(token[2].data.text, "right",MAXCHR) == 0) {
          nview = -4;
        } else if (strncmp(token[2].data.text, "top",  MAXCHR) == 0) {
          nview = -5;
        } else if (strncmp(token[2].data.text,"bottom",MAXCHR) == 0) {
          nview = -6;
        } else if (strncmp(token[2].data.text,"isometric",MAXCHR)==0){
          nview = -7;
        }
        if (token[2].data.number == 0) {
          vdirc();
        } else {
          vreadc(nview);
          pgfitc();
        }
      } else {
        frmatc(2, 2, TK_XYZ);
        if (ntokns < 8) {
          echoc();
          textc("*** Warning: ", FALSE);
          itextc(8-ntokns);
          textc(" zeroes added to complete statement. ***", TRUE);
          for (i=ntokns; i<8; i++) {
            token[i].kind = TK_REAL;
            token[i].data.word = 0.0;
          }
        }
        if (System.nerror) return;
        if (ntokns > 8) {
          echoc();
          textc("*** Word 9 on are extra and ignored. ***", TRUE);
        }
        for (i=0; i<3; i++) {
          out [i] = token[2+i].data.word;
          vert[i] = token[5+i].data.word;
        }
        dvuec(out, vert);
        pgfitc();
      }

/* Check and store data for a DATA XPIN statement. */
    } else if (strncmp(token[1].data.text, "xpin", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dxrvc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA XSLIDE statement. */
    } else if (strncmp(token[1].data.text, "xslide", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 1, TK_XYZ);
      if (ntokns < 6) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(6-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<6; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dxslc(token[2].data.text, &token[3]);

/* Check and store data for a DATA YPIN statement. */
    } else if (strncmp(token[1].data.text, "ypin", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dyrvc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA YSLIDE statement. */
    } else if (strncmp(token[1].data.text, "yslide", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 1, TK_XYZ);
      if (ntokns < 6) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(6-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<6; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dyslc(token[2].data.text, &token[3]);

/* Check and store data for a DATA ZPIN statement. */
    } else if (strncmp(token[1].data.text, "zpin", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 3, TK_XYZ);
      if (ntokns < 12) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(12-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<12; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 12) {
        echoc();
        textc("*** Word 13 on are extra and ignored. ***", TRUE);
      }
      dzrvc(token[2].data.text, &token[3], &token[6], &token[9]);

/* Check and store data for a DATA ZSLIDE statement. */
    } else if (strncmp(token[1].data.text, "zslide", MAXCHR) == 0) {
      frmatc(2, 1, TK_CHAR);
      frmatc(3, 1, TK_XYZ);
      if (ntokns < 6) {
        echoc();
        textc("*** Warning: ", FALSE);
        itextc(6-ntokns);
        textc(" zeroes added to complete statement. ***", TRUE);
        for (i=ntokns; i<6; i++) {
          token[i].kind = TK_REAL;
          token[i].data.word = 0.0;
        }
      }
      if (System.nerror) return;
      if (ntokns > 6) {
        echoc();
        textc("*** Word 7 on are extra and ignored. ***", TRUE);
      }
      dzslc(token[2].data.text, &token[3]);
    } else {
      echoc();
      textc("*** This type of DATA statement is not defined. ***",
        TRUE);
      System.nerror = 3;
    }
  } else {
    System.nerror = 2;
  }
  return;
}

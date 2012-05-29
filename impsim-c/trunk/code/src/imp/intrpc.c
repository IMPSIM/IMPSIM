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
/* intrpc-01 Jan 00:16 Jul 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Read and interpret the IMP input language.
|
|     Access:
|       void intrpc()
|
|     Error Conditions:
|       This subprogram diagnoses and reports many errors, primarily
|     format errors in IMP statements.  All non-fatal errors, however,
|     cause ignoring of the offending statement, with continuation by
|     reading of the next IMP statement.
|
|     Comments:
|       This is the main control subprogram of the IMP interpretter.
|       Execution is controlled by the user, who chooses the form and
|     order of IMP input statements read by the call to readc().  Exec-
|     ution continues until the END statement is encountered on input.
*
*     History:
*     01 Jan 00:JJU-Original.
*     12 May 00:JJU-Removed the FINISH statement.
*     26 Sep 00:JJU-Fixed Upper/Lower-casing of erase and pause ON/OFF.
*     21 Mar 03:JJU-Changed parser structure to a while loop.
*     23 Mar 03:JJU-Implemented iexprt user expertise flag.
*     14 Apr 03:JJU-Implemented enum XQ_type for execution flags.
*     31 Jan 09:JJU-Change SOLID READ to READ SOLID statement.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void intrpc()
{
  extern int iexprt;             /* Expected level of user expertise. */
  Value *value;
  char   display[8], fileid[MXFLCH+1], string[MAXCHR+1], titel[65];
  int    i, kcolor, kflags, nmin, nview;

/* Read the next IMP statement. */
  System.nerror = 0;
  while (TRUE) {           /* Loop until an END or EXECUTE statement. */
    if (System.nerror != 0) {
      textc("*** Line ignored. ***", TRUE);
      System.nerror = 0;
    }
    readc();

/* Test for and ignore a blank input record. */
    if (ntokns <= 0) {
      continue;
    } else if (token[0].kind == TK_UNDEF) {
      continue;

/* Check whether the first Token is alphameric. */
    } else if (token[0].kind == TK_CHAR) {
      lcasec(token[0].data.text);

/* Test for an ANIMATE statement. */
      if (strncmp(token[0].data.text, "animate", MAXCHR) == 0) {
        ldbitc(XQ_ANMAT, (void *) &System.xeqflags);

/* Test for an AXES statement. */
      } else if (strncmp(token[0].data.text, "axes", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_REAL) == 0) {
          for (i=ntokns-1; i>1; i--) {
            if (frmatc(i, 1, TK_CHAR) != 0) {
              xtoknc(i);
              textc("*** Word ", FALSE);
              itextc(i+1);
              textc(" ignored. ***", TRUE);
              System.nerror = 0;
            }
          }
          axesc(token[1].data.word, &token[2], ntokns-2);
        }

/* Test for a BEVEL statement. */
      } else if (strncmp(token[0].data.text, "bevel", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(BEVEL, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a BODY statement. */    
      } else if (strncmp(token[0].data.text, "body", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          mkbdyc(token[1].data.text);
        }                            /* BODY replaces LINK statement. */
      } else if (strncmp(token[0].data.text, "link", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          mkbdyc(token[1].data.text);
        }

/* Test for a CAM statement. */
      } else if (strncmp(token[0].data.text, "cam", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(CAM, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a CLEAR statement. */
      } else if (strncmp(token[0].data.text, "clear", MAXCHR) == 0) {
        endsvc();
        clearc();

/* Test for a CONTACT statement. */
      } else if (strncmp(token[0].data.text, "contact", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          contac(token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a CYLINDER statement. */
      } else if (strncmp(token[0].data.text, "cylinder", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(CYLINDER, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a DAMPER statement. */
      } else if (strncmp(token[0].data.text, "damper", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          damprc(token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a DATA statement. */
      } else if (strncmp(token[0].data.text, "data", MAXCHR) == 0) {
        datac();

/* Test for a DELETE statement. */
      } else if (strncmp(token[0].data.text, "delete", MAXCHR) == 0) {
        deletc();

/* Test for a DEVICE statement. */
      } else if (strncmp(token[0].data.text, "device", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "alpha", MAXCHR) == 0) {
            strcpy(display, "alpha");
          } else if (strncmp(token[1].data.text, "graphic",
            MAXCHR)== 0) {
            strcpy(display, "graphic");
          } else {
            strcpy(display, '\0');
          }
          devic(display);
          if (strcmp(display, "alpha") != 0) {
            locdvc("mouse");
          }
          newpgc();
        }

/* Test for a DRAW statement. */
      } else if (strncmp(token[0].data.text, "draw", MAXCHR) == 0) {
        clbitc(XQ_ANMAT, (void *) &System.xeqflags);
        kflags = System.xeqflags;
        ldbitc(XQ_ERASE, (void *) &System.xeqflags);
        drawc();
        System.xeqflags = kflags;

/* Test for an END statement. */
      } else if (strncmp(token[0].data.text, "end", MAXCHR) == 0) {
        endc();

/* Test for an ERASE statement. */
      } else if (strncmp(token[0].data.text, "erase", MAXCHR) == 0) {
        if (ntokns <= 1) {
          newpgc();
        } else {
          while (ntokns > 1) {
            if (frmatc(ntokns-1, 1, TK_CHAR) != 0) {
              xtoknc(ntokns-1);
              textc("*** Word ", FALSE);
              itextc(ntokns);
              textc(" ignored. ***", TRUE);
              System.nerror = 0;
            }
          }
          strncpy(string, token[1].data.text, MAXCHR+1);
          lcasec(string);
          if ((strncmp(string, "off", MAXCHR) == 0) && (ntokns == 2)) 
            clbitc(XQ_ERASE, (void *) &System.xeqflags);
          else if ((strncmp(string, "on", MAXCHR) == 0) && (ntokns==2)) 
            ldbitc(XQ_ERASE, (void *) &System.xeqflags);
          else if (ntokns >= 2) showc(-1, &token[1], ntokns-1);
        }

/* Test for an EXECUTE or EXECUTE/HOLD statement. */
      } else if (strncmp(token[0].data.text, "execute", MAXCHR) == 0) {
        System.hold = FALSE;
        if (ntokns > 1) {
          if (token[1].kind == TK_CHAR) {
            lcasec(token[1].data.text);
            if (strncmp(token[1].data.text, "hold", MAXCHR) == 0) {
              System.hold = TRUE;
            }
          }
        }
        endsvc();
        return;

/* Test for an EXPERT statement. */
      } else if (strncmp(token[0].data.text, "expert", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_INT) == 0) {
          iexprt = token[1].data.number;
        }

/* Test for a FIND statement. */
      } else if (strncmp(token[0].data.text, "find", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "equilibrium", MAXCHR) == 0) {
            stsetc();
          } else if (strncmp(token[1].data.text, "dynamic",
            MAXCHR)== 0) {
            dysetc();
          } else {
            echoc();
            textc(
              "*** This type of 'FIND' statement is not defined. ***",
              TRUE);
            System.nerror = 2;
          }
        }

/* Test for a FLAT statement. */
      } else if (strncmp(token[0].data.text, "flat", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(FLAT, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a FORCE statement. */
      } else if (strncmp(token[0].data.text, "force", MAXCHR) == 0) {
        if (frmatc(1, 4, TK_CHAR) == 0) {
          forcec(token[4].data.text, token[1].data.text, 
            token[2].data.text, token[3].data.text);
        }

/* Test for a GEAR statement. */
      } else if (strncmp(token[0].data.text, "gear", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(GEAR, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a GROUND statement. */
      } else if (strncmp(token[0].data.text, "ground", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          basec(token[1].data.text);
        }

/* Test for an IDENTIFY statement. */
      } else if (strncmp(token[0].data.text, "identify", MAXCHR) == 0) {
        for (i=ntokns-1; i>1; i--) {
          if (frmatc(i, 1, TK_CHAR) != 0) {
            xtoknc(i);
            textc("*** Word ", FALSE);
            itextc(i+1);
            textc(" ignored. ***", TRUE);
            System.nerror = 0;
          }
        }
        identc(&token[1], ntokns-1);

/* Test for an IMPACT statement. */
      } else if (strncmp(token[0].data.text, "impact", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_INT) == 0) {
          System.impacteq[0] = token[1].data.number;
          System.impacteq[1] = token[2].data.number;
          System.impacteq[2] = token[3].data.number;
        }

/* Test for a LIST DYNAMICS statement. */
      } else if (strncmp(token[0].data.text, "list", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "dynamics", MAXCHR) == 0) {
            if (frmatc(2, 3, TK_REAL) == 0) {
              if (frmatc(5, 2, TK_CHAR) == 0) {
                if (frmatc(7, 1, TK_INT) == 0) {
                  if (frmatc(8, ntokns-8, TK_CHAR) == 0) {
                    listc(token[1].data.text, &token[2], ntokns-2);
                  }
                }
              }
            }

/* Test for any other LIST statement. */
          } else {
            for (i=ntokns-1; i>1; i--) {
              if (frmatc(i, 1, TK_CHAR) != 0) {
                xtoknc(i);
                textc("*** Word ", FALSE);
                itextc(i+1);
                textc(" ignored. ***", TRUE);
                System.nerror = 0;
              }
            }
            listc(token[1].data.text, &token[2], ntokns-2);
          }
        }

/* Test for an OPEN statement. */
      } else if (strncmp(token[0].data.text, "open", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(OPEN, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a PAUSE statement. */
      } else if (strncmp(token[0].data.text, "pause", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          strncpy(string, token[1].data.text, MAXCHR+1);
          lcasec(string);
          if (strncmp(string, "off", MAXCHR) == 0) {
            clbitc(XQ_PAUSE, (void *) &System.xeqflags);
          } else {
            ldbitc(XQ_PAUSE, (void *) &System.xeqflags);
          }
        }

/* Test for a PLANE statement. */
      } else if (strncmp(token[0].data.text, "plane", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(PLANE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a PLOT DYNAMICS statement. */
      } else if (strncmp(token[0].data.text, "plot", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "dynamics", MAXCHR) == 0) {
            if (frmatc(2, 3, TK_REAL) == 0) {
              if (frmatc(5, 2, TK_CHAR) == 0) {
                if (frmatc(7, 1, TK_INT) == 0) {
                  if (frmatc(8, ntokns-8, TK_CHAR) == 0) {
                    plotc(token[1].data.text, &token[2], ntokns-2);
                  }
                }
              }
            }

/* Test for any other PLOT statement. */
          } else {
            for (i=ntokns-1; i>2; i--) {
              if (frmatc(i, 1, TK_CHAR) != 0) {
                xtoknc(i);
                textc("*** Word ", FALSE);
                itextc(i+1);
                textc(" ignored. ***", TRUE);
                System.nerror = 0;
              }
            }
            plotc(token[1].data.text, &token[2], ntokns-2);
          }
        }

/* Test for a POINT statement. */
      } else if (strncmp(token[0].data.text, "point", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          for (i=ntokns-1; i>2; i--) {
            if (frmatc(i, 1, TK_CHAR) != 0) {
              xtoknc(i);
              textc("*** Word ", FALSE);
              itextc(i+1);
              textc(" ignored. ***", TRUE);
              System.nerror = 0;
            }
          }
          pntsc(token[1].data.text, &token[2], ntokns-2);
        }

/* Test for a PRINT DYNAMICS statement. */
      } else if (strncmp(token[0].data.text, "print", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "dynamics", MAXCHR) == 0) {
            if (frmatc(2, 2, TK_CHAR) == 0) {
              if (frmatc(4, 1, TK_INT) == 0) {
                if (frmatc(5, ntokns-5, TK_CHAR) == 0) {
                  printc(token[1].data.text, &token[2], ntokns-2);
                }
              }
            }

/* Test for a PRINT INPUT statement. */
          } else if (strncmp(token[1].data.text,"input", MAXCHR) == 0) {
            printc(token[1].data.text, &token[1], 0);

/* Test for any other PRINT statement. */
          } else {
            for (i=ntokns-1; i>1; i--) {
              if (frmatc(i, 1, TK_CHAR) != 0) {
                xtoknc(i);
                textc("*** Word ", FALSE);
                itextc(i+1);
                textc(" ignored. ***", TRUE);
                System.nerror = 0;
              }
            }
            printc(token[1].data.text, &token[2], ntokns-2);
          }
        }

/* Test for a PRISM statement. */
      } else if (strncmp(token[0].data.text, "prism", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(XSLIDE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a RACK statement. */
      } else if (strncmp(token[0].data.text, "rack", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(RACK, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a READ SOLID statement. */
      } else if (strncmp(token[0].data.text, "read", MAXCHR) == 0) {
        if (frmatc(1, 2, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "solid", MAXCHR) == 0) {
            if (frmatc(1, 3, TK_CHAR) == 0) {
              solidc(token[2].data.text);
            }
          } else {
            echoc();
            textc(
              "*** This type of READ statement is not defined. ***",
              TRUE);
            System.nerror = 3;
          }
        }

/* Test for a RECALL INPUT statement. */
      } else if (strncmp(token[0].data.text, "recall", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "input", MAXCHR) == 0) {
            if (lunitc("read") > 0) {
              echoc();
              textc("*** The recall file is busy. ***", TRUE);
              System.nerror = 6;
            } else {
              endsvc();
              flnamc(2, fileid);
              readrc(fileid);
            }

/* Test for a RECALL VIEW statement. */
          } else if (strncmp(token[1].data.text, "view", MAXCHR) == 0) {
            nview = 0;
            if (ntokns > 2) {
              if ((token[2].kind == TK_INT) &&
                  (token[2].data.number < MXVIEW)) {
                nview = token[2].data.number;
              } else if (token[2].kind == TK_CHAR) {
                lcasec(token[2].data.text);
                if (strncmp(token[2].data.text, "front", MAXCHR) == 0) {
                  nview = -1;
                } else if(strncmp(token[2].data.text,"back",MAXCHR)==0){
                  nview = -2;
                } else if(strncmp(token[2].data.text,"left",MAXCHR)==0){
                  nview = -3;
                } else if (strncmp(token[2].data.text, "right",
                  MAXCHR) == 0) {
                  nview = -4;
                } else if(strncmp(token[2].data.text,"top",MAXCHR)== 0){
                  nview = -5;
                } else if (strncmp(token[2].data.text, "bottom",
                  MAXCHR) == 0) {
                  nview = -6;
                } else if (strncmp(token[2].data.text, "isometric",
                  MAXCHR) == 0) {
                  nview = -7;
                }
              }
            }
            if (nview == 0) {
              vdirc();
            } else {
              vreadc(nview);
            }
          } else {
            echoc();
            textc(
              "*** This type of RECALL statement is not defined. ***",
              TRUE);
            System.nerror = 3;
          }
        }

/* Test for a REMARK statement. */
      } else if (strncmp(token[0].data.text, "remark", MAXCHR) == 0) {

/* Test for a RESET statement. */
      } else if (strncmp(token[0].data.text, "reset", MAXCHR) == 0) {
        ldnanc((void *) &System.t);

/* Test for a RETURN statement. */
      } else if (strncmp(token[0].data.text, "return", MAXCHR) == 0) {
        endsvc();
        if (lunitc("write") < 0) {
          writrc("on");
        }

/* Test for a REVOLUTE statement. */
      } else if (strncmp(token[0].data.text, "revolute", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(ZPIN, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a RIGID statement. */
      } else if (strncmp(token[0].data.text, "rigid", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(RIGID, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a SCREW statement. */
      } else if (strncmp(token[0].data.text, "screw", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(SCREW, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a SHAPE statement. */
      } else if (strncmp(token[0].data.text, "shape", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          for (i=ntokns-1; i>1; i--) {
            if (frmatc(i, 1, TK_CHAR) != 0) {
              xtoknc(i);
              textc("*** Word ", FALSE);
              itextc(i+1);
              textc(" ignored. ***", TRUE);
              System.nerror = 0;
            }
          }
          shapec(token[1].data.text, &token[2], ntokns-2);
        }

/* Test for a SHOW statement. */
      } else if (strncmp(token[0].data.text, "show", MAXCHR) == 0) {
        if (token[1].kind == TK_UNDEF) {
          kcolor = kfrgnd;
          nmin = 2;
        } else if (token[1].kind == TK_CHAR) {
          nmin = 2;
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "black", MAXCHR) == 0) {
            kcolor = 0;
          } else if (strncmp(token[1].data.text,"white", MAXCHR) == 0) {
            kcolor = 1;
          } else if (strncmp(token[1].data.text,"red", MAXCHR) == 0) {
            kcolor = 2;
          } else if (strncmp(token[1].data.text,"orange",MAXCHR) == 0) {
            kcolor = 4;
          } else if (strncmp(token[1].data.text,"yellow",MAXCHR) == 0) {
            kcolor = 6;
          } else if (strncmp(token[1].data.text,"green", MAXCHR) == 0) {
            kcolor = 8;
          } else if (strncmp(token[1].data.text,"aqua", MAXCHR) == 0) {
            kcolor = 10;
          } else if (strncmp(token[1].data.text,"blue", MAXCHR) == 0) {
            kcolor = 12;
          } else if (strncmp(token[1].data.text,"violet",MAXCHR) == 0) {
            kcolor = 14;
          } else {
            nmin = 1;
            kcolor = kfrgnd;
          }
        } else {
          nmin = 1;
          kcolor = kfrgnd;
          if (frmatc(1, 1, TK_INT) == 0) {
            if ((token[1].data.number >= 0) && (token[1].data.number <
              MXCOLOR)) {
              nmin = 2;
              kcolor = token[1].data.number;
            }
          }
        }
        for (i=ntokns-1; i>=nmin; i--) {
          if (frmatc(i, 1, TK_CHAR) != 0) {
            xtoknc(i);
            textc("*** Word ", FALSE);
            itextc(i+1);
            textc(" ignored. ***", TRUE);
            System.nerror = 0;
          }
        }
        showc(kcolor, &token[nmin], ntokns-nmin);

/* Test for a SLIDE statement. */
      } else if (strncmp(token[0].data.text, "slide", MAXCHR) == 0) {
        if (frmatc(2, 1, TK_REAL) == 0) {
          if (frmatc(1, 1, TK_CHAR) == 0) {
            lcasec(token[1].data.text);
            if (token[1].data.text[0] == 'x') {
              i = 1;
            } else if (token[1].data.text[0] == 'y') {
              i = 2;
            } else if (token[1].data.text[0] == 'z') {
              i = 3;
            } else {
              i = 0;
            }
            slidec(i, token[2].data.word);
          }
        }

/* Test for a SLOT statement. */
      } else if (strncmp(token[0].data.text, "slot", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(SLOT, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a SPHERE statement. */
      } else if (strncmp(token[0].data.text, "sphere", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(SPHERE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a SPRING statement. */
      } else if (strncmp(token[0].data.text, "spring", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          sprngc(token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a STORE DYNAMICS statement. */
      } else if (strncmp(token[0].data.text, "store", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          lcasec(token[1].data.text);
          if (strncmp(token[1].data.text, "dynamics", MAXCHR) == 0) {
            if (frmatc(2, 2, TK_CHAR) == 0) {
              if (frmatc(4, 1, TK_INT) == 0) {
                if (frmatc(5, ntokns-5, TK_CHAR) == 0) {
                  storec(token[1].data.text, &token[2], ntokns-2);
                }
              }
            }

/* Test for a STORE INPUT statement. */
          } else if (strncmp(token[1].data.text, "input", MAXCHR) == 0){
            storec(token[1].data.text, &token[2], ntokns-2);

/* Test for a STORE VIEW statement. */
          } else if (strncmp(token[1].data.text, "view", MAXCHR) == 0) {
            storec(token[1].data.text, &token[2], ntokns-2);

/* Test for any other STORE statement. */
          } else {
            for (i=ntokns-1; i>1; i--) {
              if (frmatc(i, 1, TK_CHAR) != 0) {
                xtoknc(i);
                textc("*** Word ", FALSE);
                itextc(i+1);
                textc(" ignored. ***", TRUE);
                System.nerror = 0;
              }
            }
            storec(token[1].data.text, &token[2], ntokns-2);
          }
        }

/* Test for a TITLE statement. */
      } else if (strncmp(token[0].data.text, "title", MAXCHR) == 0) {
        titlec(titel);

/* Test for a TORQUE statement. */
      } else if (strncmp(token[0].data.text, "torque", MAXCHR) == 0) {
        if (frmatc(1, 4, TK_CHAR) == 0) {
          torqec(token[4].data.text, token[1].data.text, 
            token[2].data.text, token[3].data.text);
        }

/* Test for a TURN statement. */
      } else if (strncmp(token[0].data.text, "turn", MAXCHR) == 0) {
        if (frmatc(2, 1, TK_REAL) == 0) {
          if (frmatc(1, 1, TK_CHAR) == 0) {
            lcasec(token[1].data.text);
            if (token[1].data.text[0] == 'x') {
              i = 1;
            } else if (token[1].data.text[0] == 'y') {
              i = 2;
            } else if (token[1].data.text[0] == 'z') {
              i = 3;
            } else {
              i = 0;
            }   
            token[2].data.word /= System.ascale;
            turnc(i, token[2].data.word);
          }
        }

/* Test for an UNIT MASS statement. */
      } else if (strncmp(token[0].data.text, "unit", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          if (strncmp(token[1].data.text, "mass", MAXCHR) == 0) {
            if (frmatc(2, 1, TK_REAL) == 0) {
              if (token[2].data.word > 0.0) {
                System.gc = token[2].data.word;
              } else {
                echoc();
                textc("*** Error: Mass units must be positive. ***",
                  TRUE);
              }
            }
          }
        }

/* Test for an UJOINT statement. */
      } else if (strncmp(token[0].data.text, "ujoint", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(UJOINT, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a VALUE statement. */
      } else if (strncmp(token[0].data.text, "value", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          value = vcmplc(token[1].data.text);
        }

/* Test for a XPIN statement. */
      } else if (strncmp(token[0].data.text, "xpin", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(XPIN, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for an XSLIDE statement. */
      } else if (strncmp(token[0].data.text, "xslide", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(XSLIDE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a YPIN statement. */
      } else if (strncmp(token[0].data.text, "ypin", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(YPIN, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a YSLIDE statement. */
      } else if (strncmp(token[0].data.text, "yslide", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(YSLIDE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a ZERO statement. */
      } else if (strncmp(token[0].data.text, "zero", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_CHAR) == 0) {
          if (frmatc(2, 1, TK_REAL) == 0) {
            if (frmatc(3, 1, TK_INT) == 0) {
              zeroc(token[1].data.text, &token[2]);
            }
          }
        }

/* Test for a ZOOM statement. */
      } else if (strncmp(token[0].data.text, "zoom", MAXCHR) == 0) {
        if (frmatc(1, 1, TK_REAL) == 0) {
          scal3c(token[1].data.word);
          kflags = System.xeqflags;
          ldbitc(XQ_ERASE, (void *) &System.xeqflags);
          drawc();
          System.xeqflags = kflags;
        }

/* Test for a ZPIN statement. */
      } else if (strncmp(token[0].data.text, "zpin", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(ZPIN, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Test for a ZSLIDE statement. */
      } else if (strncmp(token[0].data.text, "zslide", MAXCHR) == 0) {
        if (frmatc(1, 3, TK_CHAR) == 0) {
          jointc(ZSLIDE, token[3].data.text, token[1].data.text, 
            token[2].data.text);
        }

/* Print a diagnostic message for an unrecognized statement. */
      } else {
        echoc();
        textc("*** Error: This statement is not understood. ***", TRUE);
        System.nerror = 2;
      }
    } else {
      echoc();
      textc("*** Error: This statement is not understood. ***", TRUE);
      System.nerror = 2;
    }
  }
}

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
/* beginc-01 Jan 00:11 Aug 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Initialize per installation or user defined requirements.
|
|     Access:
|       (void) beginc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     23 Mar 03:JJU-Implemented iexprt user expertise flag.
*     04 May 03:JJU-Implemented ptolerance user default value.
*     22 Apr 07:JJU-Corrected error in treating data seperators.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
void beginc()
{
# define MXCHR 4
  extern int  iexprt;            /* Expected level of user expertise. */
  static char choice[8] = "locator";
  static char disply[8] = "graphic";
  static char locatr[8] = "mouse";
  static char prompt[8] = "graphic";
  static int  lrvsvd    = FALSE;
  static int  kview     = -7;
  char command[MXCHR+1], fileid[MXFLCH+1], qchoic[8], qdsply[8],
    qlocat[8], string[MXFLCH+1];
  int  lun, nn;
  real fdata, hsymbl, vsymbl, width;
                 
/* Check the JJU license expiration date. */
/*  licnsc();*/                         /* No licensing at this time. */

/* Open the setup.jju file. */
  homedir = getenv("JJUHOME"); /* Get the JJUHOME environment string. */
  if (homedir == NULL) {
#   ifdef __WATCOMC__
      strcpy(homedir, "\\jju\\sys\\");
#   else
      strcpy(homedir, "/usr/jju/sys/");
#   endif
  }
  strcpy(fileid, homedir);
  strcat(fileid, "setup.jju");
  lun = lunitc("file");
_AGAIN:
  if((streams[lun] = fopen(fileid, "r"))!=NULL){/*Open setup.jju file.*/

/* Read the next line from the file. */
    while (!feof(streams[lun])) {           /* Check for end of file. */
      if(fgets(inbufr, MXINBF, streams[lun])!=NULL){/*Skip null line. */

/* Separate the command and value portions. */
        stripc(inbufr);              /* Strip off any leading blanks. */
        nn = strcspn(inbufr, "=");
        if (nn > 0) {   /* Find if an equal sign exists to the right. */
          strncpy(command, inbufr,min(nn,MXCHR));/* Copy left string. */
          command[min(nn,MXCHR)]='\0';/*Truncate to MXCHR characters. */
          lcasec(command);              /* Set command to lower case. */
          strcpy(string, &(inbufr[nn+1])); /* Save right string data. */
          stripc(string);      /* Strip any leading blanks from data. */

/* Truncate string at first blank (to ignore any comments on right). */
          if (strncmp(command, "title",MXCHR)!=0)/* Except for title. */
            string[strcspn(string, " ")] = '\0';

/* Interpret commands requiring alphanumeric string values. */
          if        (strncmp(command, "display",MXCHR)==0){/* Display */
            string[7] = '\0';
            strcpy(disply, string);
          } else if (strncmp(command, "choice",  MXCHR)==0){/* Choice */
            string[7] = '\0';
            strcpy(choice, string);
          } else if (strncmp(command, "locator",MXCHR)==0){/* Locator */
            string[7] = '\0';
            strcpy(locatr, string);
          } else if (strncmp(command, "impfile",MXCHR)==0){/* IMPfile */
            string[MXFLCH] = '\0';
            strcpy(filedir, string);
          } else if (strncmp(command, "imphelp",MXCHR)==0){/* IMPhelp */
            string[MXFLCH] = '\0';
            strcpy(helpdir, string);
          } else if (strncmp(command, "jjuhome",MXCHR)==0){/* JJUhome */
            string[MXFLCH] = '\0';
            strcpy(homedir, string);
          } else if (strncmp(command, "title", MXCHR) ==0){  /* Title */
            string[MXFLCH] = '\0';
            ldttlc(string);
          } else {

/* Replace any color names with their equivalent JJU color numbers. */
            if        (strncmp(string, "black",    3) == 0) {
              strcpy(string, "0");
            } else if (strncmp(string, "white",    3) == 0) {
              strcpy(string, "1");
            } else if (strncmp(string, "red",      3) == 0) {
              strcpy(string, "2");
            } else if (strncmp(string, "r_orange", 3) == 0) {
              strcpy(string, "3");
            } else if (strncmp(string, "orange",   3) == 0) {
              strcpy(string, "4");
            } else if (strncmp(string, "o_yellow", 3) == 0) {
              strcpy(string, "5");
            } else if (strncmp(string, "yellow",   3) == 0) {
              strcpy(string, "6");
            } else if (strncmp(string, "y_green",  3) == 0) {
              strcpy(string, "7");
            } else if (strncmp(string, "green",    3) == 0) {
              strcpy(string, "8");
            } else if (strncmp(string, "g_aqua",   3) == 0) {
              strcpy(string, "9");
            } else if (strncmp(string, "aqua",     3) == 0) {
              strcpy(string, "10");
            } else if (strncmp(string, "a_blue",   3) == 0) {
              strcpy(string, "11");
            } else if (strncmp(string, "blue",     3) == 0) {
              strcpy(string, "12");
            } else if (strncmp(string, "b_violet", 3) == 0) {
              strcpy(string, "13");
            } else if (strncmp(string, "violet",   3) == 0) {
              strcpy(string, "14");
            } else if (strncmp(string, "v_red",    3) == 0) {
              strcpy(string, "15");
            }

/* Interpret the command and store the value. */
            if        (strncmp(command, "coord", MXCHR) ==0){/* Coord */
              if        (strncmp(string, "true",  1) == 0) {
                szaxes = fabs(szaxes);
              } else if (strncmp(string, "false", 1) == 0) {
                szaxes = -fabs(szaxes);
              }
            } else if (strncmp(command, "crease",MXCHR)==0){/* Crease */
#             ifdef DOUBLE_PREC
                sscanf(string, "%lf", &fdata);
#             else
                sscanf(string, "%f",  &fdata);
#             endif
              crease = fdata * 180.0 / PI;
            } else if (strncmp(command, "expert",MXCHR)==0){/* Expert */
              sscanf(string, "%d", &iexprt);
            } else if (strncmp(command, "ktext", MXCHR) ==0){/* Ktext */
              sscanf(string, "%d", &ktext);
            } else if (strncmp(command, "kaxes", MXCHR) ==0){/* Kaxes */
              sscanf(string, "%d", &kaxes);
            } else if(strncmp(command,"kgeometry",MXCHR)==0){/* Kgeom */
              sscanf(string, "%d", &kdfgeo);
            } else if(strncmp(command,"poormans",MXCHR)==0){/*Poormans*/
              if        (strncmp(string, "true",  1) == 0) {
                lpoor = TRUE;
              } else if (strncmp(string, "false", 1) == 0) {
                lpoor = FALSE;
              }
            } else if(strncmp(command,"ptolerance",MXCHR)==0){/* PTol */
#             ifdef DOUBLE_PREC
                sscanf(string, "%lf, %d", &fdata, &nn);
#             else
                sscanf(string, "%f,  %d",  &fdata, &nn);
#             endif
              System.ptola = fabs(fdata/System.ascale);
              System.ptoll = fabs(fdata);
              if (nn > 0) System.cn = nn;
            } else if(strncmp(command,"rvsvideo",MXCHR)==0){/*RVSvideo*/
              if        (strncmp(string, "true",  1) == 0) {
                lrvsvd = TRUE;
              } else if (strncmp(string, "false", 1) == 0) {
                lrvsvd = FALSE;
              }
            } else if(strncmp(command,"tolerance",MXCHR)==0){/* Toler */
#             ifdef DOUBLE_PREC
                sscanf(string, "%lf", &fdata);
#             else
                sscanf(string, "%f",  &fdata);
#             endif
              zrogeo = fdata;
            } else if (strncmp(command, "view", MXCHR) == 0) {/* View */
              sscanf(string, "%d", &kview);
            }
          }
        }
      } else if (!feof(streams[lun])) {
        textc("Format error in '", FALSE);
        textc(fileid, FALSE);
        textc("' file;", TRUE);
        textc("  item: '", FALSE);
        textc(strncpy(inbufr, inbufr, strcspn(inbufr, "\n")), FALSE);
        textc("' ignored.", TRUE);
        waitc();
      }
    }
    fclose(streams[lun]);
  }
  if (strncmp(fileid, "setup.jju", 9) != 0) {
    strcpy(fileid, "setup.jju");   /* Also look in current directory. */
    goto _AGAIN;
  }

/* Set the graphic output device. */
  if (qiactc() && (strncmp(disply, "alpha", 5) != 0)) {
_REDO:
    do {
      textc("What kind of display are you using?", TRUE);
      textc("  alpha, ", FALSE);
      textc(prompt, FALSE);
      textc(" [", FALSE);
      textc(disply, FALSE);
      textc("]: > ", FALSE);         /* Prompt for the user's choice. */
    } while (bfinc(" ") != 0);
    bfgetc(string);                         /* Get the user's choice. */
    if (lenc(string) == 0) strcpy(string, disply);
    stripc(string);
    devic(string);                  /* Set the graphic output device. */
    qdvc(qdsply, qchoic, qlocat);        /* Query the actual setting. */
    if ((strncmp(string,   "alpha", 5) != 0) &&    /* Prompt again    */
        (strncmp(qdsply, "alpha", 5) == 0)) goto _REDO; /* if needed. */
    if (lrvsvd) rvsvdc();         /* Set reverse video if called for. */
  }

/* Set the input (choice and locator) devices. */
  chcdvc(choice);                           /* Set the choice device. */
  if (strncmp(qdsply, "alpha", 5) == 0) strcpy(locatr, "alpha");
  locdvc(locatr);                          /* Set the locator device. */
  akbic();                             /* Arm the keyboard interrupt. */

/* Set the 2-d window and viewport. */
  qchszc(&hsymbl, &vsymbl);         /* Get the screen character size. */
  width = 1.0 - 10.0 * hsymbl;/* Save boundary for menu on the right. */
  framsc(0.0, 0.0, width, 1.0);           /* Set the screen boundary. */
  width *= 5.0;
  fram2c(-width, 0.0, width, 0.0);      /* Set the 2D frame boundary. */
  framsc(0.0, 0.0, 1.0, 1.0);           /* Set the screen NDC bounds. */

/* Initialize the stored view transformations. */
  vopenc();                           /* Open the standard view file. */
  vreadc(kview);              /* Set the initial view transformation. */
  return;
# undef MXCHR
}

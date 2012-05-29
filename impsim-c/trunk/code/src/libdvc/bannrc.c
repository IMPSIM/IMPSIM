/* ------------------------------------------------------------------ */
/* bannrc-01 Jan 00:21 Jan 09
|     (C)Copyright, JJU Research, 2000-2009.
|
|     Description:
|       Print a banner for the top of the output of a JJU program.
|
|     Access:
|       void bannrc(char *title, char *releas, char *cpyrgt)
|     char *title,i-Title of the program.
|     char *releas,i-Release date in the form "01 Jul 2005".
|     char *cpyrgt,i-Initial copyright year, e.g. "2001".
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     21 Jan 09:JJU-Change copyright final date to current date.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void bannrc(char *title, char *releas, char *cpyrgt)
#else
  void bannrc(title, releas, cpyrgt)
  char *title, *releas, *cpyrgt;
#endif
{
  char  ctime[9], cdate[12], cyear[5];
  char *space="                                                  ";
# ifdef __WATCOMC__
    char *system = "Win/XP";
# else
    char *system = "Unix  ";
# endif
  int    index, n;
  struct tm *ltime;
  time_t timer;
 
/*  Write a banner at the top of the output.  */
  (void) time(&timer);
  ltime = localtime(&timer);
  strftime(cdate, (size_t) 12, "%d %b %Y", ltime);
  strftime(ctime, (size_t)  9, "%H:%M:%S", ltime);
  newpgc();                    /* Begin at the top of a fresh screen. */
  textc("                           <<<  Notice  >>>", TRUE);
  textc(" ", TRUE);
  textc("This is the ", FALSE);
  textc(title, FALSE);
  textc(" program.", TRUE);
  textc("(C)Copyright, JJU Research, ", FALSE);
  textc(cpyrgt, FALSE);
  strncpy(cyear, &(cdate[7]), 4);
  cyear[4] = '\0';
  if (strcmp(cyear, cpyrgt)) {
    textc("-", FALSE);
    textc(cyear, FALSE);
  }
  textc(".  All rights reserved.", TRUE);
  textc(" ", TRUE);
  textc("JJU Research is endeavoring to make this ", FALSE);
  textc("program as complete,  accurate,", TRUE);
  textc("and  easy  to use as possible. ", FALSE);
  textc("  Suggestions  and comments are welcomed.", TRUE);
  textc("Any errors encountered in either the documentation  ", FALSE);
  textc("or  in  the  results", TRUE);
  textc("should be immediately brought to our attention.", TRUE);
  textc(" ", TRUE);
  textc("Neither JJU Research nor those supplying  the  ", FALSE);
  textc("computer  facilities  for", TRUE);
  textc("this  analysis  assume any responsibility for the ", FALSE);
  textc("accuracy, validity, or", TRUE);
  textc("applicability of any results obtained from the ", FALSE);
  textc("system; users must verify", TRUE);
  textc("their own results.", TRUE);
  textc(" ", TRUE);
  textc("************************************", FALSE);
  textc("************************************", TRUE);
  textc("*", FALSE);
  n = strlen(title);
  index = 15+n/2;
  textc(&(space[index]), FALSE);
  textc(title, FALSE);
  index = 30+n-index;
  textc(&(space[index]), FALSE);
  textc("*", TRUE);
  textc("*                ", FALSE);
  textc(system, FALSE);
  textc(" Version -- Released ", FALSE);
  textc(releas, FALSE);
  textc("                *", TRUE);
  textc("*                 on ", FALSE);
  textc(cdate, FALSE);
  textc("           at ", FALSE);
  textc(ctime, FALSE);
  textc("                 *", TRUE);
  textc("************************************", FALSE);
  textc("************************************", TRUE);
  return;
}

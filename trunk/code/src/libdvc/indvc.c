/* ------------------------------------------------------------------ */
/* indvc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Prompt for locator and choice devices, and set them accordingly.
|
|     Access:
|       (void) indvc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void indvc()
{
  char answer[8], cdvstr[8], dspstr[12], ldvstr[8], quest[2];
  int  iostat;
 
  qdvc(dspstr, cdvstr, ldvstr);
_2:
  if (dspdvc == DT_ALPHA) {
    strcpy(quest, "a");
  } else {
    textc("Locator input via Alpha, Mouse, or Tablet, A,M,T [", FALSE);
    strncpy(quest, ldvstr, 1);
    quest[1] = '\0';
    textc(quest, FALSE);
    textc("]: > ", FALSE);
    if ((iostat = bfinc(quest)) == 2) return;
    if (iostat != 0) goto _2;
    alprdc(quest, answer);
    strncpy(quest, answer, 1);
    quest[1] = '\0';
  }
  if (*quest == 'a' || *quest == 'A') {
    strcpy(answer, "alpha");
  } else if (*quest == 'm' || *quest == 'M') {
    strcpy(answer, "mouse");
  } else if (*quest == 't' || *quest == 'T') {
    strcpy(answer, "tablet");
  } else {
    goto _2;
  }
  locdvc(answer);
_3:
  if (dspdvc == DT_ALPHA) {
    strcpy(quest, "a");
  } else if (*quest == 'a' || *quest == 'A') {
    strcpy(quest, "a");
  } else {
    textc("Menu choice input via Alpha or Locator, A,L  [", FALSE);
    strncpy(quest, cdvstr, 1);
    quest[1] = '\0';
    textc(quest, FALSE);
    textc("]: > ", FALSE);
    if ((iostat = bfinc(quest)) == 2) return;
    if (iostat != 0) goto _2;
    alprdc(quest, answer);
    strncpy(quest, answer, 1);
    quest[1] = '\0';
  }
  if (*quest == 'a' || *quest == 'A') {
    strcpy(answer, "alpha");
  } else if (*quest == 'l' || *quest == 'L') {
    strcpy(answer, "locator");
  } else {
    goto _3;
  }
  chcdvc(answer);
  return;
}

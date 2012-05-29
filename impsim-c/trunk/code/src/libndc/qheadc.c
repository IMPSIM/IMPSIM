/* ------------------------------------------------------------------ */
/* qheadc-04 Aug 03:09 Aug 03
|     (C)Copyright, JJU Research, 2003.
|
|     Description:
|       Return to the calling program the menu header string for a given
|     menu header number.
|
|     Access:
|       (void) qheadc(char *headr, int nmenu);
|     char *headr, o-Menu header string for menu number nmenu.
|     int   nmenu, i-Number of header string sought, (nmenu = 1,2,...).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The header string sought must have been defined by a previous
|     call to function ldhdrc().
|       The menu numbers are arranged in alphabetical order.
*
*     History:
*     04 Aug 03:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void qheadc(char *headr, int nmenu)
#else
  void qheadc(headr, nmenu)
  char *headr;
  int   nmenu;
#endif
{
  strcpy(headr, header[nmenu-1]);
  return;
}

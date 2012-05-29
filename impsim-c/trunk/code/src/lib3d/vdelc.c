/* ------------------------------------------------------------------ */
/* vdelc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Delete the specified 3D to 2D stored view transformation.
|
|     Access:
|       (void) vdelc(int nview);
|     int nview,i-View number, (1 <= nview <= 16).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If nview <= 0 a directory is printed and a prompt is issued for
|     the user's choice.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void vdelc(int nview)
#else
  void vdelc(nview)
  int nview;
#endif
{
  int iostat, n;
 
/* Print the directory if required. */
  n = nview;
  do {
    if (n <= 0) {
      vdirc();
      n = MXVIEW + 1;
    }
 
/* Get the view number. */
    if (n > MXVIEW) {
      n = 1;
      if (intact) {
        textc("Enter a view number, [1]: > ", FALSE);
        if ((iostat = bfinc("1")) == 2) return;
        if (iostat == 0) {
          n = intrdc(1, &iostat);
        } else {
          n = 0;
          continue;
        }
      }
    }
    if ((n > 0) && (n <= MXVIEW)) break;
  } while(TRUE);
 
/* Delete the view parameters. */
  lvue[n] = FALSE;
  idvue[n][0] = '\0';
  return;
}

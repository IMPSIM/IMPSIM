/* ------------------------------------------------------------------ */
/* vdirc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       List the directory information for the current stored views.
|
|     Access:
|       (void) vdirc();
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void vdirc()
{
  char key[4];
  int  i;
 
/* Print the view directory. */
  textc("====== View Directory ======", TRUE);
  textc("-7 = Isometric View (-z+x,y)", TRUE);
  textc("-6 = Bottom View       (x,z)", TRUE);
  textc("-5 = Top View         (x,-z)", TRUE);
  textc("-4 = Right View       (-z,y)", TRUE);
  textc("-3 = Left View         (z,y)", TRUE);
  textc("-2 = Back View        (-x,y)", TRUE);
  textc("-1 = Front View        (x,y)", TRUE);
 
/* Print the rest of the directory (from file). */
  for (i=1; i<=MXVIEW; i++) {
    if (lvue[i]) {
      sprintf(key, "%2d", i);
      textc(key, FALSE);
      textc(" = ", FALSE);
      textc(idvue[i], TRUE);
    }
  }
  return;
}

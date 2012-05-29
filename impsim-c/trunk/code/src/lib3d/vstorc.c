/* ------------------------------------------------------------------ */
/* vstorc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Store the current 3D to 2D transformation for later recall.
|
|     Access:
|       (void) vstorc(int nview, char viewid[])
|     int  nview,i-View number within the file (1 <= nview <= 16).
|     char viewid[],i-Identifying title for the view directory.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If execution is interactive and viewid = " " or viewid = '\0',
|     a prompt is issued for the user's choice.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void vstorc(int nview, char viewid[])
#else
  void vstorc(nview, viewid)
  int  nview;
  char viewid[];
#endif
{
  char choice[2], key[4];
  int  i, iostat, j, n;
 
/* Get the view number. */
  n = nview;
_2:
  if ((n < 0) || (n > MXVIEW)) {
    if (intact){
      do {
        textc("Enter view number, [1]: > ", FALSE);
        iostat = bfinc("1");
        if (iostat == 2) return;
      } while (iostat != 0);
      n = intrdc(1, &iostat);
      goto _2;
    }
  } else {
    if (n > 0){
      if (lvue[n]){
        if (intact){
          sprintf(key, "%2d", n);
          do {
            textc("Overwrite data for view ", FALSE);
            textc(key, FALSE);
            textc("?  y/n [n]: > ", FALSE);
            iostat = bfinc("n");
            if (iostat == 2) return;
          } while (iostat != 0);
          alprdc("n", choice);
          if (choice[0] != 'y' && choice[0] != 'Y'){
            n = -1;
            goto _2;
          }
        }
      }
 
/* Get the new view title. */
      strcpy(idvue[n], viewid);
      if ((idvue[n][0] == '\0') || (idvue[n][0] == SPACE)) {
        if (intact) {
          sprintf(key, "%2d", n);
          do {
            textc("Enter title for view ", FALSE);
            textc(key, FALSE);
            textc(": > ", FALSE);
            iostat = bfinc(" ");
            if (iostat == 2) return;
          } while (iostat != 0);
          bfgetc(idvue[n]);
        }
      }
      stripc(idvue[n]);
      lvue[n] = TRUE;
    }
 
/* Store the data. */
    for (i=0; i<3; i++) {
      for (j=0; j<3; j++) {
        x32vue[n][i][j] = x3to2[i][j];
      }
    }
  }
  return;
}

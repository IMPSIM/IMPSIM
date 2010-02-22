/* ------------------------------------------------------------------ */
/* vopenc-01 Jan 00:25 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Open any stored view file and initialize viewsc.h.
|
|     Access:
|       (void) vopenc();
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
void vopenc()
{
  int fd, i, j, k, key;

/* Look for and open an old view file. */
  if ((fd = open(filvue, O_RDWR)) >= 0) {
    lseek(fd, 0, SEEK_SET);
    if ((read(fd, (void *) &key, sizeof(int)) == sizeof(int))
      && (key == MAGIC_NUM)) {

/* Read its views. */
      for (i=0; i<=MXVIEW; i++) {
        read(fd, (void *) &(lvue[i]), sizeof(int));
      }
      for (i=1; i<=MXVIEW; i++) {
        if (lvue[i]) {
          lseek(fd, (VIEW_HEAD + (i * VIEW_SIZE)), SEEK_SET);
          read(fd, (void *) idvue[i], MXFLCH);
          idvue[i][MXFLCH] = '\0';
          for (j=0; j<3; j++) {
            for (k=0; k<3; k++) {
              read(fd, (void *) &(x32vue[i][j][k]), sizeof(real));
            }
          }
        }
      }
    }
    close(fd);
  }
  return;
}

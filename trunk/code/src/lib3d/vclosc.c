/* ------------------------------------------------------------------ */
/* vclosc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Update and close the view file.
|
|     Access:
|       (void) vclosc();
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
void vclosc()
{
  char answer[2];
  int  exist, iostat, i, j, k, fd, key, lstore, lun, magic = MAGIC_NUM;
 
/* Check for need to store data in a view file. */
  lstore = FALSE;
  for (i=0; i<=MXVIEW; i++) {
    lstore |= lvue[i];
  }
  if (lstore){
 
/* Check for an old view file. */
    lun = lunitc("file");
    if ((streams[lun] = fopen(filvue, "r")) == NULL) {
      exist = FALSE;
    } else {
      fclose(streams[lun]);
      exist = TRUE;
    }
 
/* Open an old or new view file. */
    if ((fd = open(filvue, (O_RDWR | O_CREAT), 0644)) >= 0) {
      if (exist && ((read(fd, (void *) &key, sizeof(int)) < 0)
        || (key != magic))) {
        textc("Warning:  File ", FALSE);
        textc(filvue, FALSE);
        textc(" cannot be opened as a view file.", TRUE);
        if (intact) {
          do {
            textc("Overwrite/reinitialize file?  y/n [n]: > ", FALSE);
            iostat = bfinc("n");
          } while (iostat != 0);
          alprdc("n", answer);
          answer[1] = '\0';
          if (*answer == 'y' || *answer == 'Y') {
            lseek(fd, 0, SEEK_SET);
            write(fd, (void *) &magic, sizeof(int));
            for (i=0; i<=MXVIEW; i++){
              write(fd, (void *) &(lvue[i]), sizeof(int));
            }
            for (i=1; i<=MXVIEW; i++) {
              if (lvue[i]) {
                lseek(fd, (VIEW_HEAD + (i*VIEW_SIZE)), SEEK_SET);
                write(fd, (void *) idvue[i], MXFLCH);
                for (j=0; j<3; j++) {
                  for (k=0; k<3; k++) {
                    write(fd,
                      (void *) &(x32vue[i][j][k]), sizeof(real));
                  }
                }
              }
            }
          } else {
            textc(" Stored view data is lost.", TRUE);
            waitc();
          }
        } else {
          textc(" Stored view data is lost.", TRUE);
        }
      } else {
        lseek(fd, 0, SEEK_SET);
        write(fd, (void *) &magic, sizeof(int));
        for (i=0; i<=MXVIEW; i++) {
          write(fd, (void *) &(lvue[i]), sizeof(int));
        }
        for (i=1; i<=MXVIEW; i++) {
          if (lvue[i]) {
            lseek(fd, (VIEW_HEAD + (i*VIEW_SIZE)), SEEK_SET);
            write(fd, (void *) idvue[i], MXFLCH);
            for (j=0; j<3; j++) {
              for (k=0; k<3; k++) {
                write(fd, (void *) &(x32vue[i][j][k]), sizeof(real));
              }
            }
          }
        }
      }
      close(fd);
    } else {
      textc("Error:  View file ", FALSE);
      textc(filvue, FALSE);
      textc(" cannot be opened.", TRUE);
      textc("  Stored view data is lost.", TRUE);
      waitc();
    }
  }
  return;
}

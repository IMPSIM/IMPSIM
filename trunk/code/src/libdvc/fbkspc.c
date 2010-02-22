/* ------------------------------------------------------------------ */
/* fbkspc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Backspace to the end of the previous record, the stream 
|     designated by its logical unit number.
|
|     Access:
|       (void) fbkspc(int lun);
|     int lun,i-Logical unit number of the stream designated.
|
|     Error Conditions:
|       I/O errors are reported directly by the operating system.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       It is assumed that the stream has been opened by the opnflc()
|     function with a mode of "r+".
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void fbkspc(int lun)
#else
  void fbkspc(lun)
  int lun;
#endif
{
  char buffer[2];
 
  if (lun > 0){
    fseek(streams[lun], -1, SEEK_END);
    do {
      fseek(streams[lun], -2, SEEK_CUR);
      fgets(buffer, 2, streams[lun]);
    } while (buffer[0] != '\n');
    fflush(streams[lun]);
  }
  return;
}

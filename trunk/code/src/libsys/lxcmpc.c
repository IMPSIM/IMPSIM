/* ------------------------------------------------------------------ */
/* lxcmpc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       This function determines the lexical relationship between two
|     character strings (cword1 and cword2).  The comparison is done 
|     only on the minimum of the two string lengths.  Note: this is 
|     taken to mean the length not including trailing blanks.
|
|     Access:
|       ireslt = (int) lxcmpc(char *cword1, char *cword2)
|     char *cword1i-First character string.
|     char *cword2,i-Second character string.
|     int ireslt,o-Integer flag for result of lexical compare:
|       iresult > 0 for cword1 > cword2;
|       iresult = 0 for cword1 = cword2;
|       iresult < 0 for cword1 < cword2.
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
#ifdef ANSI
  int lxcmpc(char *cword1, char *cword2)
#else
  int lxcmpc(cword1, cword2)
  char *cword1, *cword2;
#endif
{
  int nchrs;

  nchrs = min(lenc(cword1), lenc(cword2));
  return(strncmp(cword1, cword2, nchrs));
}

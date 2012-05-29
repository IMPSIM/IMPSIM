/* ------------------------------------------------------------------ */
/* lenc-01 Jan 00:23 Feb 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Find the used length of a character string not counting any
|     trailing blanks or non-printable characters.
|
|     Access:
|       length = (int) lenc(char *string);
|     char *string,i-Character string supplied.
|     int length,o-Number of characters preceding trailing blanks.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       Non-printable or blank trailing characters are not counted, but
|     non-printable followed by non-blank printable characters are
|     counted.
|       An all-blank or null string returns a lenc() of zero.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */

#include "..\libcad\libcad.h"
#ifdef ANSI
  int lenc(char *string)
#else
  int lenc(string)
  char *string;
#endif
{
  char *chr;
  int kount, len;

  len = 0;
  if (string != NULL){
    kount = 0;
    for (chr=string; *chr; chr++) {
      kount++;
      if (isgraph(*chr)) len = kount;
    }
  }
  return(len);
}

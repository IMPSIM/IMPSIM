/* ------------------------------------------------------------------ */
/* cunpkc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Unpack the color information from a single packed integer into
|     three separate integer RGB components.
|
|     Access:
|       (void) cunpkc(long int icolor, int *ired, int *igreen,
|         int *iblue);
|     long int icolor,i-Packed color information.
|     int *ired,  o-Red    color component (0<=ired  <=255).
|     int *igreen,o-Green  color component (0<=igreen<=255).
|     int *iblue, o-Blue   color component (0<=iblue <=255).
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The packed color information is formatted in eight bit groups
|     packed into a single integer of up to 24 bits.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void cunpkc(long int icolor, int *ired, int *igreen, int *iblue)
#else
  void cunpkc(icolor, ired, igreen, iblue)
  long int icolor;
  int     *ired, *igreen, *iblue;
#endif
{
  *ired   = (icolor >> 16) & 255;
  *igreen = (icolor >>  8) & 255;
  *iblue  = (icolor      ) & 255;
  return;
}

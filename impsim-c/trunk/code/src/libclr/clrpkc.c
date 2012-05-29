/* ------------------------------------------------------------------ */
/* clrpkc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Pack a set of integer RGB color values into a single integer.
|
|     Access:
|       icolor = (int) clrpkc(int ired, int igreen, int iblue);
|     int ired,  i-Red    color component (0<=ired  <=255).
|     int igreen,i-Green  color component (0<=igreen<=255).
|     int iblue, i-Blue   color component (0<=iblue <=255).
|     int icolor,o-Packed color information.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The colors are packed with eight bits per component; a minimum
|     word length of 24 bits is assumed.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int clrpkc(int ired, int igreen, int iblue)
#else
  int clrpkc(ired, igreen, iblue)
  int ired, igreen, iblue;
#endif
{
  int icolor;

  icolor = ((ired % 256) << 16) | ((igreen % 256) << 8) | (iblue % 256);
  return(icolor);
}

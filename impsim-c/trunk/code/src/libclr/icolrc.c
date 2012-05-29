/* ------------------------------------------------------------------ */
/* icolrc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Given one of the JJU color numbers, this routine finds the
|     corresponding color table number for the current display device.
|
|     Access:
|       icolor = (int) icolrc(int ncolor)
|     int ncolor,i-The given JJU color number.
|     int icolor,o-The corresponding color table number.
|
|     Error Conditions:
|       If ncolor is less than zero, icolor is set to zero.
|       If device is set to "alpha" or if ncolor is greater than or
|     equal to MXCOLOR, icolor is set to one.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int icolrc(int ncolor)
#else
  int icolrc(ncolor)
  int ncolor;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    struct videoconfig vc;
# endif
  int icolor, mxclrs;
 
  if (ncolor < 0){
    icolor = 0;
  } else if (ncolor < MXCOLOR) {
    if (dspdvc == DT_GRAPHIC) {
#     ifdef __WATCOMC__
        _getvideoconfig(&vc);
        mxclrs = min(vc.numcolors, MXCOLOR) - 2;
#     else
        mxclrs = MXCOLOR - 2;
#     endif
      icolor = (nint((ncolor - 1) * mxclrs / 14.0) % mxclrs) + 1;
    } else {
      icolor = 1;
    }
  } else {
    icolor = 1;
  }
  return(icolor);
}

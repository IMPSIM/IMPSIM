/* ------------------------------------------------------------------ */
/* qcmapc-01 Jan 00:23 Jun 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Return the number of bit planes used for displaying colors (the
|     length of the color lookup table) and the number of bits used for
|     representation of each color (resolution of the color lookup
|     table) for the display screen.
|
|     Access:
|       (void) qcmapc(int *ncbits, int *mxcbts)
|     int *ncbits,o-Max number of bits for displayable colors.
|     int *mxcbts,o-Max number of bits for each color representation.
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
#ifdef ANSI
  void qcmapc(int *ncbits, int *mxcbts)
#else
  void qcmapc(ncbits, mxcbts)
  int *ncbits, *mxcbts;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    struct videoconfig vc;
# endif
  int ncolrs;
 
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      _getvideoconfig(&vc);
      ncolrs = vc.numcolors;
#   else
      ncolrs = MXCOLOR;
#   endif
    if(ncolrs == 0)*ncbits = 4;
    if(ncolrs >= 2)*ncbits = 1;
    if(ncolrs >= 4)*ncbits = 2;
    if(ncolrs >= 8)*ncbits = 3;
    if(ncolrs >=16)*ncbits = 4;
    *mxcbts = 1;
    if(*ncbits > 1)*mxcbts = 8;
  } else {
    *ncbits = 1;
    *mxcbts = 1;
  }
  return;
}

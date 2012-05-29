/* ------------------------------------------------------------------ */
/* prcntc-01 Jan 00
|     (C)Copyright, JJU Research, 2000.
|
|     Description:
|       Draw and update a a color-filled bar along the bottom-right part
|     of the screen showing percent completion of the current task.
|
|     Access:
|       (void) prcntc(real prcent);
|     real prcent,i-Percent completion to be depicted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The original color bar outline is outlined on the initial call
|     with prcent = 0.0; later calls update the filled portion of the
|     color bar.
|       The task of measurement of completion and the setting of the
|     colors are the responsibility of the calling program.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void prcntc(real prcent)
#else
  void prcntc(prcent)
  real prcent;
#endif
{
# define SMIN 0.65
# define TMIN 0.06
# define SMAX 0.85
# define TMAX 0.08
  int  i;
  real spnt[4], tpnt[4], schsiz, tchsiz, stmp, ttmp;
 
/* When called with prcent <= 0.0, initialize the bar. */
  if (prcent <= 0.0) {
    stmp = SMIN;
    ttmp = TMIN;
    movasc(SMIN, TMIN);
    drwasc(SMIN, TMAX);
    drwasc(SMAX, TMAX);
    drwasc(SMAX, TMIN);
    for (i=0; i < 9; i++) {
      movrsc(-0.10 * (SMAX - SMIN), (TMAX - TMIN));
      drwrsc(0.0, -(TMAX-TMIN));
    }
    qchszc(&schsiz, &tchsiz);
    ttmp = TMIN - 0.5 * tchsiz;
    stmp = SMIN - 0.5 * schsiz;
    movasc(stmp, ttmp);
    htextc("0");
    stmp = 0.5 * (SMAX + SMIN) - 5.0 * schsiz;
    movasc(stmp, ttmp);
    htextc("% Complete");
    stmp = SMAX - 1.5 * schsiz;
    movasc(stmp, ttmp);
    htextc("100");
 
/* When called with prcent > zero, then fill the bar to prcent. */
  } else {
    spnt[0] = SMIN;
    tpnt[0] = TMIN;
    spnt[1] = SMIN + prcent * (SMAX - SMIN);
    tpnt[1] = TMIN;
    spnt[2] = spnt[1];
    tpnt[2] = TMAX;
    spnt[3] = SMIN;
    tpnt[3] = TMAX;
    fillsc(4, spnt, tpnt);
    bflshc();
  }
  return;
# undef SMIN
# undef TMIN
# undef SMAX
# undef TMAX
}

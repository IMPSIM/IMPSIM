/* ------------------------------------------------------------------ */
/* devic-01 Jan 00:28 Sep 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Initialize the libcad data structure and open local I/O buffers
|     to correspond to a specified type of display device.
|
|     Access:
|       (void) devic(char *kind)
|     char *kind,i-Display device mneumonic device code.
|       kind = "alpha"   for an (ASCII) alphanumeric terminal.
|       kind = "graphic" for a graphic workstation.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       This routine must be called by the application program before
|     any other graphics or libcad I/O subprograms.
|       If the kind of device is not recognized, it is treated as a
|     request for a kind = "alpha" device type.
|       If execution is not interactive, kind is treated as "alpha".
|       This routine may be called more than once if desired, perhaps
|     for example, to switch device types.  However, each time it is
|     called, all previously defined parameters are reset to their
|     initial (default) values for the new device type.
|       The application program should also call routine finplc() after
|     all libcad functions are completed to insure proper flushing of
|     local I/O buffers and closing of i/o streams.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void devic(char *kind)
#else
  void devic(kind)
  char *kind;
#endif
{
# ifdef __WATCOMC__
#   include <graph.h>
    struct videoconfig vc;
# else
#   include "xglblc.h"
# endif
  char type[8];
  int  iarg1, iarg2, i, j, lwarn, mode;
 
/* Deactivate any currently active display device. */
  intact = qiactc();               /* Set the flag for interactivity. */
  kbwtch = FALSE;     /* Interrupts ignored unless this flag is TRUE. */
  finplc();            /* Close any previously opened display device. */
 
/* Initialize the device independent parameter values. */
  lunsmb = 0;
  lsmode = FALSE;
  lspen  = FALSE;
  l2pen  = FALSE;
  l3pen  = FALSE;
  atext_en =TRUE;
  scroll_en=TRUE;
  nhdrs  = 0;
  iline  = 0;
  idash  = 0;
  ndash  = 0;
  ldash  = 0;
  dshseg = 0.0;
  for (i=0; i<MXDASH; i++) {
    dshtbl[i]=0.0;
  }
  ssymbl = 0.01250;
  tsymbl = 0.04167;
  spen   = 0.0;
  tpen   = 1.0;
  smin   = 0.0;
  tmin   = 0.0;
  smax   = 1.0;
  tmax   = 1.0;
  sscale = 1023.0;
  tscale =  767.0;
  aspect = 0.75;
  stzero = 0.0009765625;
  kgrid  = 0;
  sgmin  = 0.0;
  tgmin  = 0.0;
  sgmax  = 1.0;
  tgmax  = 1.0;
  pscale = 1.0;
  qscale = 1.0;
  p0     = 0.0;
  q0     = 0.0;
  x2min  = 0.0;
  y2min  = 0.0;
  z2min  =-99999.0;
  x2max  = 1.0;
  y2max  = 1.0;
  z2max  = 99999.0;
  x2scal = 1.0;
  y2scal = 1.0;
  x20    = 0.0;
  y20    = 0.0;
  eyeinv = 0.0;
  strcpy(filvue, "views.jju");
  for (i=0; i<4; i++) {
    for (j=0; j<4; j++) {
      x3to2[i][j] = 0.0;
      x2to3[i][j] = 0.0;
    }
    x3to2[i][i] = 1.0;
    x2to3[i][i] = 1.0;
  }
  for (i=0; i<=MXVIEW; i++) {
    lvue[i] = FALSE;
    idvue[i][0] = '\0';
  }
 
/* Verify the requested display type. */
  strcpy(type, kind);
  stripc(type);
  type[lenc(type)] = '\0';
  lcasec(type);
  if (strcmp(type, "alpha") == 0) {
    dspdvc = DT_ALPHA;
    lwarn  = FALSE;
  } else if (strcmp(type, "graphic") == 0) {
    dspdvc = DT_GRAPHIC;
    lwarn  = FALSE;
  } else {
    dspdvc = DT_ALPHA;
    lwarn  = intact;
  }
 
/* Initialize the graphic window and find its dimensions. */
  if (dspdvc == DT_GRAPHIC) {
#   ifdef __WATCOMC__
      _getvideoconfig(&vc);
      switch (vc.adapter) {
      case _VGA:
        mode = _VRES16COLOR;
        break;
      case _SVGA:
        mode = _VRES16COLOR;
        break;
      case _MCGA:
        mode = _MRES256COLOR;
        break;
      case _EGA:
        if (vc.monitor == _MONO) {
          mode = _ERESNOCOLOR;
        } else {
          mode = _ERESCOLOR;
        }
        break;
      case _CGA:
        mode = _MRES4COLOR;
        break;
      case _HERCULES:
        mode = _HERCMONO;
        break;
      default:
        mode = _MAXRESMODE;
      }
      _setvideomode(mode);
      _settextrows(30);
      _getvideoconfig(&vc);
      sscale = (real) (vc.numxpixels-1);
      tscale = (real) (vc.numypixels-1);
#   else
      if (! X_Initialized) rootwin = xinitc();
      win = xopenc(rootwin);
      sscale = (real) DisplayWidth( dsp, screen);
      tscale = (real) DisplayHeight(dsp, screen);
      aspect = ( sscale / (real) DisplayWidthMM( dsp, screen))
             / ( tscale / (real) DisplayHeightMM(dsp, screen));
#   endif
    stzero = 1.0 / max(sscale, tscale);
  }
 
/* Open the local I/O buffers for the display. */
  bfopnc();
  if(lwarn)textc("Warning: Unknown display type set to 'alpha'.", TRUE);
 
/* Initialize the device dependent parameters. */
  qcmapc(&iarg1, &iarg2);
  ctablc(iarg1, 1, 0, 50, 99);
  if (kfrgnd == kbkgnd) kfrgnd = abs(1 - kbkgnd);
  if (ktext  == kbkgnd) ktext  = kfrgnd;
  colrac(ktext);
  colrsc(ktext);
  colrfc(kfrgnd);
  if (dspdvc == DT_GRAPHIC){
    chcdvc("locator");
  } else {
    chcdvc("alpha");
  }
  locdvc("alpha");
  stdchc(0);
  dashc(0);
  homec();
  return;
}

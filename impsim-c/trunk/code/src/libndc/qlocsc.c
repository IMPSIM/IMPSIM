/* ------------------------------------------------------------------ */
/* qlocsc-01 Jan 00:30 Sep 05
|     (C)Copyright, JJU Research, 2000-2005.
|
|     Description:
|       Arm the locator device for a single input and return its screen
|     coordinates.
|
|     Access:
|       (void) qlocsc(real *s, real *t, int *lflag)
|     real *s,    o-Horizontal screen coordinate of the location input.
|     real *t,    o-Vertical   screen coordinate of the location input.
|     int  *lflag,o-Logical error flag returned as:
|       *lflag = TRUE if the location is within the screen window.
|
|     Error Conditions:
|       For non-interactive execution the current graphic pen location
|     is returned instead.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       Which locator device is read may be controlled by previous calls
|     to locdvc().  The default locator device is "alpha".
|       If the locator device is set to "alpha", the user is asked to
|     enter data via the keyboard.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef __WATCOMC__
# include <i86.h>
  static int event, imouse = 320, jmouse = 240;
# pragma off (check_stack)
  void __loadds __far mouse_handler(int max, int mcx, int mdx) {
#   pragma aux mouse_handler parm [EAX] [ECX] [EDX]
    if (max & (0x0002 + 0x0008)) {   /* Check left and right buttons. */
      imouse = mcx;
      jmouse = mdx;
      event  = TRUE;
    }
  }
# pragma on (check_stack)
#endif
#ifdef ANSI
  void qlocsc(real *s, real *t, int *lflag)
#else
  void qlocsc(s, t, lflag)
  real *s, *t;
  int  *lflag;
#endif
{
  int iostat;
# ifdef __WATCOMC__
    int (__far *mouse_ptr)();
    static int MOUSE = 0x33;
    struct SREGS sreg;
    union REGS kreg;
# else
#   include "xglblc.h"
    XButtonEvent *xbe;
# endif
 
  *s = spen;
  *t = tpen;
  bflshc();
  if (intact){
    if ((lcdvc==LT_MOUSE) || (lcdvc==LT_TABLET)) {
#     ifdef __WATCOMC__
        segread(&sreg);
        kreg.w.ax = 0;
        int386(MOUSE, &kreg, &kreg);     /* Check for a mouse driver. */
        if (kreg.w.ax == 0xffff){
          kreg.w.ax = 4;
          kreg.w.cx = imouse;
          kreg.w.dx = jmouse;
          int386(MOUSE, &kreg, &kreg);  /* Initialize mouse location. */
          kreg.w.ax = 1;
          int386(MOUSE, &kreg, &kreg);       /* Display mouse cursor. */
          kreg.w.ax  = 12;
          kreg.w.cx  = 0x0002 + 0x0008; /* Set mask for both buttons. */
          mouse_ptr  = (int (__far *)()) mouse_handler;
          kreg.x.edx = FP_OFF(mouse_ptr);
          sreg.es    = FP_SEG(mouse_ptr);
          int386x(MOUSE, &kreg, &kreg, &sreg);
          event = FALSE;
          while (!event){     /* Read mouse position at button press. */
            continue;
          }
          kreg.w.ax = 2;
          int386(MOUSE, &kreg, &kreg);          /* Hide mouse cursor. */
          kreg.w.ax = 0;
          int386(MOUSE, &kreg, &kreg);        /* Clear mouse handler. */
          *s = imouse / 640.0;
          *t = 1.0 - jmouse / 480.0;
        } else {
          do {
            textc(
              "Enter (S,T) coordinates as percent of screen size: > ",
              FALSE);
            if ((iostat = bfinc("/")) == 1) continue;
            if (iostat == 0){
              *s = relrdc(spen, &iostat);
              if (iostat != 0) continue;
              *t = relrdc(tpen, &iostat);
              if (iostat != 0) continue;
            }
            break;
          } while (TRUE);
        }
#     else
        cursrc(TRUE);
        xbe = (XButtonEvent *) xloopc(ButtonPressMask);
        PixtoAbs(*s, *t, xbe->x, xbe->y);
        cursrc(FALSE);
#     endif
      lspen = FALSE;
    } else {
      do {
        textc("Enter (S,T) coordinates as percent of screen size: > ",
          FALSE);
        if ((iostat = bfinc("/")) == 1) continue;
        if (iostat == 0){
          *s = relrdc(spen, &iostat);
          if (iostat != 0) continue;
          *t = relrdc(tpen, &iostat);
          if (iostat != 0) continue;
        }
        break;
      } while (TRUE);
    }
  }
  *lflag = (*s >= smin) && (*s <= smax) && (*t >= tmin) && (*t <= tmax);
  return;
}

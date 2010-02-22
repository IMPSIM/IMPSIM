/* ------------------------------------------------------------------ */
/* symblc-01 Jan 00:13 Aug 03
|     (C)Copyright, JJU Research, 2000-2003.
|
|     Description:
|       Draw a stroke generated symbol corresponding to one of the
|     character set at the current graphic pen location.
|
|     Access:
|       (void) symblc(char chr);
|     char chr,i-The character whose symbol is to be generated.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       The width of stroke generated characters should be defined by a
|     previous call to chsizc().  The default character width is 0.0125
|     screen units.
|       This routine will output only stroke generated characters, no
|     matter whether chsizc() has been called.
|       This routine is intended for character output on the graphic
|     screen rather than the the alphanumeric screen.  Text output on
|     the alphanumeric screen may be accomplished by a call to textc().
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  void symblc(char chr)
#else
  void symblc(chr)
  char chr;
#endif
{
# define RECSIZE 160
  int  mesh[20][2];
  int  i, j, k, nrec;
  real delta, pixels, s, t, s0, t0;
 
/* Set a local origin such that the pen is at (2,2). */
  if (lunsmb <= 0) return;
  if (spen + ssymbl > smax) return;
  pixels = ssymbl / 7.0;
  s0 = spen - 2.0 * pixels;
  t0 = tpen - 2.0 * pixels;
 
/* Get the coded symbol strokes from the symbol file. */
  lspen = FALSE;
  nrec = (int) chr;
  fseek(streams[lunsmb], (nrec * RECSIZE), SEEK_SET);
  fscanf(streams[lunsmb], "%160c", mesh);
 
/* Loop through the specified strokes. */
  for (k=0; k<20; k++){
    i = mesh[k][0];
    j = mesh[k][1];
 
/* Treat (9,9) as a stop code. */
    if (i == 9){
      delta = 10.0 * pixels;
      if (j == 9){
        break;
 
/* Treat (9,8) as a pen up code. */
      } else if (j == 8){
        lspen=FALSE;
 
/* Treat (9,7) as a pen down code. */
      } else if (j == 7){
        s=spen;
        t=tpen;
        wrpenc(s, t);
 
/* Treat (9,1-4) as origin shift codes. */
      } else if (j == 1){
        t0 += delta;
      } else if (j == 2){
        t0 -= delta;
      } else if (j == 3){
        s0 += delta;
      } else if (j == 4){
        s0 -= delta;
      }
 
/* Make the next stroke. */
    } else {
      s = s0 + i * pixels;
      t = t0 + j * pixels;
      wrpenc(s, t);
    }
  }
 
/* Shift the origin for the next character. */
  s = 9.0;
  if (nrec < 16) s = 2.0;
  s = s0 + s * pixels;
  t = t0 + 2.0 * pixels;
  movasc(s, t);
  lspen = FALSE;
  return;
# undef RECSIZE
}

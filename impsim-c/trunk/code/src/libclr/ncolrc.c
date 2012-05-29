/* ------------------------------------------------------------------ */
/* ncolrc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Given one of the JJU standard color names, this routine returns
|     the JJU color number.
|
|     Access:
|       ncolor = (int) ncolrc(char *color);
|     char *color,i-JJU standard color name given.
|     int ncolor,o-Corresponding JJU color number.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       The display device must have been defined by a previous call to
|     devic().
|       If color is input as color = "" and execution is interactive,
|     then the user is prompted to enter the color name.
|       An unrecognized color name is treated as color = "white".
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
#ifdef ANSI
  int ncolrc(char *color)
#else
  int ncolrc(color)
  char *color;
#endif
{
  char choice[9];
  static char *clrtbl[MXCOLOR] = {
    "a_blue", "aqua",     "b_violet", "black",    "blue", "g_aqua",
    "green",  "o_yellow", "orange",   "r_orange", "red",  "v_red",
    "violet", "white",    "y_green",  "yellow" };
  int  high, i, lex, low, mid, nchars, nchosn;
  static int ncolr[MXCOLOR] = {
     11,       10,         13,         0,          12,      9,
      8,        5,          4,         3,           2,     15,
     14,        1,          7,         6 };
  static int namclr[MXCOLOR] = {3,13,10,9,8,7,15,14,6,5,1,0,4,2,12,11};
 
/* If the color name is not supplied, get one from the user. */
  strcpy(choice, color);
  stripc(choice);
  nchars = lenc(choice);
  choice[nchars] = '\0';
  lcasec(choice);
  if (choice[0] == '\0'){
    if (qiactc()){
_2:   textc("Enter color name: > ", FALSE);
      bfinc(" ");
      bfgetc(choice);
      stripc(choice);
      nchars = lenc(choice);
      choice[nchars] = '\0';
      lcasec(choice);
 
/* Check the response against the color table. */
      if (nchars > 0) {
        low  = 0;
        high = MXCOLOR - 1;
        while (high > low){
          mid = (high + low) / 2;
          lex = strncmp(choice, clrtbl[mid], nchars);
          if (lex > 0){
            low  = mid + 1;
          } else if (lex < 0) {
            high = mid;
          } else {
            break;
          }
        }
        mid = (high + low) / 2;
        lex = strcmp(choice, clrtbl[mid]);
        if (lex == 0) {
          if (mid > 0) {
            low = strncmp(clrtbl[mid - 1], choice, nchars);
          } else {
            low = -1;
          }
          if (mid < (MXCOLOR - 1)) {
            high = strncmp(clrtbl[mid + 1], choice, nchars);
          } else {
            high = 1;
          }
          if ((low > 0) || (high < 0)) {
            textc("Error:  Color names are not in lexical order.",
              TRUE);
            nchosn = -1;
          } else {
            if ((low < 0) && (high > 0)) {
              nchosn = mid;
            } else {
              textc("Error:  Ambiguous choice.", TRUE);
              nchosn = -1;
            }
          }
        } else {
          nchosn = -1;
        }
      } else {
        nchosn = -1;
      }
 
/* Give help for an invalid response. */
      if ((nchosn < 0) || (nchosn >= MXCOLOR)) {
        textc("Recognized color names are:", TRUE);
        for (i=0; i<MXCOLOR; i++){
          textc("  ", FALSE);
          textc(clrtbl[namclr[i]], ((i+1) % 4 == 0));
        }
        goto _2;
      }
    } else {
      nchosn = 13;
    }
  } else {
    nchosn = 13;
    for (i=0; i<MXCOLOR; i++) {
      if (strncmp(choice, clrtbl[i], nchars) == 0) {
        nchosn = i;
        break;
      }
    }
  }
  return(ncolr[nchosn]);
}

/* ------------------------------------------------------------------ */
/* cpypbl-01 Jan 84:11 Jul 09                                          |
|     (C) Copyright, JJU Research, 1984-2009.                          |
|                                                                      |
|     This material is released under the terms of the                 |
|     GNU General Public License, version 3 (GNU GPLv3).               |
|     The full text of that license is available from the 'IMPSim'     |
|     project site on Google Code.                                     |
|                                                                      |
|     This initial release of 'IMPSim' is equivalent to the            |
|     IMP Integrated Mechanisms Program (IMP-2009) and is released     |
|     with the full approval of JJU Research of Madison, WI.           |
|                                                                      |
* ------------------------------------------------------------------- */
/* ------------------------------------------------------------------ */
/* xcntc-01 Jan 00:17 Sep 07
|     (C)Copyright, JJU Research, 2000-2007.
|
|     Description:
|       Delete a specified Contact record.
|
|     Access:
|       (void) xcntc(Contact *contact);
|     Contact *contact,i-Pointer to the Contact record to be deleted.
|
|     Error Conditions:
|       None.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
* ------------------------------------------------------------------- */
 
#include "libimp.h"
#ifdef ANSI
  void xcntc(Contact *contact)
#else
  void xcntc(contact)
  Contact *contact;
#endif
{
  Contact *cnt;

  if (contact->type == CONTACT) {
    if (System.sysCnt == contact) {
      System.sysCnt = contact->nxtCnt;
    } else {
      cnt = System.sysCnt;
      while (cnt) {
        if (cnt->nxtCnt == contact) {
          cnt->nxtCnt = contact->nxtCnt;
          break;
        } else {
          cnt = cnt->nxtCnt;
        }
      }
    }
    free(contact);
  }
  return;
}

/* ------------------------------------------------------------------ */
/* licnsc-01 Jan 00:19 Nov 06
|     (C)Copyright, JJU Research, 2000-2006.
|
|     Description:
|       Check whether the current date is beyond the JJU license
|     expiration date found encrypted in file "<JJUSYS>licens.jju".
|
|     Access:
|       (void) licnsc();
|
|     Error Conditions:
|       If the file does not exist, or contains invalid data, or if the
|     license date has expired, then a message is printed and execution
|     is aborted.
|
|     Comments:
|       None.
*
*     History:
*     01 Jan 00:JJU-Original.
*     13 Aug 03:JJU-Included iobfrc.h in libcad.h.
* ------------------------------------------------------------------- */
 
#include "..\libcad\libcad.h"
void licnsc()
{
  char acode[6], fileid[MXFLCH+1], today[12];
  int i, icheck, idate, idiff, idigit, icode[5], licens, lun, ndays,
    nmonth;
  static char month[12][4] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

/* Open the file and read the encrypted license expiration. */
  strcpy(fileid, getenv("JJUSYS"));
  strcat(fileid, "licens.jju");
  lun = lunitc("file");
  if ((streams[lun] = fopen(fileid, "r")) == NULL) {
    printf("\nCannot open '%s' as the JJU license file.\n", fileid);
    abortc();
  } else {
    fscanf(streams[lun], "%6s", acode);

/* Convert the encrypted date to unencrypted integer form. */
    for (i=0; i<5; i++) icode[i] = (int) acode[i] - 32;
    licens = 0;
    icheck = 0;
    for (i=0; i<4; i++) {
      idigit = icode[3-i];
      licens = licens * 96 + idigit;
      icheck += idigit;
    }

/* Check for validity conflicts in the encrypted code. */
    icheck = (icheck - icode[4]) % 96;
    ndays  = licens % 100;
    if ((ndays < 1) || (ndays > 31)) icheck = -1;
    nmonth = (licens / 100) % 100;
    if ((nmonth < 1) || (nmonth > 12)) icheck = -2;
    if (icheck != 0) {
      printf("\n*** The file 'licens.JJU' contains invalid data. ***\n");
      abortc();
    }

/* Get today's date and convert to the same integer form. */
    datec(today);
    sscanf(today, "%2i%*7c%2i", &icode[3], &icode[1]);
    icode[2] = 0;
    for (i=0; i<12; i++) {
      if (strncmp(&today[3], month[i], 3) == 0) {
        icode[2] = i + 1;
        break;
      }
    }
    if (icode[1] > 90) {
      idate = 19;
    } else {
      idate = 20;
    }
    for (i=1; i<4; i++) idate = idate * 100 + icode[i];

/* Check whether the license has expired. */
    idiff = licens - idate;
    if (idiff < 0) {
      printf("\n*** Your JJU software license has expired. ***\n");
      abortc();
    }
    fclose(streams[lun]);

/* Warn if the license expiration date is approaching. */
_AGAIN:
    if (idiff <= 31) {
      printf("\n*** WARNING. ***\n");
      printf(
        "*** Your JJU software license expires on %2i %3s %4i. ***\n",
        ndays, month[nmonth-1], licens / 10000);
    } else if (idiff <= 100) {
      idiff -= 70;
      goto _AGAIN;
    } else if (idiff <=  1200) {
    } else if (idiff <= 10000) {
      idiff -= 8800;
      goto _AGAIN;
    }
  }
  return;
}

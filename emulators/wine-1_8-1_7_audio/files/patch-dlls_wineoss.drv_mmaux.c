--- dlls/wineoss.drv/mmaux.c.orig	2016-10-07 13:00:34.000000000 -0700
+++ dlls/wineoss.drv/mmaux.c	2014-01-10 12:37:29.000000000 -0800
@@ -97,7 +97,6 @@
     strcpyW(lpCaps->szPname, ini);
     lpCaps->szPname[9] = '0' + wDevID; /* 6  at max */
     lpCaps->wTechnology = wDevID == 2 ? AUXCAPS_CDAUDIO : AUXCAPS_AUXIN;
-    lpCaps->wReserved1 = 0;
     lpCaps->dwSupport = AUXCAPS_VOLUME | AUXCAPS_LRVOLUME;
 
     return MMSYSERR_NOERROR;

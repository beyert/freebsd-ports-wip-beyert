--- source/fltimer.cpp.orig	2021-05-05 19:30:00 UTC
+++ source/fltimer.cpp
@@ -17,7 +17,7 @@ WARRANTIES, see the file, "license.txt," in this distr
 
 #if FLEXT_OS == FLEXT_OS_WIN
 #include <windows.h>
-#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH
+#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH || FLEXT_OS_FREEBSD
 #include <unistd.h>
 #include <sys/time.h>
 #elif FLEXT_OS == FLEXT_OS_MAC
@@ -70,7 +70,7 @@ FLEXT_TEMPIMPL(double FLEXT_CLASSDEF(flext))::GetOSTim
         SystemTimeToFileTime(&systm,&fltm);
         tm = ((LARGE_INTEGER *)&fltm)->QuadPart*1.e-7;
     }
-#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH // POSIX
+#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH  || FLEXT_OS == FLEXT_OS_FREEBSD // POSIX
     timeval tmv;
     gettimeofday(&tmv,NULL);
     tm = tmv.tv_sec+tmv.tv_usec*1.e-6;
@@ -119,7 +119,7 @@ FLEXT_TEMPIMPL(void FLEXT_CLASSDEF(flext))::Sleep(doub
 #endif
         // last resort....
         ::Sleep((long)(s*1000.));
-#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH // POSIX
+#elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX || FLEXT_OSAPI == FLEXT_OSAPI_MAC_MACH || FLEXT_OS_FREEBSD // POSIX
     usleep((long)(s*1000000.));
 #elif FLEXT_OS == FLEXT_OS_MAC // that's just for OS9 & Carbon!
     UnsignedWide tick;

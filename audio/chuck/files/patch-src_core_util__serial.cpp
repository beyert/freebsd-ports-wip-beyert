--- src/core/util_serial.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/core/util_serial.cpp
@@ -34,6 +34,10 @@
 #include "chuck_errmsg.h"
 using namespace std;
 
+#ifdef __PLATFORM_FREEBSD__
+#include <limits.h>
+#endif
+
 #if defined(__MACOSX_CORE__) && !defined(__CHIP_MODE__)
 
 #include <CoreFoundation/CoreFoundation.h>
@@ -114,7 +118,7 @@ cleanup:
     return devices;
 }
 
-#elif defined(__PLATFORM_LINUX__)
+#elif defined(__PLATFORM_LINUX__) || defined(__PLATFORM_FREEBSD__)
 
 
 #include <sys/types.h>

--- src/audio/OSSAudioDevice.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/audio/OSSAudioDevice.cpp
@@ -1,6 +1,6 @@
 // OSSAudioDevice.cpp
 
-#if defined(LINUX)
+#if defined(LINUX) || defined(FREEBSD)
 
 #include <math.h>
 #include "OSSAudioDevice.h"
@@ -216,5 +216,5 @@ void OSSAudioDevice::run()
 	PRINT1("OSSAudioDevice::run: thread exiting\n");
 }
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD
 

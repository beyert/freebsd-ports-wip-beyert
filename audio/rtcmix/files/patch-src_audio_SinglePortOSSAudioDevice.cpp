--- src/audio/SinglePortOSSAudioDevice.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/audio/SinglePortOSSAudioDevice.cpp
@@ -1,6 +1,6 @@
 // SinglePortOSSAudioDevice.cpp
 
-#if defined(LINUX)
+#if defined(LINUX) || defined(FREEBSD)
 
 #include "SinglePortOSSAudioDevice.h"
 #include <sys/soundcard.h>
@@ -184,4 +184,4 @@ SinglePortOSSAudioDevice::closeDevice()
 	return status;
 }
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD

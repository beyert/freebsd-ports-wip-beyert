--- src/audio/MultiPortOSSAudioDevice.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/audio/MultiPortOSSAudioDevice.cpp
@@ -1,6 +1,6 @@
 // MultiPortOSSAudioDevice.cpp
 
-#if defined(LINUX)
+#if defined(LINUX) || defined(FREEBSD)
 
 #include "MultiPortOSSAudioDevice.h"
 #include <sys/soundcard.h>
@@ -233,4 +233,4 @@ MultiPortOSSAudioDevice::closeDevice()
 	return status;
 }
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD

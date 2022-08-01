--- src/audio/AppleAudioDevice.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/audio/AppleAudioDevice.cpp
@@ -4,6 +4,8 @@
 //
 //
 
+#ifdef APPLEAUDIO
+
 #include "AppleAudioDevice.h"
 #include <AudioUnit/AudioUnit.h>
 #include <MacTypes.h>
@@ -1655,5 +1657,7 @@ void AppleAudioDevice::parseDeviceDescription(const ch
 {
 	
 }
+#endif
+
 #endif
 

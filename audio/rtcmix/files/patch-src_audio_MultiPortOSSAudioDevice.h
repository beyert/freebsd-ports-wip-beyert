--- src/audio/MultiPortOSSAudioDevice.h.orig	2022-06-20 19:29:55 UTC
+++ src/audio/MultiPortOSSAudioDevice.h
@@ -3,7 +3,7 @@
 #ifndef _MULTI_PORT_OSS_AUDIO_DEVICE_H_
 #define _MULTI_PORT_OSS_AUDIO_DEVICE_H_
 
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 
 #include "OSSAudioDevice.h"
 
@@ -32,6 +32,6 @@ class MultiPortOSSAudioDevice : public OSSAudioDevice 
 	int *_devices;
 };
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD
 
 #endif	// _MULTI_PORT_OSS_AUDIO_DEVICE_H_

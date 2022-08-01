--- src/audio/SinglePortOSSAudioDevice.h.orig	2022-06-20 19:29:55 UTC
+++ src/audio/SinglePortOSSAudioDevice.h
@@ -3,7 +3,7 @@
 #ifndef _SINGLE_PORT_OSS_AUDIO_DEVICE_H_
 #define _SINGLE_PORT_OSS_AUDIO_DEVICE_H_
 
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 
 #include "OSSAudioDevice.h"
 
@@ -28,6 +28,6 @@ class SinglePortOSSAudioDevice : public OSSAudioDevice
 	virtual int closeDevice();
 };
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD
 
 #endif	// _SINGLE_PORT_OSS_AUDIO_DEVICE_H_

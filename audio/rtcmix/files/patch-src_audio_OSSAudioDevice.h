--- src/audio/OSSAudioDevice.h.orig	2022-06-20 19:29:55 UTC
+++ src/audio/OSSAudioDevice.h
@@ -3,7 +3,7 @@
 #ifndef _OSS_AUDIO_DEVICE_H_
 #define _OSS_AUDIO_DEVICE_H_
 
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 
 #include "ThreadedAudioDevice.h"
 
@@ -40,6 +40,6 @@ class OSSAudioDevice : public ThreadedAudioDevice { (p
 	int		_bufferSize;
 };
 
-#endif	// LINUX
+#endif	// LINUX || FREEBSD
 
 #endif	// _OSS_AUDIO_DEVICE_H_

--- src/audio/AudioFileDevice.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/audio/AudioFileDevice.cpp
@@ -11,7 +11,7 @@
 #include <assert.h>
 #include <errno.h>
 #include <string.h>
-#if defined(linux) || defined(MACOSX)
+#if defined(linux) || defined(FREEBSD) || defined(MACOSX)
 #include <unistd.h>
 #endif
 
@@ -176,7 +176,7 @@ void AudioFileDevice::run()
 	
 	while (!stopping()) {
 		while (paused()) {
-#ifdef linux
+#if defined(linux) || defined(FREEBSD)
 			::usleep(1000);
 #endif
 		}

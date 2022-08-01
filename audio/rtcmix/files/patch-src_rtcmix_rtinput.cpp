--- src/rtcmix/rtinput.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/rtinput.cpp
@@ -21,9 +21,9 @@
 #include <Option.h>
 #include "audio_devices.h"
 #include "InputFile.h"
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
    #include <fcntl.h>
-#endif /* LINUX */
+#endif /* LINUX || FREEBSD */
 
 /* code that lets user specify buses for input sources */
 //#define INPUT_BUS_SUPPORT

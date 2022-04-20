--- src/core/util_hid.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/core/util_hid.cpp
@@ -6308,7 +6308,7 @@ int Keyboard_close( int js )
 
 
 
-#elif defined(__PLATFORM_LINUX__)
+#elif defined(__PLATFORM_LINUX__) || defined(__PLATFORM_FREEBSD__)
 /*****************************************************************************
 Linux general HID support
 *****************************************************************************/
@@ -6318,7 +6318,9 @@ Linux general HID support
 #include <sys/stat.h>
 #include <unistd.h>
 #include <dirent.h>
+#ifdef __PLATFORM_LINUX__
 #include <linux/unistd.h>
+#endif
 #include <string.h>
 #include <fcntl.h>
 #include <sys/poll.h>
@@ -6326,6 +6328,9 @@ Linux general HID support
 #include <errno.h>
 #include <linux/joystick.h>
 #include <linux/input.h>
+#ifdef __PLATFORM_FREEBSD__
+#include <linux/types.h>
+#endif
 
 #define CK_HID_DIR ("/dev/input")
 #define CK_HID_MOUSEFILE ("mouse%d")

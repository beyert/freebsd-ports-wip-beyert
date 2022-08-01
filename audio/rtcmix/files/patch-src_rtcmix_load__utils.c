--- src/rtcmix/load_utils.c.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/load_utils.c
@@ -9,7 +9,7 @@
 
 #include "load_utils.h"
 
-#if (defined(MACOSX) && !defined(JAGUAR)) || defined(LINUX)
+#if (defined(MACOSX) && !defined(JAGUAR)) || defined(LINUX) || defined(FREEBSD)
 
 #include <dlfcn.h>
 

--- src/rtcmix/TaskManager.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/TaskManager.cpp
@@ -17,7 +17,7 @@
 #include <stdio.h>
 #include <assert.h>
 
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 #include <sys/time.h>
 #include <sys/resource.h>
 #endif

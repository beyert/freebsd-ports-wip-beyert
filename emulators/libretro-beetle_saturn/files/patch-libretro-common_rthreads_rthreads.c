--- libretro-common/rthreads/rthreads.c.orig	2021-06-09 14:45:41 UTC
+++ libretro-common/rthreads/rthreads.c
@@ -55,7 +55,7 @@
 #include <time.h>
 #endif
 
-#if defined(VITA) || defined(BSD) || defined(ORBIS)
+#if defined(VITA) || defined(__FreeBSD__) || defined(ORBIS)
 #include <sys/time.h>
 #endif
 

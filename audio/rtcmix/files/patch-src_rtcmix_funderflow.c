--- src/rtcmix/funderflow.c.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/funderflow.c
@@ -20,7 +20,7 @@ void flush_all_underflows_to_zero()
 }
 #endif
 
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 
 #include <stdio.h>
 #include <stdlib.h>

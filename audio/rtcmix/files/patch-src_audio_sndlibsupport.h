--- src/audio/sndlibsupport.h.orig	2022-06-20 19:29:55 UTC
+++ src/audio/sndlibsupport.h
@@ -6,7 +6,7 @@
 #ifndef _SNDLIB_SUPPORT_H_
 #define _SNDLIB_SUPPORT_H_
 
-#if defined(LINUX)
+#if defined(LINUX) && !defined(FREEBSD)
 #include <endian.h>      /* so that sndlib.h will get host byte-order right */
 #elif defined(MACOSX)
 #include <machine/endian.h>

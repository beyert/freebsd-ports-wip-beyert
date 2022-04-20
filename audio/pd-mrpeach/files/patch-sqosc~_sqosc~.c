--- sqosc~/sqosc~.c.orig	2017-07-12 21:05:29 UTC
+++ sqosc~/sqosc~.c
@@ -32,6 +32,8 @@
 
 #if defined(__FreeBSD__) || defined(__APPLE__)
 #include <machine/endian.h>
+#define __LITTLE_ENDIAN _LITTLE_ENDIAN
+#define __BYTE_ORDER _BYTE_ORDER
 #endif
 
 #ifdef __APPLE__

--- plugins/zerogs/opengl/common/PS2Etypes.h.orig	2014-01-24 10:07:16.000000000 -0800
+++ plugins/zerogs/opengl/common/PS2Etypes.h	2014-03-23 14:47:09.000000000 -0700
@@ -91,7 +91,7 @@
 
 #else // _MSC_VER
 
-#ifdef __LINUX__
+#ifdef __FreeBSD__
 
 #ifdef HAVE_STDINT_H
 #include "stdint.h"

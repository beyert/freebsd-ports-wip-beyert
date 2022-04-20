--- plugins/CDVDlinuz/Src/convert.h.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/convert.h	2014-03-23 14:55:16.000000000 -0700
@@ -82,7 +82,7 @@
 
 
 
-extern off64_t ConvertEndianOffset(off64_t number);
+extern off_t ConvertEndianOffset(off_t number);
 
 extern unsigned int ConvertEndianUInt(unsigned int number);
 

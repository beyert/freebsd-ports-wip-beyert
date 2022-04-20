--- plugins/CDVDlinuz/Src/convert.c.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/convert.c	2014-03-23 14:55:52.000000000 -0700
@@ -52,15 +52,15 @@
 
 
 
-off64_t ConvertEndianOffset(off64_t number) {
+off_t ConvertEndianOffset(off_t number) {
 
 #ifndef CONVERTLITTLEENDIAN
 
   union {
 
-    off64_t n;
+    off_t n;
 
-    char c[sizeof(off64_t)];
+    char c[sizeof(off_t)];
 
   } oldnumber, newnumber;
 
@@ -70,9 +70,9 @@
 
   oldnumber.n = number;
 
-  for(i = 0; i < sizeof(off64_t); i++)
+  for(i = 0; i < sizeof(off_t); i++)
 
-    newnumber.c[i] = oldnumber.c[sizeof(off64_t) - 1 - i];
+    newnumber.c[i] = oldnumber.c[sizeof(off_t) - 1 - i];
 
   return(newnumber.n);
 

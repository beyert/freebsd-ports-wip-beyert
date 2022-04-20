--- plugins/CDVDlinuz/Src/Linux/actualfile.h.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/Linux/actualfile.h	2014-03-23 14:56:25.000000000 -0700
@@ -48,7 +48,7 @@
 
 
 
-#include <sys/types.h> // off64_t
+#include <sys/types.h> // off_t
 
 
 
@@ -78,9 +78,9 @@
 
 extern ACTUALHANDLE ActualFileOpenForRead(const char *filename);
 
-extern off64_t ActualFileSize(ACTUALHANDLE handle);
+extern off_t ActualFileSize(ACTUALHANDLE handle);
 
-extern int ActualFileSeek(ACTUALHANDLE handle, off64_t position);
+extern int ActualFileSeek(ACTUALHANDLE handle, off_t position);
 
 extern int ActualFileRead(ACTUALHANDLE handle, int bytes, char *buffer);
 

--- plugins/CDVDlinuz/Src/Linux/actualfile.c.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/Linux/actualfile.c	2014-03-23 17:12:46.000000000 -0700
@@ -48,11 +48,11 @@
 
 #include <string.h> // strerror()
 
-#include <sys/stat.h> // stat64(), open(), fstat()
+#include <sys/stat.h> // stat(), open(), fstat()
 
-#include <sys/types.h> // stat64(), open(), fstat(), lseek64()
+#include <sys/types.h> // stat(), open(), fstat(), lseek()
 
-#include <unistd.h> // stat64(), fstat(), lseek64(), read(), close(), write()
+#include <unistd.h> // stat(), fstat(), lseek(), read(), close(), write()
 
 // unlink()
 
@@ -70,7 +70,7 @@
 
   int retval;
 
-  struct stat64 filestat;
+  struct stat filestat;
 
 
 
@@ -84,7 +84,7 @@
 
   errno = 0;
 
-  retval = stat64(filename, &filestat);
+  retval = stat(filename, &filestat);
 
   if((retval < 0) || (errno != 0)) {
 
@@ -170,6 +170,7 @@
 
   errno = 0;
 
+#define O_LARGEFILE         0200000
   newhandle = open(filename, O_RDONLY | O_LARGEFILE);
 
   if((newhandle < 0) || (errno != 0)) {
@@ -196,11 +197,11 @@
 
 
 
-off64_t ActualFileSize(ACTUALHANDLE handle) {
+off_t ActualFileSize(ACTUALHANDLE handle) {
 
   int retval;
 
-  struct stat64 filestat;
+  struct stat filestat;
 
 
 
@@ -214,7 +215,7 @@
 
   errno = 0;
 
-  retval = fstat64(handle, &filestat);
+  retval = fstat(handle, &filestat);
 
   if((retval < 0) || (errno != 0))  return(-1); // Name doesn't exist.
 
@@ -226,9 +227,9 @@
 
 
 
-int ActualFileSeek(ACTUALHANDLE handle, off64_t position) {
+int ActualFileSeek(ACTUALHANDLE handle, off_t position) {
 
-  off64_t moved;
+  off_t moved;
 
 
 
@@ -248,7 +249,7 @@
 
   errno = 0;
 
-  moved = lseek64(handle, position, SEEK_SET);
+  moved = lseek(handle, position, SEEK_SET);
 
   if(errno != 0) {
 

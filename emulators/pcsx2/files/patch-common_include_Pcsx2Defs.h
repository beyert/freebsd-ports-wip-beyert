--- common/include/Pcsx2Defs.h.orig	2014-01-24 10:07:19.000000000 -0800
+++ common/include/Pcsx2Defs.h	2014-03-23 14:45:51.000000000 -0700
@@ -20,7 +20,7 @@
 #define WX_PCSX2
 
 // some distributions are lower case
-#if defined (__linux__) || defined(__CYGWIN__)
+#if defined (__linux__) || defined(__CYGWIN__) || defined(__FreeBSD__)
 #if !defined(__LINUX__)
 #	define __LINUX__
 #endif

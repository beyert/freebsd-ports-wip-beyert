--- vst/Interface.h.orig	2022-02-11 10:14:58 UTC
+++ vst/Interface.h
@@ -12,6 +12,7 @@
 #define VST_WINDOWS 0
 #define VST_MACOS 1
 #define VST_LINUX 2
+#define VST_FREEBSD 3
 
 // overriden when building Wine!
 #ifndef VST_HOST_SYSTEM
@@ -21,6 +22,8 @@
 #  define VST_HOST_SYSTEM VST_MACOS
 # elif defined(__linux__)
 #  define VST_HOST_SYSTEM VST_LINUX
+# elif defined(__FreeBSD__)
+#  define VST_HOST_SYSTEM VST_FREEBSD
 # else
 #  error "unsupported host system"
 # endif

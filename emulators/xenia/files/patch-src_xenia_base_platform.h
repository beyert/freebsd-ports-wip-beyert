--- src/xenia/base/platform.h.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/base/platform.h
@@ -37,6 +37,8 @@
 #elif defined(__gnu_linux__)
 #define XE_PLATFORM_GNU_LINUX 1
 #define XE_PLATFORM_LINUX 1
+#elif defined(__FreeBSD__)
+#define XE_PLATFORM_FREEBSD 1
 #else
 #error Unsupported target OS.
 #endif

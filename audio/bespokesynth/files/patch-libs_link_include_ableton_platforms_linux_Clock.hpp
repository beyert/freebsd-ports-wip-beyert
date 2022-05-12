--- libs/link/include/ableton/platforms/linux/Clock.hpp.orig	2021-12-03 12:55:21 UTC
+++ libs/link/include/ableton/platforms/linux/Clock.hpp
@@ -32,7 +32,7 @@ namespace platforms
 #undef linux
 #endif
 
-#if defined(__FreeBSD_kernel__)
+#if defined(__FreeBSD__)
 #define CLOCK_MONOTONIC_RAW CLOCK_MONOTONIC
 #endif
 

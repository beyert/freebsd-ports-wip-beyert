--- src/core/util_string.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/core/util_string.cpp
@@ -41,6 +41,10 @@
 #include <linux/limits.h>
 #endif // __PLATFORM_LINUX__
 
+#ifdef __PLATFORM_FREEBSD__
+#include <limits.h>
+#endif
+
 #include <stdio.h>
 using namespace std;
 

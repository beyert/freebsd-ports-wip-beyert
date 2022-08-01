--- src/rtcmix/atomic_stack.h.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/atomic_stack.h
@@ -6,7 +6,10 @@
 //#if MAC_OS_X_VERSION_MAX_ALLOWED < MAC_OS_X_VERSION_10_4
 //#include <CoreServices/CoreServices.h>
 //#endif
-#elif defined(LINUX)
+#elif defined(LINUX) || defined(FREEBSD)
+#ifdef FREEBSD
+#include <stdatomic.h>
+#endif
 template <class T>
 static bool	compare_and_swap(T *oldvalue, T *newvalue, T **pvalue);
 #endif

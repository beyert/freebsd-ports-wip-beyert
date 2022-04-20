--- src/xenia/base/atomic.h.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/base/atomic.h
@@ -94,7 +94,7 @@ inline bool atomic_cas(int64_t old_value, int64_t new_
              old_value) == old_value;
 }
 
-#elif XE_PLATFORM_LINUX
+#elif XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
 
 inline int32_t atomic_inc(volatile int32_t* value) {
   return __sync_add_and_fetch(value, 1);

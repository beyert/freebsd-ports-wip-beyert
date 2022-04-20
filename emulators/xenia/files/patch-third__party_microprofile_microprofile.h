--- third_party/microprofile/microprofile.h.orig	2021-06-09 19:56:36 UTC
+++ third_party/microprofile/microprofile.h
@@ -242,7 +242,7 @@ typedef uint32_t MicroProfileThreadIdType;
 #define MP_GETCURRENTPROCESSID() GetCurrentProcessId()
 typedef uint32_t MicroProfileProcessIdType;
 
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 #include <unistd.h>
 #include <time.h>
 inline int64_t MicroProfileTicksPerSecondCpu()

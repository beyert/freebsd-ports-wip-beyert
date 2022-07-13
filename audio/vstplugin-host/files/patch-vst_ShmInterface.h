--- vst/ShmInterface.h.orig	2022-02-11 10:14:58 UTC
+++ vst/ShmInterface.h
@@ -27,6 +27,11 @@
 # endif
 #endif
 
+#if VST_HOST_SYSTEM == VST_FREEBSD
+#  define SHM_SEMAPHORE 1
+//#  define SHM_EVENT 1
+#endif
+
 // Windows: we use unnamed Events and duplicate the handles in the child process.
 // This *might* be more efficient than using named Events.
 #if VST_HOST_SYSTEM == VST_WINDOWS

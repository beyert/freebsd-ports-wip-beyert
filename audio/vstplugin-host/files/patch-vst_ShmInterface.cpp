--- vst/ShmInterface.cpp.orig	2022-02-11 10:14:58 UTC
+++ vst/ShmInterface.cpp
@@ -23,6 +23,9 @@
 #  include <semaphore.h>
 #  if VST_HOST_SYSTEM == VST_MACOS
 #   include <sys/stat.h>
+#  elif VST_HOST_SYSTEM == VST_FREEBSD
+#   include <sys/stat.h>
+#   include <sys/event.h>
 #  endif
 # endif
 #endif

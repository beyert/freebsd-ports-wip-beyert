--- vst/MiscUtils.cpp.orig	2022-02-11 10:14:58 UTC
+++ vst/MiscUtils.cpp
@@ -15,6 +15,7 @@
 # include <dlfcn.h>
 # include <unistd.h>
 # include <fcntl.h>
+# include <sys/wait.h>
 #endif
 
 #if VST_HOST_SYSTEM != VST_WINDOWS

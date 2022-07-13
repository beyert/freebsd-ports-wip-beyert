--- vst/CpuArch.cpp.orig	2022-02-11 10:14:58 UTC
+++ vst/CpuArch.cpp
@@ -23,9 +23,12 @@
 # include <mach-o/fat.h>
 #endif
 
-#if defined(__linux__)
+#if defined(__linux__) || defined(__FreeBSD__)
 # include <elf.h>
 #endif
+#if defined(__FreeBSD__)
+# include <unistd.h>
+#endif
 
 #if USE_WINE
 // avoid including Wine headers just for a few defines
@@ -357,6 +360,9 @@ static const std::vector<const char *> gBundleBinaryPa
 #if defined(__linux__)
     "Contents/i386-linux", "Contents/x86_64-linux"
 #endif
+#if defined(__FreeBSD__)
+    "Contents/i386-freebsd", "Contents/amd64-freebsd"
+#endif
 };
 
 static const std::vector<const char *> gBundleBinaryExtensions = {
@@ -368,6 +374,9 @@ static const std::vector<const char *> gBundleBinaryEx
     "",
 #endif
 #if defined(__linux__)
+    ".so"
+#endif
+#if defined(__FreeBSD__)
     ".so"
 #endif
 };

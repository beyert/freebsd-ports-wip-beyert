--- reicast-emulator/core/libretro/common.cpp.orig	2017-01-26 09:26:17.000000000 -0800
+++ reicast-emulator/core/libretro/common.cpp	2017-02-13 23:52:49.355413000 -0800
@@ -292,7 +292,7 @@
 }
 #endif
 
-#if defined(__MACH__) || defined(__linux__)
+#if defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__)
 //#define LOG_SIGHANDLER
 
 static void fault_handler (int sn, siginfo_t * si, void *segfault_ctx)

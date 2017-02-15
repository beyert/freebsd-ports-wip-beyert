--- reicast-emulator/core/hw/sh4/dyna/driver.cpp.orig	2017-01-26 09:26:17.000000000 -0800
+++ reicast-emulator/core/hw/sh4/dyna/driver.cpp	2017-02-13 22:36:29.102610000 -0800
@@ -36,6 +36,8 @@
 	;
 #elif defined(__linux__)
 	__attribute__((section(".text")));
+#elif defined(__FreeBSD__)
+	__attribute__((section(".text")));
 #elif defined(__MACH__)
 	__attribute__((section("__TEXT,.text")));
 #else

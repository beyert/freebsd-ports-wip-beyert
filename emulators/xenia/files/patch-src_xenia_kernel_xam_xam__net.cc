--- src/xenia/kernel/xam/xam_net.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/kernel/xam/xam_net.cc
@@ -26,7 +26,7 @@
 // NOTE: must be included last as it expects windows.h to already be included.
 #define _WINSOCK_DEPRECATED_NO_WARNINGS  // inet_addr
 #include <winsock2.h>                    // NOLINT(build/include_order)
-#elif XE_PLATFORM_LINUX
+#elif XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
 #include <arpa/inet.h>
 #include <netinet/in.h>
 #include <netinet/ip.h>

--- speexin~.c.orig	2021-07-29 21:45:22 UTC
+++ speexin~.c
@@ -50,7 +50,7 @@
 #define SOCKET_ERROR -1
 #endif
 
-#if defined(__APPLE__) || defined(_WIN32)
+#if defined(__APPLE__) || defined(__FreeBSD__) || defined(_WIN32)
 #define MSG_NOSIGNAL 0
 #define SOL_TCP IPPROTO_TCP
 #endif

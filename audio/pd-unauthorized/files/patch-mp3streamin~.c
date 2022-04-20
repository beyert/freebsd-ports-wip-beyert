--- mp3streamin~.c.orig	2021-07-29 21:45:22 UTC
+++ mp3streamin~.c
@@ -57,7 +57,7 @@
 #define SOCKET_ERROR -1
 #endif /* _WIN32 */
 
-#if defined(__APPLE__) || defined(_WIN32)
+#if defined(__APPLE__) || defined(__FreeBSD__) || defined(_WIN32)
 #define MSG_NOSIGNAL 0
 #define SOL_TCP IPPROTO_TCP
 #endif

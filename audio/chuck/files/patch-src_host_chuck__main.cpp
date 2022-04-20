--- src/host/chuck_main.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/host/chuck_main.cpp
@@ -170,6 +170,10 @@ static void version()
     platform = "microsoft win32 + cygwin";
 #elif defined(__LINUX_ALSA__)
     platform = "linux (alsa)";
+#elif defined(__FREEBSD_ALSA__)
+    platform = "freebsd (alsa)";
+#elif defined(__FREEBSD_OSS__)
+    platform = "freebsd (oss)";
 #elif defined(__LINUX_OSS__)
     platform = "linux (oss)";
 #elif defined(__LINUX_JACK__) || defined(__UNIX_JACK__)

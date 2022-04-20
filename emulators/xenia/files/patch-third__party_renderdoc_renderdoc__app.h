--- third_party/renderdoc/renderdoc_app.h.orig	2021-06-09 19:56:36 UTC
+++ third_party/renderdoc/renderdoc_app.h
@@ -30,7 +30,7 @@
 
 #if defined(WIN32)
 	#define RENDERDOC_CC __cdecl
-#elif defined(__linux__)
+#elif defined(__linux__) || defined(__FreeBSD__)
 	#define RENDERDOC_CC
 #else
 	#error "Unknown platform"

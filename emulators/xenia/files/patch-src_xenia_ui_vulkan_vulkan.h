--- src/xenia/ui/vulkan/vulkan.h.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/ui/vulkan/vulkan.h
@@ -14,6 +14,8 @@
 
 #if XE_PLATFORM_WIN32
 #define VK_USE_PLATFORM_WIN32_KHR 1
+#elif XE_PLATFORM_FREEBSD
+#define VK_USE_PLATFORM_XCB_KHR 1
 #elif XE_PLATFORM_LINUX
 #define VK_USE_PLATFORM_XCB_KHR 1
 #else

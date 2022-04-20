--- src/xenia/ui/vulkan/vulkan_context.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/ui/vulkan/vulkan_context.cc
@@ -25,7 +25,7 @@
 #include "xenia/ui/vulkan/vulkan_util.h"
 #include "xenia/ui/window.h"
 
-#if XE_PLATFORM_LINUX
+#if XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
 #include "xenia/ui/window_gtk.h"
 
 #include <X11/Xlib-xcb.h>
@@ -69,7 +69,7 @@ bool VulkanContext::Initialize() {
     status = vkCreateWin32SurfaceKHR(*provider->instance(), &create_info,
                                      nullptr, &surface);
     CheckResult(status, "vkCreateWin32SurfaceKHR");
-#elif XE_PLATFORM_LINUX
+#elif XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
 #ifdef GDK_WINDOWING_X11
     GtkWidget* window_handle =
         static_cast<GtkWidget*>(target_window_->native_handle());

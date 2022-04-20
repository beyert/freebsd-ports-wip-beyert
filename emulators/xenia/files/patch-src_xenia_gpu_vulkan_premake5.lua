--- src/xenia/gpu/vulkan/premake5.lua.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/gpu/vulkan/premake5.lua
@@ -52,8 +52,8 @@ project("xenia-gpu-vulkan-trace-viewer")
     "fmt",
     "glslang-spirv",
     "imgui",
-    "libavcodec",
-    "libavutil",
+    "avcodec",
+    "avutil",
     "mspack",
     "snappy",
     "spirv-tools",
@@ -121,8 +121,8 @@ project("xenia-gpu-vulkan-trace-dump")
     "fmt",
     "glslang-spirv",
     "imgui",
-    "libavcodec",
-    "libavutil",
+    "avcodec",
+    "avutil",
     "mspack",
     "snappy",
     "spirv-tools",

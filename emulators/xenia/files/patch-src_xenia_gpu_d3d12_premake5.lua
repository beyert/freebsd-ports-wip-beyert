--- src/xenia/gpu/d3d12/premake5.lua.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/gpu/d3d12/premake5.lua
@@ -46,8 +46,8 @@ project("xenia-gpu-d3d12-trace-viewer")
     "dxbc",
     "fmt",
     "imgui",
-    "libavcodec",
-    "libavutil",
+    "avcodec",
+    "avutil",
     "mspack",
     "snappy",
     "xxhash",
@@ -93,8 +93,8 @@ project("xenia-gpu-d3d12-trace-dump")
     "dxbc",
     "fmt",
     "imgui",
-    "libavcodec",
-    "libavutil",
+    "avcodec",
+    "avutil",
     "mspack",
     "snappy",
     "xxhash",

--- src/xenia/apu/premake5.lua.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/apu/premake5.lua
@@ -7,8 +7,8 @@ project("xenia-apu")
   kind("StaticLib")
   language("C++")
   links({
-    "libavcodec",
-    "libavutil",
+    "avcodec",
+    "avutil",
     "xenia-base",
   })
   defines({

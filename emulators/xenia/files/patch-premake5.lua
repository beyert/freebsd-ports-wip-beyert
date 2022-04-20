--- premake5.lua.orig	2021-06-09 19:56:36 UTC
+++ premake5.lua
@@ -21,11 +21,14 @@ includedirs({
   ".",
   "src",
   "third_party",
+  "third_party/nowide/include",
 })
 
 defines({
   "_UNICODE",
   "UNICODE",
+  "BOOST_NOWIDE_USE_FILEBUF_REPLACEMENT",
+  "BOOST_NOWIDE_FSTREAM_INCLUDED_HPP",
 })
 
 cppdialect("C++17")
@@ -102,7 +105,6 @@ filter("platforms:Linux")
   })
   pkg_config.all("gtk+-x11-3.0")
   links({
-    "stdc++fs",
     "dl",
     "lz4",
     "pthread",

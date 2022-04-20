--- cmake/PdExternal.cmake.orig	2018-03-11 19:32:35 UTC
+++ cmake/PdExternal.cmake
@@ -42,6 +42,10 @@ endif()
 
 if(CMAKE_SYSTEM_NAME MATCHES "Linux")
   set(PD_EXTERNAL_SUFFIX ".pd_linux")
+elseif(CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
+  set(PD_EXTERNAL_SUFFIX ".pd_freebsd")
+elseif(CMAKE_SYSTEM_NAME MATCHES "OpenBSD")
+  set(PD_EXTERNAL_SUFFIX ".pd_openbsd")
 elseif(CMAKE_SYSTEM_NAME MATCHES "Darwin")
   set(PD_EXTERNAL_SUFFIX ".pd_darwin")
 elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")

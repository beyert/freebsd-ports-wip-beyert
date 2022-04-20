--- cmake/FindLibc.cmake.orig	2014-01-24 10:07:08.000000000 -0800
+++ cmake/FindLibc.cmake	2014-03-23 21:53:33.000000000 -0700
@@ -8,9 +8,8 @@
 endif(LIBC_LIBRARIES)
 
 find_library(librt NAMES rt)
-find_library(libdl NAMES dl)
 find_library(libm NAMES m)
-set(LIBC_LIBRARIES ${librt} ${libdl} ${libm})
+set(LIBC_LIBRARIES ${librt} ${libm})
 
 # handle the QUIETLY and REQUIRED arguments and set LIBC_FOUND to TRUE if 
 # all listed variables are TRUE

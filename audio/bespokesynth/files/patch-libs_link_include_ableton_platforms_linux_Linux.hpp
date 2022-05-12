--- libs/link/include/ableton/platforms/linux/Linux.hpp.orig	2021-12-03 12:55:21 UTC
+++ libs/link/include/ableton/platforms/linux/Linux.hpp
@@ -19,7 +19,7 @@
 
 #pragma once
 
-#include <byteswap.h>
+#include <infiniband/byteswap.h>
 
 #ifndef ntohll
 #define ntohll(x) bswap_64(x)

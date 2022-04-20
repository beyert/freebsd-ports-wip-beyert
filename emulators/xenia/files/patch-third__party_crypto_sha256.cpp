--- third_party/crypto/sha256.cpp.orig	2021-06-09 19:56:36 UTC
+++ third_party/crypto/sha256.cpp
@@ -9,7 +9,7 @@
 
 // big endian architectures need #define __BYTE_ORDER __BIG_ENDIAN
 #ifndef _MSC_VER
-#include <endian.h>
+#include <sys/endian.h>
 #endif
 
 namespace sha256 {
@@ -573,4 +573,4 @@ std::string SHA256::operator()(const std::string& text
   return getHash();
 }
 
-}
\ No newline at end of file
+}

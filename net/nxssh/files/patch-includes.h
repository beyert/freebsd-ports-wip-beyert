--- includes.h.orig	2018-11-25 15:34:22 UTC
+++ includes.h
@@ -163,6 +163,7 @@
 
 #ifdef WITH_OPENSSL
 #include <openssl/opensslv.h> /* For OPENSSL_VERSION_NUMBER */
+#include "libcrypto-compat.h"
 #endif
 
 #include "defines.h"

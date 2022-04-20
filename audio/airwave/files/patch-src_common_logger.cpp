--- src/common/logger.cpp.orig	2020-07-15 17:59:39 UTC
+++ src/common/logger.cpp
@@ -4,7 +4,7 @@
 #include <cstring>
 #include <ctime>
 #include <unistd.h>
-#include <linux/un.h>
+#include <sys/un.h>
 #include <sys/socket.h>
 #include <vector>
 #include "common/types.h"

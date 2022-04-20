--- src/common/event.cpp.orig	2021-11-03 18:29:52.141564000 -0700
+++ src/common/event.cpp	2021-11-04 12:36:51.732148000 -0700
@@ -1,10 +1,10 @@
 #include "event.h"
 
 #include <errno.h>
-#include <syscall.h>
+#include <sys/syscall.h>
 #include <time.h>
 #include <unistd.h>
-#include <linux/futex.h>
+#include <linux/linux_futex.h>
 
 
 #define futex_wait(futex, count, timeout) \

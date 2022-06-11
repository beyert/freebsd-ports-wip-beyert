--- src/common/event.cpp.orig	2020-07-15 17:59:39 UTC
+++ src/common/event.cpp
@@ -1,17 +1,19 @@
 #include "event.h"
 
 #include <errno.h>
-#include <syscall.h>
+#include <sys/syscall.h>
 #include <time.h>
 #include <unistd.h>
-#include <linux/futex.h>
+#include <linux/linux_futex.h>
 
+#define __NR_futex 98
+#define SYS_futex __NR_futex
 
 #define futex_wait(futex, count, timeout) \
-		(syscall(SYS_futex, futex, FUTEX_WAIT, count, timeout, nullptr, 0) == 0)
+		(syscall(SYS_futex, futex, LINUX_FUTEX_WAIT, count, timeout, nullptr, 0) == 0)
 
 #define futex_post(futex, count) \
-		(syscall(SYS_futex, futex, FUTEX_WAKE, count, nullptr, nullptr, 0) == 0)
+		(syscall(SYS_futex, futex, LINUX_FUTEX_WAKE, count, nullptr, nullptr, 0) == 0)
 
 
 Event::Event() :

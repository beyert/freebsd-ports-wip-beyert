--- src/vfs/vfs-file-monitor.c.orig	2018-03-04 16:04:33 UTC
+++ src/vfs/vfs-file-monitor.c
@@ -20,6 +20,8 @@
 #include "config.h"
 #endif
 
+#include <sys/inotify.h>
+
 #include "vfs-file-monitor.h"
 #include "vfs-file-info.h"
 #include <sys/types.h>  /* for stat */

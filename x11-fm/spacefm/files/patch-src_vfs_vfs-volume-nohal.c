--- src/vfs/vfs-volume-nohal.c.orig	2018-03-04 16:04:33 UTC
+++ src/vfs/vfs-volume-nohal.c
@@ -35,8 +35,10 @@
 #include <sys/wait.h>
 
 #include <signal.h>  // kill
-#include <linux/kdev_t.h>  // MAJOR MINOR
-#include <sys/sysmacros.h> // needed for dev_t
+/* 3 lines taken from /usr/include/linux/kdev_t.h on ubuntu 20 (GPLv2) */
+#define MAJOR(dev)  ((dev)>>8)
+#define MINOR(dev)  ((dev) & 0xff)
+#define MKDEV(ma,mi)    ((ma)<<8 | (mi))
 
 #ifdef HAVE_STATVFS
 #include <sys/statvfs.h>

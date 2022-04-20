
--- plugins/CDVDlinuz/Src/Linux/CD.c.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/Linux/CD.c	2014-03-23 17:30:44.000000000 -0700
@@ -56,7 +56,15 @@
 
 
 
+#if __LINUX__
 #include <linux/cdrom.h> // CD/DVD based ioctl() and defines.
+
+#elif __FreeBSD__
+/* thanks audio/xcdplayer/files/cdrom_freebsd.h */
+#include <sys/cdio.h>
+#define CDROM_LBA CD_LBA_FORMAT
+#define CDROM_MSF 0x02
+#endif
 
 
 

--- src/settings.c.orig	2018-03-04 16:04:33 UTC
+++ src/settings.c
@@ -21,6 +21,7 @@
 #include <stdlib.h>
 #include <unistd.h>
 #include <sys/stat.h>
+#include <sys/wait.h> /* for WIFEXITED */
 
 #include "glib-utils.h" /* for g_mkdir_with_parents() */
 #include <glib/gi18n.h>

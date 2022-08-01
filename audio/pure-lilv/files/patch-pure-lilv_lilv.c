--- pure-lilv/lilv.c.orig	2018-04-11 15:45:42 UTC
+++ pure-lilv/lilv.c
@@ -12,7 +12,11 @@
 #include <stdlib.h>
 #include <unistd.h>
 #include <string.h>
-#include <alloca.h>
+
+/* #define __GNUC__ 2 */
+#include <stdlib.h>
+#undef  alloca	/* some GNU bits try to get cute and define this on their own */
+#define alloca(sz) __builtin_alloca(sz)
 
 #include <pure/runtime.h>
 

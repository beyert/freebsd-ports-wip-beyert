--- pluginhost~/pluginhost~.c.orig	2015-03-19 11:46:31 UTC
+++ pluginhost~/pluginhost~.c
@@ -21,6 +21,7 @@
 
 #include <sys/wait.h>
 #include <stdlib.h>
+#include <sys/signal.h>
 
 #include "ph_common.h"
 #include "handlers_pd.h"

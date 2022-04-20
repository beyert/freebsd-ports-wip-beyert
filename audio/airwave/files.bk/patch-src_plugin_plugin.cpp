--- src/plugin/plugin.cpp.orig	2021-11-03 18:29:52.147416000 -0700
+++ src/plugin/plugin.cpp	2021-11-04 12:33:42.760586000 -0700
@@ -5,11 +5,12 @@
 #include <sys/wait.h>
 #include "common/logger.h"
 #include "common/protocol.h"
+#include <signal.h>
 
-
 #define XEMBED_EMBEDDED_NOTIFY	0
 #define XEMBED_FOCUS_OUT		5
 #define kVstExtMaxParamStrLen	24
+// #define SIGKILL 9
 
 namespace Airwave {
 

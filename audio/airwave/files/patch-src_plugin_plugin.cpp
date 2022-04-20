--- src/plugin/plugin.cpp.orig	2020-07-15 17:59:39 UTC
+++ src/plugin/plugin.cpp
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
 

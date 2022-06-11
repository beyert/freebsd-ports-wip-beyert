--- src/common/logger.h.orig	2020-07-15 17:59:39 UTC
+++ src/common/logger.h
@@ -3,6 +3,8 @@
 
 #include <string>
 
+/* same value as in /usr/include/linux/un.h on Ubuntu bionic */
+#define UNIX_PATH_MAX 108
 
 #define FLOOD(format, ...) \
 		Airwave::loggerMessage(Airwave::LogLevel::kFlood, format, ##__VA_ARGS__)

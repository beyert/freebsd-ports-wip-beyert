--- src/manager/core/logsocket.cpp.orig	2020-07-15 17:59:39 UTC
+++ src/manager/core/logsocket.cpp
@@ -3,11 +3,13 @@
 #include <cerrno>
 #include <cstring>
 #include <unistd.h>
-#include <linux/un.h>
+#include <sys/un.h>
 #include <sys/ioctl.h>
 #include <sys/socket.h>
 #include <QByteArray>
 
+/* same value as in /usr/include/linux/un.h on Ubuntu bionic */
+#define UNIX_PATH_MAX 108
 
 LogSocket::LogSocket(QObject* parent) :
 	QObject(parent),

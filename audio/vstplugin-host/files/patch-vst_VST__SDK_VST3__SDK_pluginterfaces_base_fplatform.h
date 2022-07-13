--- vst/VST_SDK/VST3_SDK/pluginterfaces/base/fplatform.h.orig	2021-12-16 12:29:35 UTC
+++ vst/VST_SDK/VST3_SDK/pluginterfaces/base/fplatform.h
@@ -39,6 +39,7 @@
 //-----------------------------------------------------------------------------
 #if defined (_WIN32)
 	//-----------------------------------------------------------------------------
+	#define SMTG_OS_FREEBSD	0
 	#define SMTG_OS_LINUX	0
 	#define SMTG_OS_MACOS	0
 	#define SMTG_OS_WINDOWS	1
@@ -114,8 +115,9 @@
 //-----------------------------------------------------------------------------
 // LINUX
 //-----------------------------------------------------------------------------
-#elif __gnu_linux__ || __linux__
-	#define SMTG_OS_LINUX	1
+#elif __gnu_linux__ || __linux__ || defined(__FreeBSD__)
+	#define SMTG_OS_FREEBSD	1
+	#define SMTG_OS_LINUX	0
 	#define SMTG_OS_MACOS	0
 	#define SMTG_OS_WINDOWS	0
 	#define SMTG_OS_IOS		0
@@ -127,7 +129,7 @@
 	#define SMTG_CPU_ARM_64	__aarch64__
 	#define SMTG_CPU_ARM_64EC 0
 
-	#include <endian.h>
+	#include <sys/endian.h>
 	#if __BYTE_ORDER == __LITTLE_ENDIAN
 		#define BYTEORDER kLittleEndian
 	#else
@@ -165,6 +167,7 @@
 //-----------------------------------------------------------------------------
 #elif __APPLE__
 	#include <TargetConditionals.h>
+	#define SMTG_OS_FREEBSD	0
 	#define SMTG_OS_LINUX	0
 	#define SMTG_OS_MACOS	1
 	#define SMTG_OS_WINDOWS	0

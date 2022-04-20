--- plugins/CDVDlinuz/Src/PS2Edefs.h.orig	2014-01-24 10:07:13.000000000 -0800
+++ plugins/CDVDlinuz/Src/PS2Edefs.h	2014-03-23 14:53:07.000000000 -0700
@@ -33,7 +33,7 @@
 
 #include "PS2Etypes.h"
 
-#ifdef __LINUX__
+#ifdef __FreeBSD__
 #define CALLBACK
 #else
 #include <windows.h>
@@ -70,6 +70,39 @@
 #define PS2E_USB_VERSION  0x0003
 #define PS2E_FW_VERSION   0x0002
 #define PS2E_SIO_VERSION  0x0001
+#ifdef __FreeBSD__
+
+#ifdef HAVE_STDINT_H
+#include "stdint.h"
+
+typedef int8_t s8;
+typedef int16_t s16;
+typedef int32_t s32;
+typedef int64_t s64;
+
+typedef uint8_t u8;
+typedef uint16_t u16;
+typedef uint32_t u32;
+typedef uint64_t u64;
+
+typedef uintptr_t uptr;
+typedef intptr_t sptr;
+
+#else // HAVE_STDINT_H
+
+typedef char s8;
+typedef short s16;
+typedef int s32;
+typedef long long s64;
+
+typedef unsigned char u8;
+typedef unsigned short u16;
+typedef unsigned int u32;
+typedef unsigned long long u64;
+
+#endif // HAVE_STDINT_H
+#endif // __FreeBSD__
+
 #ifdef COMMONdefs
 
 u32   CALLBACK PS2EgetLibType(void);

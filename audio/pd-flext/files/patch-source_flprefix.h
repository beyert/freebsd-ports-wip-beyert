--- source/flprefix.h.orig	2021-05-05 19:30:00 UTC
+++ source/flprefix.h
@@ -48,8 +48,13 @@ WARRANTIES, see the file, "license.txt," in this distr
 #define FLEXT_OS_WIN    1
 #define FLEXT_OS_MAC    2  
 #define FLEXT_OS_LINUX  3
-#define FLEXT_OS_IRIX   4
+#define FLEXT_OS_FREEBSD  4
+#define FLEXT_OS_IRIX   5
 
+#if defined(__FreeBSD__)
+	#define FLEXT_OS FLEXT_OS_FREEBSD
+#endif
+
 // --- definitions for FLEXT_OS_API ---------------------
 #define FLEXT_OSAPI_UNKNOWN 0
 
@@ -228,6 +233,55 @@ WARRANTIES, see the file, "license.txt," in this distr
     // This is important for everything
     #pragma bool on
 
+#elif (FLEXT_OS == FLEXT_OS_FREEBSD || defined(freebsd) || defined(__freebsd__))
+
+    #ifndef FLEXT_CPU
+        #if defined(__amd64__)
+            #define FLEXT_CPU FLEXT_CPU_X86_64
+        #elif defined(_X86_) || defined(__i386__) || defined(__i586__) || defined(__i686__)
+            #define FLEXT_CPU FLEXT_CPU_IA32
+        #elif defined(__ppc64__)
+            #define FLEXT_CPU FLEXT_CPU_PPC64
+        #elif defined(__ppc__)
+            #define FLEXT_CPU FLEXT_CPU_PPC
+        #elif defined(__MIPS__)
+            #define FLEXT_CPU FLEXT_CPU_MIPS
+        #else
+            #define FLEXT_CPU FLEXT_CPU_UNKNOWN
+        #endif
+    #endif
+
+    #ifndef FLEXT_OS
+        #if defined(freebsd) || defined(__FreeBSD__)
+            #define FLEXT_OS FLEXT_OS_FREEBSD
+        #elif defined(__CYGWIN__) || defined(__CYGWIN32__) || defined(__MINGW32__)
+            #define FLEXT_OS FLEXT_OS_WIN
+        #elif defined(__APPLE__) && defined(__MACH__)
+            #define FLEXT_OS FLEXT_OS_MAC
+        // how about IRIX??
+        #else
+            #define FLEXT_OS FLEXT_OS_UNKNOWN
+        #endif
+    #endif
+
+    #ifndef FLEXT_OSAPI
+        #if FLEXT_OS == FLEXT_OS_MAC
+            #define FLEXT_OSAPI FLEXT_OSAPI_MAC_MACH
+        #elif FLEXT_OS == FLEXT_OS_FREEBSD
+            #define FLEXT_OSAPI FLEXT_OSAPI_UNIX_POSIX
+        #elif FLEXT_OS == FLEXT_OS_WIN
+            #if defined(__MINGW32__)
+                #define FLEXT_OSAPI FLEXT_OSAPI_WIN_NATIVE
+            #else
+                #define FLEXT_OSAPI FLEXT_OSAPI_WIN_POSIX
+            #endif
+        #elif FLEXT_OS == FLEXT_OS_LINUX || FLEXT_OS == FLEXT_OS_IRIX
+            #define FLEXT_OSAPI FLEXT_OSAPI_UNIX_POSIX
+        #else
+            #define FLEXT_OSAPI FLEXT_OSAPI_UNKNOWN
+        #endif
+    #endif
+
 #elif defined(__GNUG__) || (defined(__ICC) && (FLEXT_OS == FLEXT_OS_LINUX || defined(linux) || defined(__linux__)))
 
     // GNU C++
@@ -323,6 +377,14 @@ WARRANTIES, see the file, "license.txt," in this distr
     #endif
 #elif FLEXT_OS == FLEXT_OS_LINUX
 //  #pragma message("Compiling for Linux")
+
+    #if FLEXT_SYS == FLEXT_SYS_PD
+//      #define PD
+    #else
+        #error "Flext SYS/OS combination unknown"
+    #endif
+#elif FLEXT_OS == FLEXT_OS_FREEBSD
+//  #pragma message("Compiling for FreeBSD")
 
     #if FLEXT_SYS == FLEXT_SYS_PD
 //      #define PD

--- src/core/util_console.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/core/util_console.cpp
@@ -95,6 +95,9 @@ void io_addhistory( const char * addme )
 #ifdef __PLATFORM_MACOSX__
   #include <termios.h>
   static struct termios g_save;
+#elif defined(__PLATFORM_FREEBSD__)
+  #include <termios.h>
+  static struct termios g_save;
 #else
   #include <termio.h>
   static struct termio g_save;
@@ -102,8 +105,8 @@ void io_addhistory( const char * addme )
 
   #include <unistd.h>
   #include <sys/ioctl.h>
-#else
-  #include <conio.h>
+//#else
+//  #include <conio.h>
 #endif
 
 
@@ -122,6 +125,9 @@ t_CKBOOL kb_initscr()
 #ifdef __PLATFORM_MACOSX__
     struct termios term;
     if( ioctl( 0, TIOCGETA, &term ) == -1 )
+#elif defined(__PLATFORM_FREEBSD__)
+    struct termios term;
+    if( ioctl( 0, TIOCGETA, &term ) == -1 )
 #else
     struct termio term;
     if( ioctl( 0, TCGETA, &term ) == -1 )
@@ -144,6 +150,8 @@ t_CKBOOL kb_initscr()
 
 #ifdef __PLATFORM_MACOSX__
     ioctl( 0, TIOCSETA, &term );
+#elif defined(__PLATFORM_FREEBSD__)
+    ioctl( 0, TIOCSETA, &term );
 #else
     ioctl( 0, TCSETA, &term );
 #endif
@@ -162,6 +170,8 @@ void kb_endwin()
 
 #ifndef __PLATFORM_WIN32__
 #ifdef __PLATFORM_MACOSX__
+    ioctl( 0, TIOCSETA, &g_save );
+#elif defined(__PLATFORM_FREEBSD__)
     ioctl( 0, TIOCSETA, &g_save );
 #else
     ioctl( 0, TCSETA, &g_save );

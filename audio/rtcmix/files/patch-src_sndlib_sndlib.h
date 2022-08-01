--- src/sndlib/sndlib.h.orig	2022-06-20 19:29:55 UTC
+++ src/sndlib/sndlib.h
@@ -91,7 +91,7 @@
 /* due to project builder stupidity, we can't always depend on -D flags here (maybe we need a SNDLIB_OS macro?) */
 /* these wouldn't work with autoconf anyway, so we'll do it by hand */
 
-#if (!defined(SGI)) && (!defined(NEXT)) && (!defined(LINUX)) && (!defined(MACOS)) && (!defined(SUN)) && (!defined(UW2)) && (!defined(SCO5)) && (!defined(ALPHA)) && (!defined(WINDOZE)) && (!defined(MAC_OSX))
+#if (!defined(SGI)) && (!defined(NEXT)) && (!defined(LINUX)) && (!defined(FREEBSD)) && (!defined(MACOS)) && (!defined(SUN)) && (!defined(UW2)) && (!defined(SCO5)) && (!defined(ALPHA)) && (!defined(WINDOZE)) && (!defined(MAC_OSX))
   #if defined(__dest_os)
     /* we're in Metrowerks Land */
     #if (__dest_os == __mac_os)
@@ -138,7 +138,7 @@
 #ifndef ESD
 #ifndef HAVE_OSS
 #ifndef HAVE_ALSA
-  #if defined(LINUX) || defined(SCO5) || defined(UW2) || defined(HAVE_SOUNDCARD_H) || defined(HAVE_SYS_SOUNDCARD_H) || defined(HAVE_MACHINE_SOUNDCARD_H) || defined(USR_LIB_OSS) || defined(USR_LOCAL_LIB_OSS) || defined(OPT_OSS) || defined(VAR_LIB_OSS) || defined(__FreeBSD__) || defined(__bsdi__)
+  #if defined(LINUX) || defined(FREEBSD) || defined(SCO5) || defined(UW2) || defined(HAVE_SOUNDCARD_H) || defined(HAVE_SYS_SOUNDCARD_H) || defined(HAVE_MACHINE_SOUNDCARD_H) || defined(USR_LIB_OSS) || defined(USR_LOCAL_LIB_OSS) || defined(OPT_OSS) || defined(VAR_LIB_OSS) || defined(__FreeBSD__) || defined(__bsdi__)
     #define HAVE_OSS 1
   #else
     #define HAVE_OSS 0

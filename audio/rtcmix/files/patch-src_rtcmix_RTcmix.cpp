--- src/rtcmix/RTcmix.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/RTcmix.cpp
@@ -51,7 +51,7 @@ extern "C" {
 #ifdef SGI
   void flush_all_underflows_to_zero();
 #endif
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
   void sigfpe_handler(int sig);
 #endif
 }
@@ -273,7 +273,7 @@ RTcmix::free_globals()
    the exception is thrown doesn't mean there's a serious problem.  For
    more info, see: http://www.smartelectronix.com/musicdsp/text/other001.txt.
 */
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 #ifdef DENORMAL_CHECK
 static void
 detect_denormals()
@@ -285,7 +285,7 @@ detect_denormals()
    _FPU_SETCW(cw);
 }
 #endif /* DENORMAL_CHECK */
-#endif /* LINUX */
+#endif /* LINUX || FREEBSD */
 
 //  The RTcmix constructor with default SR, NCHANS, and RTBUFSAMPS
 RTcmix::RTcmix() 

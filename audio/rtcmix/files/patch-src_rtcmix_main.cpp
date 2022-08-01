--- src/rtcmix/main.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/main.cpp
@@ -39,7 +39,7 @@ extern "C" {
 #ifdef SGI
   void flush_all_underflows_to_zero();
 #endif
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
   void sigfpe_handler(int sig);
 #endif
 }
@@ -53,7 +53,7 @@ extern "C" {
    the exception is thrown doesn't mean there's a serious problem.  For
    more info, see: http://www.musicdsp.org/files/other001.txt.
 */
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
 #ifdef DENORMAL_CHECK
 static void
 detect_denormals()
@@ -65,7 +65,7 @@ detect_denormals()
    _FPU_SETCW(cw);
 }
 #endif /* DENORMAL_CHECK */
-#endif /* LINUX */
+#endif /* LINUX || FREEBSD */
 
 
 #ifndef EMBEDDED
@@ -74,12 +74,12 @@ detect_denormals()
 int
 main(int argc, char *argv[], char **env)
 {
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
  #ifdef DENORMAL_CHECK
    detect_denormals();
  #endif
    signal(SIGFPE, sigfpe_handler);          /* Install signal handler */
-#endif /* LINUX */
+#endif /* LINUX || FREEBSD */
 #ifdef SGI
    flush_all_underflows_to_zero();
 #endif

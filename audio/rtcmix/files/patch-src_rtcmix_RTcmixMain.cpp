--- src/rtcmix/RTcmixMain.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/rtcmix/RTcmixMain.cpp
@@ -58,7 +58,7 @@ usage()
 #ifdef OSC
       "           -o       run with background OSC server\n"
 #endif
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
       "           -p NUM   set process priority to NUM (as root only)\n"
 #endif
       "           -D NAME  audio device name\n"
@@ -231,7 +231,7 @@ void
 RTcmixMain::parseArguments(int argc, char **argv, char **env)
 {
    int         i;
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
    int		   priority = 0;
 #endif
    int		   printlevel = 5;
@@ -299,7 +299,7 @@ RTcmixMain::parseArguments(int argc, char **argv, char
                }
 				Option::print(printlevel);
                break;
-#ifdef LINUX
+#if defined(LINUX) || defined(FREEBSD)
             case 'p':
                if (++i >= argc) {
                   fprintf(stderr, "You didn't give a priority number.\n");
@@ -420,7 +420,7 @@ RTcmixMain::run()
 
            /* Create scheduling thread. */
            rtcmix_debug(NULL, "calling runMainLoop()");
-           retcode = runMainLoop();
+           retcode = RTcmix::runMainLoop();
            if (retcode != 0) {
               rterror(NULL, "runMainLoop() failed\n");
            }
@@ -470,7 +470,7 @@ RTcmixMain::run()
     
           /* Create scheduling thread. */
           rtcmix_debug(NULL, "calling runMainLoop()");
-          retcode = runMainLoop();
+          retcode = RTcmix::runMainLoop();
           if (retcode != 0) {
              rterror(NULL, "runMainLoop() failed\n");
           }
@@ -518,7 +518,7 @@ RTcmixMain::run()
 //			 	perror("setpriority");
 #endif
 		 rtcmix_debug(NULL, "RTcmixMain::run: calling runMainLoop()");
-		  if ((status = runMainLoop()) == 0) {
+		  if ((status = RTcmix::runMainLoop()) == 0) {
 			 rtcmix_debug(NULL, "RTcmixMain::run: calling waitForMainLoop()");
 			 waitForMainLoop();
 		  }
@@ -648,7 +648,8 @@ RTcmixMain::sockit(void *arg)
     // socknew is offset from MYPORT to allow more than one inst
     sss.sin_port = htons(MYPORT+socknew);
 
-    err = bind(s, (struct sockaddr *)&sss, sizeof(sss));
+    // :: implies usage of C extern over C++ method
+    err = ::bind(s, (struct sockaddr *)&sss, sizeof(sss));
     if (err < 0) {
       perror("bind");
 	  run_status = RT_ERROR;	// Notify inTraverse()

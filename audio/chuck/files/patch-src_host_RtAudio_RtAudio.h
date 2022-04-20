--- src/host/RtAudio/RtAudio.h.orig	2021-08-16 04:08:51 UTC
+++ src/host/RtAudio/RtAudio.h
@@ -222,7 +222,9 @@ class RtAudio
   enum Api {
     UNSPECIFIED,    /*!< Search for a working compiled API. */
     LINUX_ALSA,     /*!< The Advanced Linux Sound Architecture API. */
+    FREEBSD_ALSA,     /*!< FreeBSD Advanced Linux Sound Architecture API. */
     LINUX_PULSE,    /*!< The Linux PulseAudio API. */
+    FREEBSD_OSS,      /*!< The FreeBSD Open Sound System API. */
     LINUX_OSS,      /*!< The Linux Open Sound System API. */
     UNIX_JACK,      /*!< The Jack Low-Latency Audio Server API. */
     MACOSX_CORE,    /*!< Macintosh OS-X Core Audio API. */
@@ -532,7 +534,7 @@ class RtAudio
   typedef unsigned long ThreadHandle;
   typedef CRITICAL_SECTION StreamMutex;
 
-#elif defined(__LINUX_ALSA__) || defined(__LINUX_PULSE__) || defined(__UNIX_JACK__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__)
+#elif defined(__LINUX_ALSA__) || defined (__FREEBSD_ALSA__) || defined(__LINUX_PULSE__) || defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__)
   // Using pthread library for various flavors of unix.
   #include <pthread.h>
 
@@ -935,7 +937,7 @@ class RtApiDs: public RtApi (public)
 
 #endif
 
-#if defined(__LINUX_ALSA__)
+#if defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__)
 
 class RtApiAlsa: public RtApi
 {
@@ -943,7 +945,11 @@ class RtApiAlsa: public RtApi (public)
 
   RtApiAlsa();
   ~RtApiAlsa();
+#if defined(__LINUX_ALSA__)
   RtAudio::Api getCurrentApi() { return RtAudio::LINUX_ALSA; }
+#elif defined(__FREEBSD_ALSA__)
+  RtAudio::Api getCurrentApi() { return RtAudio::FREEBSD_ALSA; }
+#endif
   unsigned int getDeviceCount( void );
   RtAudio::DeviceInfo getDeviceInfo( unsigned int device );
   void closeStream( void );
@@ -1001,7 +1007,7 @@ class RtApiPulse: public RtApi (public)
 
 #endif
 
-#if defined(__LINUX_OSS__)
+#if defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
 
 class RtApiOss: public RtApi
 {
@@ -1009,7 +1015,11 @@ class RtApiOss: public RtApi (public)
 
   RtApiOss();
   ~RtApiOss();
+#if defined(__FREEBSD_OSS__)
+  RtAudio::Api getCurrentApi() { return RtAudio::FREEBSD_OSS; }
+#elif defined(__LINUX_OSS__)
   RtAudio::Api getCurrentApi() { return RtAudio::LINUX_OSS; }
+#endif
   unsigned int getDeviceCount( void );
   RtAudio::DeviceInfo getDeviceInfo( unsigned int device );
   void closeStream( void );

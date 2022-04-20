--- src/host/RtAudio/RtAudio.cpp.orig	2021-10-23 23:48:40 UTC
+++ src/host/RtAudio/RtAudio.cpp
@@ -58,7 +58,7 @@ const unsigned int RtApi::SAMPLE_RATES[] = {
   #define MUTEX_DESTROY(A)    DeleteCriticalSection(A)
   #define MUTEX_LOCK(A)       EnterCriticalSection(A)
   #define MUTEX_UNLOCK(A)     LeaveCriticalSection(A)
-#elif defined(__LINUX_ALSA__) || defined(__LINUX_PULSE__) || defined(__UNIX_JACK__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__)
+#elif defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__) || defined(__LINUX_PULSE__) || defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__) || defined(__MACOSX_CORE__)
   // pthread API
   #define MUTEX_INITIALIZE(A) pthread_mutex_init(A, NULL)
   #define MUTEX_DESTROY(A)    pthread_mutex_destroy(A)
@@ -87,9 +87,15 @@ void RtAudio :: getCompiledApi( std::vector<RtAudio::A
 #if defined(__LINUX_ALSA__)
   apis.push_back( LINUX_ALSA );
 #endif
+#if defined(__FREEBSD_ALSA__)
+  apis.push_back( FREEBSD_ALSA );
+#endif
 #if defined(__LINUX_PULSE__)
   apis.push_back( LINUX_PULSE );
 #endif
+#if defined(__FREEBSD_OSS__)
+  apis.push_back( FREEBSD_OSS );
+#endif
 #if defined(__LINUX_OSS__)
   apis.push_back( LINUX_OSS );
 #endif
@@ -121,10 +127,18 @@ void RtAudio :: openRtApi( RtAudio::Api api )
   if ( api == LINUX_ALSA )
     rtapi_ = new RtApiAlsa();
 #endif
+#if defined(__FREEBSD_ALSA__)
+  if ( api == FREEBSD_ALSA )
+    rtapi_ = new RtApiAlsa();
+#endif
 #if defined(__LINUX_PULSE__)
   if ( api == LINUX_PULSE )
     rtapi_ = new RtApiPulse();
 #endif
+#if defined(__FREEBSD_OSS__)
+  if ( api == FREEBSD_OSS )
+    rtapi_ = new RtApiOss();
+#endif
 #if defined(__LINUX_OSS__)
   if ( api == LINUX_OSS )
     rtapi_ = new RtApiOss();
@@ -5262,7 +5276,7 @@ static const char* getErrorString( int code )
 #endif
 
 
-#if defined(__LINUX_ALSA__)
+#if defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__)
 
 #include <alsa/asoundlib.h>
 #include <unistd.h>
@@ -6529,7 +6543,7 @@ static void *alsaCallbackHandler( void *ptr )
   pthread_exit( NULL );
 }
 
-//******************** End of __LINUX_ALSA__ *********************//
+//******************** End of __LINUX_ALSA__ || __FREEBSD_ALSA__ *********************//
 #endif
 
 #if defined(__LINUX_PULSE__)
@@ -7006,13 +7020,17 @@ bool RtApiPulse::probeDeviceOpen( unsigned int device,
 //******************** End of __LINUX_PULSE__ *********************//
 #endif
 
-#if defined(__LINUX_OSS__)
+#if defined(__FREEBSD_OSS__) ||defined(__LINUX_OSS__)
 
 #include <unistd.h>
 #include <sys/ioctl.h>
 #include <unistd.h>
 #include <fcntl.h>
+#if defined(__FREEBSD_OSS__)
+#include <sys/soundcard.h>
+#elif defined(__LINUX_OSS__)
 #include "soundcard.h"
+#endif
 #include <errno.h>
 #include <math.h>
 
@@ -7444,7 +7462,7 @@ bool RtApiOss :: probeDeviceOpen( unsigned int device,
   }
 
   // Verify the sample rate setup worked.
-  if ( abs( srate - sampleRate ) > 100 ) {
+  if ( abs(int(srate - sampleRate)) > 100 ) {
     close( fd );
     errorStream_ << "RtApiOss::probeDeviceOpen: device (" << ainfo.name << ") does not support sample rate (" << sampleRate << ").";
     errorText_ = errorStream_.str();

--- src/core/rtmidi.cpp.orig	2021-08-16 04:08:51 UTC
+++ src/core/rtmidi.cpp
@@ -5,10 +5,11 @@
     This class implements some common functionality for the realtime
     MIDI input/output subclasses RtMidiIn and RtMidiOut.
 
-    RtMidi WWW site: http://music.mcgill.ca/~gary/rtmidi/
+    RtMidi GitHub site: https://github.com/thestk/rtmidi
+    RtMidi WWW site: http://www.music.mcgill.ca/~gary/rtmidi/
 
     RtMidi: realtime MIDI i/o C++ classes
-    Copyright (c) 2003-2005 Gary P. Scavone
+    Copyright (c) 2003-2019 Gary P. Scavone
 
     Permission is hereby granted, free of charge, to any person
     obtaining a copy of this software and associated documentation files
@@ -22,8 +23,9 @@
     included in all copies or substantial portions of the Software.
 
     Any person wishing to distribute modifications to the Software is
-    requested to send the modifications to the original developer so that
-    they can be incorporated into the canonical version.
+    asked to send the modifications to the original developer so that
+    they can be incorporated into the canonical version.  This is,
+    however, not a binding provision of this license.
 
     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
     EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
@@ -35,75 +37,609 @@
 */
 /**********************************************************************/
 
-// RtMidi: Version 1.0.4, 14 October 2005
-
-// chuck
 #include "rtmidi.h"
 #include <sstream>
-#include <iostream>
-#include <stdio.h>
 
+#if defined(TARGET_OS_IPHONE)
 
+    #define AudioGetCurrentHostTime CAHostTimeBase::GetCurrentTime
+    #define AudioConvertHostTimeToNanos CAHostTimeBase::ConvertToNanos
+
+    #include <mach/mach_time.h>
+    class CTime2nsFactor
+    {
+    public:
+        CTime2nsFactor()
+        {
+            mach_timebase_info_data_t tinfo;
+            mach_timebase_info(&tinfo);
+            Factor = (double)tinfo.numer / tinfo.denom;
+        }
+        static double Factor;
+    };
+    double CTime2nsFactor::Factor;
+    static CTime2nsFactor InitTime2nsFactor;
+    #undef AudioGetCurrentHostTime
+    #undef AudioConvertHostTimeToNanos
+  #define AudioGetCurrentHostTime (uint64_t) mach_absolute_time
+  #define AudioConvertHostTimeToNanos(t) t *CTime2nsFactor::Factor
+  #define EndianS32_BtoN(n) n
+
+#endif
+
+// Default for Windows is to add an identifier to the port names; this
+// flag can be defined (e.g. in your project file) to disable this behaviour.
+//#define RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES
+
+// **************************************************************** //
+//
+// MidiInApi and MidiOutApi subclass prototypes.
+//
+// **************************************************************** //
+
+#if !defined(__LINUX_ALSA__) && !defined(__FREEBSD_ALSA__) && !defined(__FREEBSD_OSS__) && !defined(__LINUX_OSS__) && !defined(__UNIX_JACK__) && !defined(__MACOSX_CORE__) && !defined(__WINDOWS_MM__) && !defined(TARGET_IPHONE_OS)
+  #define __RTMIDI_DUMMY__
+#endif
+
+#if defined(__MACOSX_CORE__)
+
+class MidiInCore: public MidiInApi
+{
+ public:
+  MidiInCore( const std::string &clientName, unsigned int queueSizeLimit );
+  ~MidiInCore( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::MACOSX_CORE; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName );
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+class MidiOutCore: public MidiOutApi
+{
+ public:
+  MidiOutCore( const std::string &clientName );
+  ~MidiOutCore( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::MACOSX_CORE; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName );
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+  void sendMessage( const unsigned char *message, size_t size );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+#endif
+
+#if defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
+
+class MidiInJack: public MidiInApi
+{
+ public:
+  MidiInJack( const std::string &clientName, unsigned int queueSizeLimit );
+  ~MidiInJack( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::UNIX_JACK; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName);
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+
+ protected:
+  std::string clientName;
+
+  void connect( void );
+  void initialize( const std::string& clientName );
+};
+
+class MidiOutJack: public MidiOutApi
+{
+ public:
+  MidiOutJack( const std::string &clientName );
+  ~MidiOutJack( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::UNIX_JACK; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName);
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+  void sendMessage( const unsigned char *message, size_t size );
+
+ protected:
+  std::string clientName;
+
+  void connect( void );
+  void initialize( const std::string& clientName );
+};
+
+#endif
+
+#if defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__)
+
+class MidiInAlsa: public MidiInApi
+{
+ public:
+  MidiInAlsa( const std::string &clientName, unsigned int queueSizeLimit );
+  ~MidiInAlsa( void );
+#if defined(__LINUX_ALSA__)
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::LINUX_ALSA; };
+#else
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::FREEBSD_ALSA; };
+#endif
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName);
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+class MidiOutAlsa: public MidiOutApi
+{
+ public:
+  MidiOutAlsa( const std::string &clientName );
+  ~MidiOutAlsa( void );
+#if defined(__LINUX_ALSA__)
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::LINUX_ALSA; };
+#else
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::FREEBSD_ALSA; };
+#endif
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName );
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+  void sendMessage( const unsigned char *message, size_t size );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+#endif
+
+#if defined(__WINDOWS_MM__)
+
+class MidiInWinMM: public MidiInApi
+{
+ public:
+  MidiInWinMM( const std::string &clientName, unsigned int queueSizeLimit );
+  ~MidiInWinMM( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::WINDOWS_MM; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName );
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+class MidiOutWinMM: public MidiOutApi
+{
+ public:
+  MidiOutWinMM( const std::string &clientName );
+  ~MidiOutWinMM( void );
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::WINDOWS_MM; };
+  void openPort( unsigned int portNumber, const std::string &portName );
+  void openVirtualPort( const std::string &portName );
+  void closePort( void );
+  void setClientName( const std::string &clientName );
+  void setPortName( const std::string &portName );
+  unsigned int getPortCount( void );
+  std::string getPortName( unsigned int portNumber );
+  void sendMessage( const unsigned char *message, size_t size );
+
+ protected:
+  void initialize( const std::string& clientName );
+};
+
+#endif
+
+#if defined(__RTMIDI_DUMMY__)
+
+class MidiInDummy: public MidiInApi
+{
+ public:
+ MidiInDummy( const std::string &/*clientName*/, unsigned int queueSizeLimit ) : MidiInApi( queueSizeLimit ) { errorString_ = "MidiInDummy: This class provides no functionality."; error( RtMidiError::WARNING, errorString_ ); }
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::RTMIDI_DUMMY; }
+  void openPort( unsigned int /*portNumber*/, const std::string &/*portName*/ ) {}
+  void openVirtualPort( const std::string &/*portName*/ ) {}
+  void closePort( void ) {}
+  void setClientName( const std::string &/*clientName*/ ) {};
+  void setPortName( const std::string &/*portName*/ ) {};
+  unsigned int getPortCount( void ) { return 0; }
+  std::string getPortName( unsigned int /*portNumber*/ ) { return ""; }
+
+ protected:
+  void initialize( const std::string& /*clientName*/ ) {}
+};
+
+class MidiOutDummy: public MidiOutApi
+{
+ public:
+  MidiOutDummy( const std::string &/*clientName*/ ) { errorString_ = "MidiOutDummy: This class provides no functionality."; error( RtMidiError::WARNING, errorString_ ); }
+  RtMidi::Api getCurrentApi( void ) { return RtMidi::RTMIDI_DUMMY; }
+  void openPort( unsigned int /*portNumber*/, const std::string &/*portName*/ ) {}
+  void openVirtualPort( const std::string &/*portName*/ ) {}
+  void closePort( void ) {}
+  void setClientName( const std::string &/*clientName*/ ) {};
+  void setPortName( const std::string &/*portName*/ ) {};
+  unsigned int getPortCount( void ) { return 0; }
+  std::string getPortName( unsigned int /*portNumber*/ ) { return ""; }
+  void sendMessage( const unsigned char * /*message*/, size_t /*size*/ ) {}
+
+ protected:
+  void initialize( const std::string& /*clientName*/ ) {}
+};
+
+#endif
+
 //*********************************************************************//
-//  Common RtMidi Definitions
+//  RtMidi Definitions
 //*********************************************************************//
 
 RtMidi :: RtMidi()
-  : apiData_( 0 ), connected_( false )
+  : rtapi_(0)
 {
 }
 
-// chuck
-void RtMidi :: error( RtMidiError::Type type )
+RtMidi :: ~RtMidi()
 {
-  if (type == RtMidiError::WARNING) {
-    std::cerr << "[chuck](via RtMidi): " << errorString_ << "\n";
+  delete rtapi_;
+  rtapi_ = 0;
+}
+
+std::string RtMidi :: getVersion( void ) throw()
+{
+  return std::string( RTMIDI_VERSION );
+}
+
+// Define API names and display names.
+// Must be in same order as API enum.
+extern "C" {
+const char* rtmidi_api_names[][2] = {
+  { "unspecified" , "Unknown" },
+  { "core"        , "CoreMidi" },
+  { "alsa"        , "ALSA" },
+  { "jack"        , "Jack" },
+  { "winmm"       , "Windows MultiMedia" },
+  { "dummy"       , "Dummy" },
+};
+const unsigned int rtmidi_num_api_names =
+  sizeof(rtmidi_api_names)/sizeof(rtmidi_api_names[0]);
+
+// The order here will control the order of RtMidi's API search in
+// the constructor.
+extern "C" const RtMidi::Api rtmidi_compiled_apis[] = {
+#if defined(__MACOSX_CORE__)
+  RtMidi::MACOSX_CORE,
+#endif
+#if defined(__LINUX_ALSA__)
+  RtMidi::LINUX_ALSA,
+#endif
+#if defined(__FREEBSD_ALSA__)
+  RtMidi::FREEBSD_ALSA,
+#endif
+#if defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
+  RtMidi::UNIX_JACK,
+#endif
+#if defined(__WINDOWS_MM__)
+  RtMidi::WINDOWS_MM,
+#endif
+#if defined(__RTMIDI_DUMMY__)
+  RtMidi::RTMIDI_DUMMY,
+#endif
+  RtMidi::UNSPECIFIED,
+};
+extern "C" const unsigned int rtmidi_num_compiled_apis =
+  sizeof(rtmidi_compiled_apis)/sizeof(rtmidi_compiled_apis[0])-1;
+}
+
+// This is a compile-time check that rtmidi_num_api_names == RtMidi::NUM_APIS.
+// If the build breaks here, check that they match.
+template<bool b> class StaticAssert { public: StaticAssert() {} };
+template<> class StaticAssert<true>{ public: StaticAssert() {} };
+class StaticAssertions { StaticAssertions() {
+  StaticAssert<rtmidi_num_api_names == RtMidi::NUM_APIS>();
+}};
+
+void RtMidi :: getCompiledApi( std::vector<RtMidi::Api> &apis ) throw()
+{
+  apis = std::vector<RtMidi::Api>(rtmidi_compiled_apis,
+                                  rtmidi_compiled_apis + rtmidi_num_compiled_apis);
+}
+
+std::string RtMidi :: getApiName( RtMidi::Api api )
+{
+  if (api < 0 || api >= RtMidi::NUM_APIS)
+    return "";
+  return rtmidi_api_names[api][0];
+}
+
+std::string RtMidi :: getApiDisplayName( RtMidi::Api api )
+{
+  if (api < 0 || api >= RtMidi::NUM_APIS)
+    return "Unknown";
+  return rtmidi_api_names[api][1];
+}
+
+RtMidi::Api RtMidi :: getCompiledApiByName( const std::string &name )
+{
+  unsigned int i=0;
+  for (i = 0; i < rtmidi_num_compiled_apis; ++i)
+    if (name == rtmidi_api_names[rtmidi_compiled_apis[i]][0])
+      return rtmidi_compiled_apis[i];
+  return RtMidi::UNSPECIFIED;
+}
+
+void RtMidi :: setClientName( const std::string &clientName )
+{
+  rtapi_->setClientName( clientName );
+}
+
+void RtMidi :: setPortName( const std::string &portName )
+{
+  rtapi_->setPortName( portName );
+}
+
+
+//*********************************************************************//
+//  RtMidiIn Definitions
+//*********************************************************************//
+
+void RtMidiIn :: openMidiApi( RtMidi::Api api, const std::string &clientName, unsigned int queueSizeLimit )
+{
+  delete rtapi_;
+  rtapi_ = 0;
+
+#if defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
+  if ( api == UNIX_JACK )
+    rtapi_ = new MidiInJack( clientName, queueSizeLimit );
+#endif
+#if defined(__LINUX_ALSA__)
+  if ( api == LINUX_ALSA )
+    rtapi_ = new MidiInAlsa( clientName, queueSizeLimit );
+#endif
+#if defined(__FREEBSD_ALSA__)
+  if ( api == FREEBSD_ALSA )
+    rtapi_ = new MidiInAlsa( clientName, queueSizeLimit );
+#endif
+#if defined(__WINDOWS_MM__)
+  if ( api == WINDOWS_MM )
+    rtapi_ = new MidiInWinMM( clientName, queueSizeLimit );
+#endif
+#if defined(__MACOSX_CORE__)
+  if ( api == MACOSX_CORE )
+    rtapi_ = new MidiInCore( clientName, queueSizeLimit );
+#endif
+#if defined(__RTMIDI_DUMMY__)
+  if ( api == RTMIDI_DUMMY )
+    rtapi_ = new MidiInDummy( clientName, queueSizeLimit );
+#endif
+}
+
+RTMIDI_DLL_PUBLIC RtMidiIn :: RtMidiIn( RtMidi::Api api, const std::string &clientName, unsigned int queueSizeLimit )
+  : RtMidi()
+{
+  if ( api != UNSPECIFIED ) {
+    // Attempt to open the specified API.
+    openMidiApi( api, clientName, queueSizeLimit );
+    if ( rtapi_ ) return;
+
+    // No compiled support for specified API value.  Issue a warning
+    // and continue as if no API was specified.
+    std::cerr << "\nRtMidiIn: no compiled support for specified API argument!\n\n" << std::endl;
   }
-  else if (type == RtMidiError::DEBUG_WARNING) {
+
+  // Iterate through the compiled APIs and return as soon as we find
+  // one with at least one port or we reach the end of the list.
+  std::vector< RtMidi::Api > apis;
+  getCompiledApi( apis );
+  for ( unsigned int i=0; i<apis.size(); i++ ) {
+    openMidiApi( apis[i], clientName, queueSizeLimit );
+    if ( rtapi_ && rtapi_->getPortCount() ) break;
+  }
+
+  if ( rtapi_ ) return;
+
+  // It should not be possible to get here because the preprocessor
+  // definition __RTMIDI_DUMMY__ is automatically defined if no
+  // API-specific definitions are passed to the compiler. But just in
+  // case something weird happens, we'll throw an error.
+  std::string errorText = "RtMidiIn: no compiled API support found ... critical error!!";
+  throw( RtMidiError( errorText, RtMidiError::UNSPECIFIED ) );
+}
+
+RtMidiIn :: ~RtMidiIn() throw()
+{
+}
+
+
+//*********************************************************************//
+//  RtMidiOut Definitions
+//*********************************************************************//
+
+void RtMidiOut :: openMidiApi( RtMidi::Api api, const std::string &clientName )
+{
+  delete rtapi_;
+  rtapi_ = 0;
+
+#if defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
+  if ( api == UNIX_JACK )
+    rtapi_ = new MidiOutJack( clientName );
+#endif
+#if defined(__LINUX_ALSA__)
+  if ( api == LINUX_ALSA )
+    rtapi_ = new MidiOutAlsa( clientName );
+#endif
+#ifdef __FREEBSD_ALSA__
+  if ( api == FREEBSD_ALSA )
+    rtapi_ = new MidiOutAlsa( clientName );
+#endif
+#if defined(__WINDOWS_MM__)
+  if ( api == WINDOWS_MM )
+    rtapi_ = new MidiOutWinMM( clientName );
+#endif
+#if defined(__MACOSX_CORE__)
+  if ( api == MACOSX_CORE )
+    rtapi_ = new MidiOutCore( clientName );
+#endif
+#if defined(__RTMIDI_DUMMY__)
+  if ( api == RTMIDI_DUMMY )
+    rtapi_ = new MidiOutDummy( clientName );
+#endif
+}
+
+RTMIDI_DLL_PUBLIC RtMidiOut :: RtMidiOut( RtMidi::Api api, const std::string &clientName)
+{
+  if ( api != UNSPECIFIED ) {
+    // Attempt to open the specified API.
+    openMidiApi( api, clientName );
+    if ( rtapi_ ) return;
+
+    // No compiled support for specified API value.  Issue a warning
+    // and continue as if no API was specified.
+    std::cerr << "\nRtMidiOut: no compiled support for specified API argument!\n\n" << std::endl;
+  }
+
+  // Iterate through the compiled APIs and return as soon as we find
+  // one with at least one port or we reach the end of the list.
+  std::vector< RtMidi::Api > apis;
+  getCompiledApi( apis );
+  for ( unsigned int i=0; i<apis.size(); i++ ) {
+    openMidiApi( apis[i], clientName );
+    if ( rtapi_ && rtapi_->getPortCount() ) break;
+  }
+
+  if ( rtapi_ ) return;
+
+  // It should not be possible to get here because the preprocessor
+  // definition __RTMIDI_DUMMY__ is automatically defined if no
+  // API-specific definitions are passed to the compiler. But just in
+  // case something weird happens, we'll thrown an error.
+  std::string errorText = "RtMidiOut: no compiled API support found ... critical error!!";
+  throw( RtMidiError( errorText, RtMidiError::UNSPECIFIED ) );
+}
+
+RtMidiOut :: ~RtMidiOut() throw()
+{
+}
+
+//*********************************************************************//
+//  Common MidiApi Definitions
+//*********************************************************************//
+
+MidiApi :: MidiApi( void )
+  : apiData_( 0 ), connected_( false ), errorCallback_(0), firstErrorOccurred_(false), errorCallbackUserData_(0)
+{
+}
+
+MidiApi :: ~MidiApi( void )
+{
+}
+
+void MidiApi :: setErrorCallback( RtMidiErrorCallback errorCallback, void *userData = 0 )
+{
+    errorCallback_ = errorCallback;
+    errorCallbackUserData_ = userData;
+}
+
+void MidiApi :: error( RtMidiError::Type type, std::string errorString )
+{
+  if ( errorCallback_ ) {
+
+    if ( firstErrorOccurred_ )
+      return;
+
+    firstErrorOccurred_ = true;
+    const std::string errorMessage = errorString;
+
+    errorCallback_( type, errorMessage, errorCallbackUserData_ );
+    firstErrorOccurred_ = false;
+    return;
+  }
+
+  if ( type == RtMidiError::WARNING ) {
+    std::cerr << '\n' << errorString << "\n\n";
+  }
+  else if ( type == RtMidiError::DEBUG_WARNING ) {
 #if defined(__RTMIDI_DEBUG__)
-    std::cerr << "[chuck](via RtMidi): " << errorString_ << "\n";
+    std::cerr << '\n' << errorString << "\n\n";
 #endif
   }
   else {
-    // std::cerr << "[chuck](via RtMidi): " << errorString_ << "\n";
-    throw RtMidiError( errorString_, type );
+    std::cerr << '\n' << errorString << "\n\n";
+    throw RtMidiError( errorString, type );
   }
 }
 
-
 //*********************************************************************//
-//  Common RtMidiIn Definitions
+//  Common MidiInApi Definitions
 //*********************************************************************//
 
-RtMidiIn :: RtMidiIn() : RtMidi()
+MidiInApi :: MidiInApi( unsigned int queueSizeLimit )
+  : MidiApi()
 {
-  this->initialize();
+  // Allocate the MIDI queue.
+  inputData_.queue.ringSize = queueSizeLimit;
+  if ( inputData_.queue.ringSize > 0 )
+    inputData_.queue.ring = new MidiMessage[ inputData_.queue.ringSize ];
 }
 
-void RtMidiIn :: setCallback( RtMidiCallback callback, void *userData )
+MidiInApi :: ~MidiInApi( void )
 {
+  // Delete the MIDI queue.
+  if ( inputData_.queue.ringSize > 0 ) delete [] inputData_.queue.ring;
+}
+
+void MidiInApi :: setCallback( RtMidiIn::RtMidiCallback callback, void *userData )
+{
   if ( inputData_.usingCallback ) {
-    errorString_ = "RtMidiIn::setCallback: callback function is already set!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiInApi::setCallback: a callback function is already set!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   if ( !callback ) {
     errorString_ = "RtMidiIn::setCallback: callback function value is invalid!";
-    error( RtMidiError::WARNING );
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
-  inputData_.userCallback = (void *) callback;
+  inputData_.userCallback = callback;
   inputData_.userData = userData;
   inputData_.usingCallback = true;
 }
 
-void RtMidiIn :: cancelCallback()
+void MidiInApi :: cancelCallback()
 {
   if ( !inputData_.usingCallback ) {
     errorString_ = "RtMidiIn::cancelCallback: no callback function was set!";
-    error( RtMidiError::WARNING );
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
@@ -112,57 +648,107 @@ void RtMidiIn :: cancelCallback()
   inputData_.usingCallback = false;
 }
 
-void RtMidiIn :: setQueueSizeLimit( unsigned int queueSize )
+void MidiInApi :: ignoreTypes( bool midiSysex, bool midiTime, bool midiSense )
 {
-  inputData_.queueLimit = queueSize;
-}
-
-void RtMidiIn :: ignoreTypes( bool midiSysex, bool midiTime, bool midiSense )
-{
   inputData_.ignoreFlags = 0;
   if ( midiSysex ) inputData_.ignoreFlags = 0x01;
   if ( midiTime ) inputData_.ignoreFlags |= 0x02;
   if ( midiSense ) inputData_.ignoreFlags |= 0x04;
 }
 
-double RtMidiIn :: getMessage( std::vector<unsigned char> *message )
+double MidiInApi :: getMessage( std::vector<unsigned char> *message )
 {
   message->clear();
 
   if ( inputData_.usingCallback ) {
-    errorString_ = "RtMidiIn::getNextMessage: user callback is currently set for this port.";
-    error( RtMidiError::WARNING );
+    errorString_ = "RtMidiIn::getNextMessage: a user callback is currently set for this port.";
+    error( RtMidiError::WARNING, errorString_ );
     return 0.0;
   }
 
-  if ( inputData_.queue.size() == 0 ) return 0.0;
+  double timeStamp;
+  if ( !inputData_.queue.pop( message, &timeStamp ) )
+    return 0.0;
 
+  return timeStamp;
+}
+
+unsigned int MidiInApi::MidiQueue::size( unsigned int *__back,
+                                         unsigned int *__front )
+{
+  // Access back/front members exactly once and make stack copies for
+  // size calculation
+  unsigned int _back = back, _front = front, _size;
+  if ( _back >= _front )
+    _size = _back - _front;
+  else
+    _size = ringSize - _front + _back;
+
+  // Return copies of back/front so no new and unsynchronized accesses
+  // to member variables are needed.
+  if ( __back ) *__back = _back;
+  if ( __front ) *__front = _front;
+  return _size;
+}
+
+// As long as we haven't reached our queue size limit, push the message.
+bool MidiInApi::MidiQueue::push( const MidiInApi::MidiMessage& msg )
+{
+  // Local stack copies of front/back
+  unsigned int _back, _front, _size;
+
+  // Get back/front indexes exactly once and calculate current size
+  _size = size( &_back, &_front );
+
+  if ( _size < ringSize-1 )
+  {
+    ring[_back] = msg;
+    back = (back+1)%ringSize;
+    return true;
+  }
+
+  return false;
+}
+
+bool MidiInApi::MidiQueue::pop( std::vector<unsigned char> *msg, double* timeStamp )
+{
+  // Local stack copies of front/back
+  unsigned int _back, _front, _size;
+
+  // Get back/front indexes exactly once and calculate current size
+  _size = size( &_back, &_front );
+
+  if ( _size == 0 )
+    return false;
+
   // Copy queued message to the vector pointer argument and then "pop" it.
-  std::vector<unsigned char> *bytes = &(inputData_.queue.front().bytes);
-  message->assign( bytes->begin(), bytes->end() );
-  double deltaTime = inputData_.queue.front().timeStamp;
-  inputData_.queue.pop();
+  msg->assign( ring[_front].bytes.begin(), ring[_front].bytes.end() );
+  *timeStamp = ring[_front].timeStamp;
 
-  return deltaTime;
+  // Update front
+  front = (front+1)%ringSize;
+  return true;
 }
 
 //*********************************************************************//
-//  Common RtMidiOut Definitions
+//  Common MidiOutApi Definitions
 //*********************************************************************//
 
-RtMidiOut :: RtMidiOut() : RtMidi()
+MidiOutApi :: MidiOutApi( void )
+  : MidiApi()
 {
-  this->initialize();
 }
 
+MidiOutApi :: ~MidiOutApi( void )
+{
+}
 
-//*********************************************************************//
-//  API: Macintosh OS-X
-//*********************************************************************//
+// *************************************************** //
+//
+// OS/API-specific methods.
+//
+// *************************************************** //
 
-// API information found at:
-//   - http://developer. apple .com/audio/pdf/coreaudio.pdf 
-
 #if defined(__MACOSX_CORE__)
 
 // The CoreMIDI API is based on the use of a callback function for
@@ -171,11 +757,12 @@ RtMidiOut :: RtMidiOut() : RtMidi()
 
 // OS-X CoreMIDI header files.
 #include <CoreMIDI/CoreMIDI.h>
-#include <CoreAudio/HostTime.h>
 
-// CoreMIDI naming helper function prototypes
-static void readable_name(MIDIEndpointRef end, char *buffer, int bufsize);
-static int get_device_name(SInt32 uniqueid, char*buffer, int bufsize);
+// these are not available on iOS. 
+#if (TARGET_OS_IPHONE == 0)
+  #include <CoreAudio/HostTime.h>
+  #include <CoreServices/CoreServices.h>
+#endif
 
 // A structure to hold variables related to the CoreMIDI API
 // implementation.
@@ -185,217 +772,84 @@ struct CoreMidiData {
   MIDIEndpointRef endpoint;
   MIDIEndpointRef destinationId;
   unsigned long long lastTime;
+  MIDISysexSendRequest sysexreq;
 };
 
-// ******
-// API: OS-X
-// helper functions
-// *****
-
-// coreMIDI port naming helper function
-/*
-  This wraps up the code to take a passed-in endpoint and work out
-  a nice human-readable name for it.
-
-  For the moment, this function will return firstly the device name +
-  port name, or if we can work out what external devices are hooked
-  in, that name. It only grabs the very first connected device name.
-
-  NB. won't get connected devices correctly before 10.3.
-*/
-static void readable_name(MIDIEndpointRef end, char *buffer, int bufsize)
-{  
-    MIDIEntityRef ent = 0; // NULL;
-    MIDIDeviceRef dev = 0; //NULL;
-    int ii, count, length;//, ret;
-    SInt32 *idarray;
-    CFDataRef data = NULL;
-    CFStringRef s;
-
-    buffer[0] = '\0';
-  
-    if( MIDIObjectGetDataProperty(end, kMIDIPropertyConnectionUniqueID, &data) == 0)
-    {
-        length = CFDataGetLength(data) / sizeof(SInt32);
-        idarray = (SInt32 *) CFDataGetBytePtr(data);
-        count = 0;
-        for (ii = 0; ii < length; ii++) {
-            if (bufsize < 3)
-                break;
-            if (count > 0) {
-                strcpy(buffer, ", ");
-                buffer += 2;
-                bufsize -= 2;
-            }
-      
-            if (get_device_name(idarray[ii], buffer, bufsize) == 0) {
-                count++;
-                bufsize -= strlen(buffer);
-                buffer += strlen(buffer);
-            }
-        }
-
-        CFRelease(data);
-        if (count > 0)
-            return;
-    }
-
-    char * mid = buffer;
-    // build up the name of the enclosing device, if it can be found.
-    if (MIDIEndpointGetEntity(end, &ent) == 0) {
-        if (MIDIEntityGetDevice(ent, &dev) == 0) {
-            if (MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &s) == 0) {
-                CFStringGetCString(s, buffer, bufsize, 0);
-                bufsize -= strlen(buffer) + 1;
-                buffer += strlen(buffer);
-
-                CFRelease(s);
-            }
-        }
-    }
-
-    // ge
-    char buffy[128];
-    // Now add the port/endpoint name.
-    // no need to update buffer pointer. Last item.
-    if (MIDIObjectGetStringProperty(end, kMIDIPropertyName, &s) == 0) {
-        CFStringGetCString(s, buffy, 128, 0);
-        CFRelease(s);
-        
-        // copy if different
-        if( strcmp( mid, buffy ) && strlen(buffy) < bufsize ) {
-            *buffer = ' ';
-            buffer++;
-            strcpy( buffer, buffy );
-        }
-    }
-}
-
-
-// port naming helper function (External devices)
-/*
-  Uses the midiojectfindbyuniqueid function to hunt down the relevant
-  device and copies its name into the buffer provided. We don't know
-  what type of device we'll get back, so we first throw away any
-  external flags (We don't care), and then cast it up to device which
-  is the thing which has a useful name.
-
-  If it can't find one, return -1. 0 returned on success.
-*/
-static int get_device_name(SInt32 uniqueid, char *buffer, int bufsize)
-{
-    int ret;
-    MIDIObjectRef object = 0; // NULL; // 1.3.1.0
-    MIDIObjectType type;
-
-    MIDIDeviceRef dev = 0; // NULL;
-    MIDIEntityRef ent = 0; // NULL;
-    MIDIEndpointRef end = 0; // NULL;
-    CFStringRef name = NULL;
-
-    ret = MIDIObjectFindByUniqueID(uniqueid, &object, &type);
-    if (ret < 0)
-        return -1;
-
-    // now clear any external flag.
-    if (type > 0) 
-        type = (MIDIObjectType) (type & (~kMIDIObjectType_ExternalMask));
-
-    if (type == kMIDIObjectType_Device) {
-        dev = (MIDIDeviceRef) object;
-    } else  if (type == kMIDIObjectType_Entity) {
-        ent = (MIDIEntityRef) object;
-        if (MIDIEntityGetDevice(ent, &dev)) {
-            return -1;
-        }
-    } if (type == kMIDIObjectType_Source ||
-        type == kMIDIObjectType_Destination) {
-        end = (MIDIEndpointRef) object;
-        if (MIDIEndpointGetEntity(end, &ent)) {
-            return -1;
-        }
-        if (MIDIEntityGetDevice(ent, &dev)) {
-            return -1;
-        }
-    } else {
-        // unknown type
-        printf("Unknown type %d returned from findobject\n", (int) type);
-        CFRelease( &object ); // 1.3.1.0
-        return -1;
-    }
-
-    MIDIObjectGetStringProperty(dev, kMIDIPropertyName, &name);
-    CFStringGetCString(name, buffer, bufsize, 0);
-    CFRelease(name);
-
-    return 0;
-}
-
-
-
-
-
 //*********************************************************************//
 //  API: OS-X
-//  Class Definitions: RtMidiIn
+//  Class Definitions: MidiInCore
 //*********************************************************************//
 
-void midiInputCallback( const MIDIPacketList *list, void *procRef, void *srcRef )
+static void midiInputCallback( const MIDIPacketList *list, void *procRef, void */*srcRef*/ )
 {
-  RtMidiIn::RtMidiInData *data = static_cast<RtMidiIn::RtMidiInData *> (procRef);
+  MidiInApi::RtMidiInData *data = static_cast<MidiInApi::RtMidiInData *> (procRef);
   CoreMidiData *apiData = static_cast<CoreMidiData *> (data->apiData);
 
-  bool continueSysex = false;
   unsigned char status;
   unsigned short nBytes, iByte, size;
   unsigned long long time;
-  RtMidiIn::MidiMessage message;
+
+  bool& continueSysex = data->continueSysex;
+  MidiInApi::MidiMessage& message = data->message;
+
   const MIDIPacket *packet = &list->packet[0];
   for ( unsigned int i=0; i<list->numPackets; ++i ) {
 
     // My interpretation of the CoreMIDI documentation: all message
     // types, except sysex, are complete within a packet and there may
     // be several of them in a single packet.  Sysex messages can be
-    // broken across multiple packets but are bundled alone within a
-    // packet.  I'm assuming that sysex messages, if segmented, must
-    // be complete within the same MIDIPacketList.
+    // broken across multiple packets and PacketLists but are bundled
+    // alone within each packet (these packets do not contain other
+    // message types).  If sysex messages are split across multiple
+    // MIDIPacketLists, they must be handled by multiple calls to this
+    // function.
 
     nBytes = packet->length;
-    if ( nBytes == 0 ) continue;
+    if ( nBytes == 0 ) {
+      packet = MIDIPacketNext( packet );
+      continue;
+    }
 
     // Calculate time stamp.
-    message.timeStamp = 0.0;
-    if ( data->firstMessage )
+    if ( data->firstMessage ) {
+      message.timeStamp = 0.0;
       data->firstMessage = false;
+    }
     else {
       time = packet->timeStamp;
+      if ( time == 0 ) { // this happens when receiving asynchronous sysex messages
+        time = AudioGetCurrentHostTime();
+      }
       time -= apiData->lastTime;
       time = AudioConvertHostTimeToNanos( time );
-      message.timeStamp = time * 0.000000001;
+      if ( !continueSysex )
+        message.timeStamp = time * 0.000000001;
     }
-    apiData->lastTime = packet->timeStamp;
 
+    // Track whether any non-filtered messages were found in this
+    // packet for timestamp calculation
+    bool foundNonFiltered = false;
+
     iByte = 0;
     if ( continueSysex ) {
       // We have a continuing, segmented sysex message.
-      if ( !(data->ignoreFlags & 0x01) ) {
+      if ( !( data->ignoreFlags & 0x01 ) ) {
         // If we're not ignoring sysex messages, copy the entire packet.
-        for ( unsigned int j=0; j<nBytes; j++ )
+        for ( unsigned int j=0; j<nBytes; ++j )
           message.bytes.push_back( packet->data[j] );
       }
-      if ( packet->data[nBytes] == 0xF7 ) continueSysex = false;
-      if ( !continueSysex ) {
+      continueSysex = packet->data[nBytes-1] != 0xF7;
+
+      if ( !( data->ignoreFlags & 0x01 ) && !continueSysex ) {
         // If not a continuing sysex message, invoke the user callback function or queue the message.
-        if ( data->usingCallback && message.bytes.size() > 0 ) {
+        if ( data->usingCallback ) {
           RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) data->userCallback;
           callback( message.timeStamp, &message.bytes, data->userData );
         }
         else {
           // As long as we haven't reached our queue size limit, push the message.
-          if ( data->queueLimit > data->queue.size() )
-            data->queue.push( message );
-          else
-            std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
+          if ( !data->queue.push( message ) )
+            std::cerr << "\nMidiInCore: message queue limit reached!!\n\n";
         }
         message.bytes.clear();
       }
@@ -417,26 +871,24 @@ void midiInputCallback( const MIDIPacketList *list, vo
             iByte = nBytes;
           }
           else size = nBytes - iByte;
-          if ( packet->data[nBytes] == 0xF7 ) continueSysex = false;
+          continueSysex = packet->data[nBytes-1] != 0xF7;
         }
-        else if ( status < 0xF3 ) {
-          if ( status == 0xF1 && (data->ignoreFlags & 0x02) ) {
-            // A MIDI time code message and we're ignoring it.
+        else if ( status == 0xF1 ) {
+          // A MIDI time code message
+          if ( data->ignoreFlags & 0x02 ) {
             size = 0;
-            iByte += 3;
+            iByte += 2;
           }
-          else size = 3;
+          else size = 2;
         }
+        else if ( status == 0xF2 ) size = 3;
         else if ( status == 0xF3 ) size = 2;
-        else if ( status == 0xF8 ) {
-          size = 1;
-          if ( data->ignoreFlags & 0x02 ) {
-            // A MIDI timing tick message and we're ignoring it.
-            size = 0;
-            iByte += 3;
-          }
+        else if ( status == 0xF8 && ( data->ignoreFlags & 0x02 ) ) {
+          // A MIDI timing tick message and we're ignoring it.
+          size = 0;
+          iByte += 1;
         }
-        else if ( status == 0xFE && (data->ignoreFlags & 0x04) ) {
+        else if ( status == 0xFE && ( data->ignoreFlags & 0x04 ) ) {
           // A MIDI active sensing message and we're ignoring it.
           size = 0;
           iByte += 1;
@@ -445,6 +897,7 @@ void midiInputCallback( const MIDIPacketList *list, vo
 
         // Copy the MIDI data to our vector.
         if ( size ) {
+          foundNonFiltered = true;
           message.bytes.assign( &packet->data[iByte], &packet->data[iByte+size] );
           if ( !continueSysex ) {
             // If not a continuing sysex message, invoke the user callback function or queue the message.
@@ -454,10 +907,8 @@ void midiInputCallback( const MIDIPacketList *list, vo
             }
             else {
               // As long as we haven't reached our queue size limit, push the message.
-              if ( data->queueLimit > data->queue.size() )
-                data->queue.push( message );
-              else
-                std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
+              if ( !data->queue.push( message ) )
+                std::cerr << "\nMidiInCore: message queue limit reached!!\n\n";
             }
             message.bytes.clear();
           }
@@ -465,18 +916,49 @@ void midiInputCallback( const MIDIPacketList *list, vo
         }
       }
     }
+
+    // Save the time of the last non-filtered message
+    if ( foundNonFiltered ) {
+      apiData->lastTime = packet->timeStamp;
+      if ( apiData->lastTime == 0 ) { // this happens when receiving asynchronous sysex messages
+        apiData->lastTime = AudioGetCurrentHostTime();
+      }
+    }
+
     packet = MIDIPacketNext(packet);
   }
 }
 
-void RtMidiIn :: initialize( void )
+MidiInCore :: MidiInCore( const std::string &clientName, unsigned int queueSizeLimit )
+  : MidiInApi( queueSizeLimit )
 {
+  MidiInCore::initialize( clientName );
+}
+
+MidiInCore :: ~MidiInCore( void )
+{
+  // Close a connection if it exists.
+  MidiInCore::closePort();
+
+  // Cleanup.
+  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+  MIDIClientDispose( data->client );
+  if ( data->endpoint ) MIDIEndpointDispose( data->endpoint );
+  delete data;
+}
+
+void MidiInCore :: initialize( const std::string& clientName )
+{
   // Set up our client.
   MIDIClientRef client;
-  OSStatus result = MIDIClientCreate( CFSTR("RtMidi Input Client"), NULL, NULL, &client );
+  CFStringRef name = CFStringCreateWithCString( NULL, clientName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDIClientCreate(name, NULL, NULL, &client );
   if ( result != noErr ) {
-    errorString_ = "RtMidiIn::initialize: error creating OS-X MIDI client object.";
-    error( RtMidiError::DRIVER_ERROR );
+    std::ostringstream ost;
+    ost << "MidiInCore::initialize: error creating OS-X MIDI client object (" << result << ").";
+    errorString_ = ost.str();
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific connection information.
@@ -485,45 +967,56 @@ void RtMidiIn :: initialize( void )
   data->endpoint = 0;
   apiData_ = (void *) data;
   inputData_.apiData = (void *) data;
+  CFRelease( name );
 }
 
-void RtMidiIn :: openPort( unsigned int portNumber )
+void MidiInCore :: openPort( unsigned int portNumber, const std::string &portName )
 {
   if ( connected_ ) {
-    errorString_ = "RtMidiIn::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiInCore::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
   unsigned int nSrc = MIDIGetNumberOfSources();
-  if (nSrc < 1) {
-    errorString_ = "RtMidiIn::openPort: no MIDI input sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+  if ( nSrc < 1 ) {
+    errorString_ = "MidiInCore::openPort: no MIDI input sources found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-  std::ostringstream ost;
   if ( portNumber >= nSrc ) {
-    ost << "RtMidiIn::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiInCore::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
   MIDIPortRef port;
   CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
-  OSStatus result = MIDIInputPortCreate( data->client, CFSTR("RtMidi MIDI Input Port"), midiInputCallback, (void *)&inputData_, &port );
+  CFStringRef portNameRef = CFStringCreateWithCString( NULL, portName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDIInputPortCreate( data->client,
+                                         portNameRef,
+                                         midiInputCallback, (void *)&inputData_, &port );
+  CFRelease( portNameRef );
+
   if ( result != noErr ) {
     MIDIClientDispose( data->client );
-    errorString_ = "RtMidiIn::openPort: error creating OS-X MIDI input port.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiInCore::openPort: error creating OS-X MIDI input port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Get the desired input source identifier.
   MIDIEndpointRef endpoint = MIDIGetSource( portNumber );
-  if ( endpoint == 0 ) { // 1.3.1.0: changed from NULL to 0
+  if ( endpoint == 0 ) {
     MIDIPortDispose( port );
     MIDIClientDispose( data->client );
-    errorString_ = "RtMidiIn::openPort: error getting MIDI input source reference.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiInCore::openPort: error getting MIDI input source reference.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Make the connection.
@@ -531,8 +1024,9 @@ void RtMidiIn :: openPort( unsigned int portNumber )
   if ( result != noErr ) {
     MIDIPortDispose( port );
     MIDIClientDispose( data->client );
-    errorString_ = "RtMidiIn::openPort: error connecting OS-X MIDI input port.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiInCore::openPort: error connecting OS-X MIDI input port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific port information.
@@ -541,114 +1035,254 @@ void RtMidiIn :: openPort( unsigned int portNumber )
   connected_ = true;
 }
 
-void RtMidiIn :: openVirtualPort()
+void MidiInCore :: openVirtualPort( const std::string &portName )
 {
   CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
 
   // Create a virtual MIDI input destination.
   MIDIEndpointRef endpoint;
-  OSStatus result = MIDIDestinationCreate( data->client, CFSTR("RtMidi Input"), midiInputCallback, (void *)&inputData_, &endpoint );
+  CFStringRef portNameRef = CFStringCreateWithCString( NULL, portName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDIDestinationCreate( data->client,
+                                           portNameRef,
+                                           midiInputCallback, (void *)&inputData_, &endpoint );
+  CFRelease( portNameRef );
+
   if ( result != noErr ) {
-    errorString_ = "RtMidiIn::openVirtualPort: error creating virtual OS-X MIDI destination.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiInCore::openVirtualPort: error creating virtual OS-X MIDI destination.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific connection information.
   data->endpoint = endpoint;
 }
 
-void RtMidiIn :: closePort( void )
+void MidiInCore :: closePort( void )
 {
-  if ( connected_ ) {
-    CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+
+  if ( data->endpoint ) {
+    MIDIEndpointDispose( data->endpoint );
+    data->endpoint = 0;
+  }
+
+  if ( data->port ) {
     MIDIPortDispose( data->port );
-    connected_ = false;
+    data->port = 0;
   }
+
+  connected_ = false;
 }
 
-RtMidiIn :: ~RtMidiIn()
+void MidiInCore :: setClientName ( const std::string& )
 {
-  // Close a connection if it exists.
-  closePort();
 
-  // Cleanup.
-  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
-  MIDIClientDispose( data->client );
-  if ( data->endpoint ) MIDIEndpointDispose( data->endpoint );
-  delete data;
+  errorString_ = "MidiInCore::setClientName: this function is not implemented for the MACOSX_CORE API!";
+  error( RtMidiError::WARNING, errorString_ );
+
 }
 
-unsigned int RtMidiIn :: getPortCount()
+void MidiInCore :: setPortName ( const std::string& )
 {
+
+  errorString_ = "MidiInCore::setPortName: this function is not implemented for the MACOSX_CORE API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+unsigned int MidiInCore :: getPortCount()
+{
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
   return MIDIGetNumberOfSources();
 }
 
-std::string RtMidiIn :: getPortName( unsigned int portNumber )
+// This function was submitted by Douglas Casey Tucker and apparently
+// derived largely from PortMidi.
+CFStringRef EndpointName( MIDIEndpointRef endpoint, bool isExternal )
 {
-//  CFStringRef nameRef;
+  CFMutableStringRef result = CFStringCreateMutable( NULL, 0 );
+  CFStringRef str;
+
+  // Begin with the endpoint's name.
+  str = NULL;
+  MIDIObjectGetStringProperty( endpoint, kMIDIPropertyName, &str );
+  if ( str != NULL ) {
+    CFStringAppend( result, str );
+    CFRelease( str );
+  }
+
+  MIDIEntityRef entity = 0;
+  MIDIEndpointGetEntity( endpoint, &entity );
+  if ( entity == 0 )
+    // probably virtual
+    return result;
+
+  if ( CFStringGetLength( result ) == 0 ) {
+    // endpoint name has zero length -- try the entity
+    str = NULL;
+    MIDIObjectGetStringProperty( entity, kMIDIPropertyName, &str );
+    if ( str != NULL ) {
+      CFStringAppend( result, str );
+      CFRelease( str );
+    }
+  }
+  // now consider the device's name
+  MIDIDeviceRef device = 0;
+  MIDIEntityGetDevice( entity, &device );
+  if ( device == 0 )
+    return result;
+
+  str = NULL;
+  MIDIObjectGetStringProperty( device, kMIDIPropertyName, &str );
+  if ( CFStringGetLength( result ) == 0 ) {
+      CFRelease( result );
+      return str;
+  }
+  if ( str != NULL ) {
+    // if an external device has only one entity, throw away
+    // the endpoint name and just use the device name
+    if ( isExternal && MIDIDeviceGetNumberOfEntities( device ) < 2 ) {
+      CFRelease( result );
+      return str;
+    } else {
+      if ( CFStringGetLength( str ) == 0 ) {
+        CFRelease( str );
+        return result;
+      }
+      // does the entity name already start with the device name?
+      // (some drivers do this though they shouldn't)
+      // if so, do not prepend
+      if ( CFStringCompareWithOptions( result, /* endpoint name */
+                                       str /* device name */,
+                                       CFRangeMake(0, CFStringGetLength( str ) ), 0 ) != kCFCompareEqualTo ) {
+        // prepend the device name to the entity name
+        if ( CFStringGetLength( result ) > 0 )
+          CFStringInsert( result, 0, CFSTR(" ") );
+
+        CFStringInsert( result, 0, str );
+      }
+      CFRelease( str );
+    }
+  }
+  return result;
+}
+
+// This function was submitted by Douglas Casey Tucker and apparently
+// derived largely from PortMidi.
+static CFStringRef ConnectedEndpointName( MIDIEndpointRef endpoint )
+{
+  CFMutableStringRef result = CFStringCreateMutable( NULL, 0 );
+  CFStringRef str;
+  OSStatus err;
+  int i;
+
+  // Does the endpoint have connections?
+  CFDataRef connections = NULL;
+  int nConnected = 0;
+  bool anyStrings = false;
+  err = MIDIObjectGetDataProperty( endpoint, kMIDIPropertyConnectionUniqueID, &connections );
+  if ( connections != NULL ) {
+    // It has connections, follow them
+    // Concatenate the names of all connected devices
+    nConnected = CFDataGetLength( connections ) / sizeof(MIDIUniqueID);
+    if ( nConnected ) {
+      const SInt32 *pid = (const SInt32 *)(CFDataGetBytePtr(connections));
+      for ( i=0; i<nConnected; ++i, ++pid ) {
+        MIDIUniqueID id = EndianS32_BtoN( *pid );
+        MIDIObjectRef connObject;
+        MIDIObjectType connObjectType;
+        err = MIDIObjectFindByUniqueID( id, &connObject, &connObjectType );
+        if ( err == noErr ) {
+          if ( connObjectType == kMIDIObjectType_ExternalSource  ||
+               connObjectType == kMIDIObjectType_ExternalDestination ) {
+            // Connected to an external device's endpoint (10.3 and later).
+            str = EndpointName( (MIDIEndpointRef)(connObject), true );
+          } else {
+            // Connected to an external device (10.2) (or something else, catch-
+            str = NULL;
+            MIDIObjectGetStringProperty( connObject, kMIDIPropertyName, &str );
+          }
+          if ( str != NULL ) {
+            if ( anyStrings )
+              CFStringAppend( result, CFSTR(", ") );
+            else
+              anyStrings = true;
+            CFStringAppend( result, str );
+            CFRelease( str );
+          }
+        }
+      }
+    }
+    CFRelease( connections );
+  }
+  if ( anyStrings )
+    return result;
+
+  CFRelease( result );
+
+  // Here, either the endpoint had no connections, or we failed to obtain names
+  return EndpointName( endpoint, false );
+}
+
+std::string MidiInCore :: getPortName( unsigned int portNumber )
+{
+  CFStringRef nameRef;
   MIDIEndpointRef portRef;
-  std::ostringstream ost;
   char name[128];
 
+  std::string stringName;
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
   if ( portNumber >= MIDIGetNumberOfSources() ) {
-    ost << "RtMidiIn::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiInCore::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::WARNING, errorString_ );
+    return stringName;
   }
+
   portRef = MIDIGetSource( portNumber );
-#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1030  
-  readable_name(portRef, name, sizeof(name));
-#else
-  MIDIObjectGetStringProperty( portRef, kMIDIPropertyName, &nameRef );
-  CFStringGetCString( nameRef, name, sizeof(name), 0);
+  nameRef = ConnectedEndpointName( portRef );
+  CFStringGetCString( nameRef, name, sizeof(name), kCFStringEncodingUTF8 );
   CFRelease( nameRef );
-#endif
-  std::string stringName = name;
-  return stringName;
+
+  return stringName = name;
 }
 
 //*********************************************************************//
 //  API: OS-X
-//  Class Definitions: RtMidiOut
+//  Class Definitions: MidiOutCore
 //*********************************************************************//
 
-unsigned int RtMidiOut :: getPortCount()
+MidiOutCore :: MidiOutCore( const std::string &clientName )
+  : MidiOutApi()
 {
-  return MIDIGetNumberOfDestinations();
+  MidiOutCore::initialize( clientName );
 }
 
-std::string RtMidiOut :: getPortName( unsigned int portNumber )
+MidiOutCore :: ~MidiOutCore( void )
 {
-//  CFStringRef nameRef;
-  MIDIEndpointRef portRef;
-  std::ostringstream ost;
-  char name[128];
+  // Close a connection if it exists.
+  MidiOutCore::closePort();
 
-  if ( portNumber >= MIDIGetNumberOfDestinations() ) {
-    ost << "RtMidiOut::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
-  portRef = MIDIGetDestination( portNumber );
-#if MAC_OS_X_VERSION_MAX_ALLOWED >= 1030
-  readable_name(portRef, name, sizeof(name));
-#else
-  MIDIObjectGetStringProperty( portRef, kMIDIPropertyName, &nameRef );
-  CFStringGetCString( nameRef, name, sizeof(name), 0);
-  CFRelease( nameRef );
-#endif
-  std::string stringName = name;
-  return stringName;
+  // Cleanup.
+  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+  MIDIClientDispose( data->client );
+  if ( data->endpoint ) MIDIEndpointDispose( data->endpoint );
+  delete data;
 }
 
-void RtMidiOut :: initialize( void )
+void MidiOutCore :: initialize( const std::string& clientName )
 {
   // Set up our client.
   MIDIClientRef client;
-  OSStatus result = MIDIClientCreate( CFSTR("RtMidi Output Client"), NULL, NULL, &client );
+  CFStringRef name = CFStringCreateWithCString( NULL, clientName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDIClientCreate(name, NULL, NULL, &client );
   if ( result != noErr ) {
-    errorString_ = "RtMidiOut::initialize: error creating OS-X MIDI client object.";
-    error( RtMidiError::DRIVER_ERROR );
+    std::ostringstream ost;
+    ost << "MidiInCore::initialize: error creating OS-X MIDI client object (" << result << ").";
+    errorString_ = ost.str();
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific connection information.
@@ -656,45 +1290,83 @@ void RtMidiOut :: initialize( void )
   data->client = client;
   data->endpoint = 0;
   apiData_ = (void *) data;
+  CFRelease( name );
 }
 
-void RtMidiOut :: openPort( unsigned int portNumber )
+unsigned int MidiOutCore :: getPortCount()
 {
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
+  return MIDIGetNumberOfDestinations();
+}
+
+std::string MidiOutCore :: getPortName( unsigned int portNumber )
+{
+  CFStringRef nameRef;
+  MIDIEndpointRef portRef;
+  char name[128];
+
+  std::string stringName;
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
+  if ( portNumber >= MIDIGetNumberOfDestinations() ) {
+    std::ostringstream ost;
+    ost << "MidiOutCore::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
+    errorString_ = ost.str();
+    error( RtMidiError::WARNING, errorString_ );
+    return stringName;
+  }
+
+  portRef = MIDIGetDestination( portNumber );
+  nameRef = ConnectedEndpointName(portRef);
+  CFStringGetCString( nameRef, name, sizeof(name), kCFStringEncodingUTF8 );
+  CFRelease( nameRef );
+
+  return stringName = name;
+}
+
+void MidiOutCore :: openPort( unsigned int portNumber, const std::string &portName )
+{
   if ( connected_ ) {
-    errorString_ = "RtMidiOut::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutCore::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
+  CFRunLoopRunInMode( kCFRunLoopDefaultMode, 0, false );
   unsigned int nDest = MIDIGetNumberOfDestinations();
   if (nDest < 1) {
-    errorString_ = "RtMidiOut::openPort: no MIDI output destinations found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+    errorString_ = "MidiOutCore::openPort: no MIDI output destinations found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-  std::ostringstream ost;
   if ( portNumber >= nDest ) {
-    ost << "RtMidiOut::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiOutCore::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
   MIDIPortRef port;
   CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
-  OSStatus result = MIDIOutputPortCreate( data->client, CFSTR("RtMidi Virtual MIDI Output Port"), &port );
+  CFStringRef portNameRef = CFStringCreateWithCString( NULL, portName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDIOutputPortCreate( data->client, portNameRef, &port );
+  CFRelease( portNameRef );
   if ( result != noErr ) {
     MIDIClientDispose( data->client );
-    errorString_ = "RtMidiOut::openPort: error creating OS-X MIDI output port.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiOutCore::openPort: error creating OS-X MIDI output port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Get the desired output port identifier.
   MIDIEndpointRef destination = MIDIGetDestination( portNumber );
-  if ( destination == 0 ) { // 1.3.1.0: changed from NULL to 0
+  if ( destination == 0 ) {
     MIDIPortDispose( port );
     MIDIClientDispose( data->client );
-    errorString_ = "RtMidiOut::openPort: error getting MIDI output destination reference.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiOutCore::openPort: error getting MIDI output destination reference.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific connection information.
@@ -703,78 +1375,120 @@ void RtMidiOut :: openPort( unsigned int portNumber )
   connected_ = true;
 }
 
-void RtMidiOut :: closePort( void )
+void MidiOutCore :: closePort( void )
 {
-  if ( connected_ ) {
-    CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+
+  if ( data->endpoint ) {
+    MIDIEndpointDispose( data->endpoint );
+    data->endpoint = 0;
+  }
+
+  if ( data->port ) {
     MIDIPortDispose( data->port );
-    connected_ = false;
+    data->port = 0;
   }
+
+  connected_ = false;
 }
 
-void RtMidiOut :: openVirtualPort()
+void MidiOutCore :: setClientName ( const std::string& )
 {
+
+  errorString_ = "MidiOutCore::setClientName: this function is not implemented for the MACOSX_CORE API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+void MidiOutCore :: setPortName ( const std::string& )
+{
+
+  errorString_ = "MidiOutCore::setPortName: this function is not implemented for the MACOSX_CORE API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+void MidiOutCore :: openVirtualPort( const std::string &portName )
+{
   CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
 
   if ( data->endpoint ) {
-    errorString_ = "RtMidiOut::openVirtualPort: a virtual output port already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutCore::openVirtualPort: a virtual output port already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   // Create a virtual MIDI output source.
   MIDIEndpointRef endpoint;
-  OSStatus result = MIDISourceCreate( data->client, CFSTR("RtMidi Output"), &endpoint );
+  CFStringRef portNameRef = CFStringCreateWithCString( NULL, portName.c_str(), kCFStringEncodingASCII );
+  OSStatus result = MIDISourceCreate( data->client, portNameRef, &endpoint );
+  CFRelease( portNameRef );
+
   if ( result != noErr ) {
-    errorString_ = "RtMidiOut::initialize: error creating OS-X virtual MIDI source.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiOutCore::initialize: error creating OS-X virtual MIDI source.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   // Save our api-specific connection information.
   data->endpoint = endpoint;
 }
 
-RtMidiOut :: ~RtMidiOut()
+void MidiOutCore :: sendMessage( const unsigned char *message, size_t size )
 {
-  // Close a connection if it exists.
-  closePort();
+  // We use the MIDISendSysex() function to asynchronously send sysex
+  // messages.  Otherwise, we use a single CoreMidi MIDIPacket.
+  unsigned int nBytes = static_cast<unsigned int> (size);
+  if ( nBytes == 0 ) {
+    errorString_ = "MidiOutCore::sendMessage: no data in message argument!";
+    error( RtMidiError::WARNING, errorString_ );
+    return;
+  }
 
-  // Cleanup.
+  MIDITimeStamp timeStamp = AudioGetCurrentHostTime();
   CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
-  MIDIClientDispose( data->client );
-  if ( data->endpoint ) MIDIEndpointDispose( data->endpoint );
-  delete data;
-}
+  OSStatus result;
 
-void RtMidiOut :: sendMessage( std::vector<unsigned char> *message )
-{
-  unsigned int nBytes = message->size();
-  // Pad the buffer for extra (unknown) structure data.
-  Byte buffer[nBytes+32];
-  MIDIPacketList *pktlist = (MIDIPacketList *) buffer;
-  MIDIPacket *curPacket = MIDIPacketListInit( pktlist );
+  if ( message[0] != 0xF0 && nBytes > 3 ) {
+    errorString_ = "MidiOutCore::sendMessage: message format problem ... not sysex but > 3 bytes?";
+    error( RtMidiError::WARNING, errorString_ );
+    return;
+  }
 
-  MIDITimeStamp timeStamp = 0;
-  curPacket = MIDIPacketListAdd( pktlist, sizeof(buffer), curPacket, timeStamp, nBytes, &message->at(0) );
+  Byte buffer[nBytes+(sizeof( MIDIPacketList ))];
+  ByteCount listSize = sizeof( buffer );
+  MIDIPacketList *packetList = (MIDIPacketList*)buffer;
+  MIDIPacket *packet = MIDIPacketListInit( packetList );
 
-  CoreMidiData *data = static_cast<CoreMidiData *> (apiData_);
+  ByteCount remainingBytes = nBytes;
+  while ( remainingBytes && packet ) {
+    ByteCount bytesForPacket = remainingBytes > 65535 ? 65535 : remainingBytes; // 65535 = maximum size of a MIDIPacket
+    const Byte* dataStartPtr = (const Byte *) &message[nBytes - remainingBytes];
+    packet = MIDIPacketListAdd( packetList, listSize, packet, timeStamp, bytesForPacket, dataStartPtr );
+    remainingBytes -= bytesForPacket;
+  }
 
+  if ( !packet ) {
+    errorString_ = "MidiOutCore::sendMessage: could not allocate packet list";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
+
   // Send to any destinations that may have connected to us.
-  OSStatus result;
   if ( data->endpoint ) {
-    result = MIDIReceived( data->endpoint, pktlist );
+    result = MIDIReceived( data->endpoint, packetList );
     if ( result != noErr ) {
-      errorString_ = "RtMidiOut::sendMessage: error sending MIDI to virtual destinations.";
-      error( RtMidiError::WARNING );
+      errorString_ = "MidiOutCore::sendMessage: error sending MIDI to virtual destinations.";
+      error( RtMidiError::WARNING, errorString_ );
     }
   }
 
   // And send to an explicit destination port if we're connected.
   if ( connected_ ) {
-    result = MIDISend( data->port, data->destinationId, pktlist );
+    result = MIDISend( data->port, data->destinationId, packetList );
     if ( result != noErr ) {
-      errorString_ = "RtMidiOut::sendMessage: error sending MIDI message to port.";
-      error( RtMidiError::WARNING );
+      errorString_ = "MidiOutCore::sendMessage: error sending MIDI message to port.";
+      error( RtMidiError::WARNING, errorString_ );
     }
   }
 }
@@ -789,8 +1503,7 @@ void RtMidiOut :: sendMessage( std::vector<unsigned ch
 // API information found at:
 //   - http://www.alsa-project.org/documentation.php#Library
 
-// chuck
-#if defined(__LINUX_ALSASEQ__) || defined(__PLATFORM_LINUX__)
+#if defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__)
 
 // The ALSA Sequencer API is based on the use of a callback function for
 // MIDI input.
@@ -798,6 +1511,10 @@ void RtMidiOut :: sendMessage( std::vector<unsigned ch
 // Thanks to Pedro Lopez-Cabanillas for help with the ALSA sequencer
 // time stamps and other assorted fixes!!!
 
+// If you don't need timestamping for incoming MIDI events, define the
+// preprocessor definition AVOID_TIMESTAMPING to save resources
+// associated with the ALSA sequencer queues.
+
 #include <pthread.h>
 #include <sys/time.h>
 
@@ -808,32 +1525,38 @@ void RtMidiOut :: sendMessage( std::vector<unsigned ch
 // implementation.
 struct AlsaMidiData {
   snd_seq_t *seq;
+  unsigned int portNum;
   int vport;
   snd_seq_port_subscribe_t *subscription;
   snd_midi_event_t *coder;
   unsigned int bufferSize;
   unsigned char *buffer;
   pthread_t thread;
-  unsigned long long lastTime;
+  pthread_t dummy_thread_id;
+  snd_seq_real_time_t lastTime;
   int queue_id; // an input queue is needed to get timestamped events
+  int trigger_fds[2];
 };
 
 #define PORT_TYPE( pinfo, bits ) ((snd_seq_port_info_get_capability(pinfo) & (bits)) == (bits))
 
 //*********************************************************************//
 //  API: LINUX ALSA
-//  Class Definitions: RtMidiIn
+//  Class Definitions: MidiInAlsa
 //*********************************************************************//
 
-extern "C" void *alsaMidiHandler( void *ptr )
+static void *alsaMidiHandler( void *ptr )
 {
-  RtMidiIn::RtMidiInData *data = static_cast<RtMidiIn::RtMidiInData *> (ptr);
+  MidiInApi::RtMidiInData *data = static_cast<MidiInApi::RtMidiInData *> (ptr);
   AlsaMidiData *apiData = static_cast<AlsaMidiData *> (data->apiData);
 
   long nBytes;
-  unsigned long long time, lastTime;
+  double time;
   bool continueSysex = false;
-  RtMidiIn::MidiMessage message;
+  bool doDecode = false;
+  MidiInApi::MidiMessage message;
+  int poll_fd_count;
+  struct pollfd *poll_fds;
 
   snd_seq_event_t *ev;
   int result;
@@ -841,63 +1564,93 @@ extern "C" void *alsaMidiHandler( void *ptr )
   result = snd_midi_event_new( 0, &apiData->coder );
   if ( result < 0 ) {
     data->doInput = false;
-    std::cerr << "\nRtMidiIn::alsaMidiHandler: error initializing MIDI event parser!\n\n";
+    std::cerr << "\nMidiInAlsa::alsaMidiHandler: error initializing MIDI event parser!\n\n";
     return 0;
   }
   unsigned char *buffer = (unsigned char *) malloc( apiData->bufferSize );
   if ( buffer == NULL ) {
     data->doInput = false;
-    std::cerr << "\nRtMidiIn::alsaMidiHandler: error initializing buffer memory!\n\n";
+    snd_midi_event_free( apiData->coder );
+    apiData->coder = 0;
+    std::cerr << "\nMidiInAlsa::alsaMidiHandler: error initializing buffer memory!\n\n";
     return 0;
   }
   snd_midi_event_init( apiData->coder );
   snd_midi_event_no_status( apiData->coder, 1 ); // suppress running status messages
 
+  poll_fd_count = snd_seq_poll_descriptors_count( apiData->seq, POLLIN ) + 1;
+  poll_fds = (struct pollfd*)alloca( poll_fd_count * sizeof( struct pollfd ));
+  snd_seq_poll_descriptors( apiData->seq, poll_fds + 1, poll_fd_count - 1, POLLIN );
+  poll_fds[0].fd = apiData->trigger_fds[0];
+  poll_fds[0].events = POLLIN;
+
   while ( data->doInput ) {
 
     if ( snd_seq_event_input_pending( apiData->seq, 1 ) == 0 ) {
-      // No data pending ... sleep a bit.
-      usleep( 1000 );
+      // No data pending
+      if ( poll( poll_fds, poll_fd_count, -1) >= 0 ) {
+        if ( poll_fds[0].revents & POLLIN ) {
+          bool dummy;
+          int res = read( poll_fds[0].fd, &dummy, sizeof(dummy) );
+          (void) res;
+        }
+      }
       continue;
     }
 
     // If here, there should be data.
     result = snd_seq_event_input( apiData->seq, &ev );
     if ( result == -ENOSPC ) {
-      std::cerr << "\nRtMidiIn::alsaMidiHandler: MIDI input buffer overrun!\n\n";
+      std::cerr << "\nMidiInAlsa::alsaMidiHandler: MIDI input buffer overrun!\n\n";
       continue;
     }
     else if ( result <= 0 ) {
-      std::cerr << "RtMidiIn::alsaMidiHandler: unknown MIDI input error!\n";
+      std::cerr << "\nMidiInAlsa::alsaMidiHandler: unknown MIDI input error!\n";
+      perror("System reports");
       continue;
     }
 
     // This is a bit weird, but we now have to decode an ALSA MIDI
     // event (back) into MIDI bytes.  We'll ignore non-MIDI types.
-    message.bytes.clear();
+    if ( !continueSysex ) message.bytes.clear();
+
+    doDecode = false;
     switch ( ev->type ) {
 
-        case SND_SEQ_EVENT_PORT_SUBSCRIBED:
+    case SND_SEQ_EVENT_PORT_SUBSCRIBED:
 #if defined(__RTMIDI_DEBUG__)
-      std::cout << "RtMidiIn::alsaMidiHandler: port connection made!\n";
+      std::cout << "MidiInAlsa::alsaMidiHandler: port connection made!\n";
 #endif
       break;
 
-        case SND_SEQ_EVENT_PORT_UNSUBSCRIBED:
-      std::cerr << "RtMidiIn::alsaMidiHandler: port connection has closed!\n";
-      data->doInput = false;
+    case SND_SEQ_EVENT_PORT_UNSUBSCRIBED:
+#if defined(__RTMIDI_DEBUG__)
+      std::cerr << "MidiInAlsa::alsaMidiHandler: port connection has closed!\n";
+      std::cout << "sender = " << (int) ev->data.connect.sender.client << ":"
+                << (int) ev->data.connect.sender.port
+                << ", dest = " << (int) ev->data.connect.dest.client << ":"
+                << (int) ev->data.connect.dest.port
+                << std::endl;
+#endif
       break;
 
     case SND_SEQ_EVENT_QFRAME: // MIDI time code
-      if ( data->ignoreFlags & 0x02 ) break;
+      if ( !( data->ignoreFlags & 0x02 ) ) doDecode = true;
+      break;
 
-    case SND_SEQ_EVENT_TICK: // MIDI timing tick
-      if ( data->ignoreFlags & 0x02 ) break;
+    case SND_SEQ_EVENT_TICK: // 0xF9 ... MIDI timing tick
+      if ( !( data->ignoreFlags & 0x02 ) ) doDecode = true;
+      break;
 
+    case SND_SEQ_EVENT_CLOCK: // 0xF8 ... MIDI timing (clock) tick
+      if ( !( data->ignoreFlags & 0x02 ) ) doDecode = true;
+      break;
+
     case SND_SEQ_EVENT_SENSING: // Active sensing
-      if ( data->ignoreFlags & 0x04 ) break;
+      if ( !( data->ignoreFlags & 0x04 ) ) doDecode = true;
+      break;
 
-        case SND_SEQ_EVENT_SYSEX:
+    case SND_SEQ_EVENT_SYSEX:
       if ( (data->ignoreFlags & 0x01) ) break;
       if ( ev->data.ext.len > apiData->bufferSize ) {
         apiData->bufferSize = ev->data.ext.len;
@@ -905,58 +1658,85 @@ extern "C" void *alsaMidiHandler( void *ptr )
         buffer = (unsigned char *) malloc( apiData->bufferSize );
         if ( buffer == NULL ) {
           data->doInput = false;
-          std::cerr << "\nRtMidiIn::alsaMidiHandler: error resizing buffer memory!\n\n";
+          std::cerr << "\nMidiInAlsa::alsaMidiHandler: error resizing buffer memory!\n\n";
           break;
         }
       }
+      doDecode = true;
+      break;
 
     default:
+      doDecode = true;
+    }
+
+    if ( doDecode ) {
+
       nBytes = snd_midi_event_decode( apiData->coder, buffer, apiData->bufferSize, ev );
-      if ( nBytes <= 0 ) {
-#if defined(__RTMIDI_DEBUG__)
-        std::cerr << "\nRtMidiIn::alsaMidiHandler: event parsing error or not a MIDI event!\n\n";
-#endif
-        break;
-      }
+      if ( nBytes > 0 ) {
+        // The ALSA sequencer has a maximum buffer size for MIDI sysex
+        // events of 256 bytes.  If a device sends sysex messages larger
+        // than this, they are segmented into 256 byte chunks.  So,
+        // we'll watch for this and concatenate sysex chunks into a
+        // single sysex message if necessary.
+        if ( !continueSysex )
+          message.bytes.assign( buffer, &buffer[nBytes] );
+        else
+          message.bytes.insert( message.bytes.end(), buffer, &buffer[nBytes] );
 
-      // The ALSA sequencer has a maximum buffer size for MIDI sysex
-      // events of 256 bytes.  If a device sends sysex messages larger
-      // than this, they are segmented into 256 byte chunks.  So,
-      // we'll watch for this and concatenate sysex chunks into a
-      // single sysex message if necessary.
-      if ( !continueSysex )
-        message.bytes.assign( buffer, &buffer[nBytes] );
-      else
-        message.bytes.insert( message.bytes.end(), buffer, &buffer[nBytes] );
+        continueSysex = ( ( ev->type == SND_SEQ_EVENT_SYSEX ) && ( message.bytes.back() != 0xF7 ) );
+        if ( !continueSysex ) {
 
-      if ( ev->type == SND_SEQ_EVENT_SYSEX && message.bytes.back() == 0xF7 )
-        continueSysex = false;
-      else {
-        continueSysex = true;
-        break;
-      }
+          // Calculate the time stamp:
+          message.timeStamp = 0.0;
 
-      // Calculate the time stamp:
-      message.timeStamp = 0.0;
+          // Method 1: Use the system time.
+          //(void)gettimeofday(&tv, (struct timezone *)NULL);
+          //time = (tv.tv_sec * 1000000) + tv.tv_usec;
 
-      // Method 1: Use the system time.
-      //(void)gettimeofday(&tv, (struct timezone *)NULL);
-      //time = (tv.tv_sec * 1000000) + tv.tv_usec;
+          // Method 2: Use the ALSA sequencer event time data.
+          // (thanks to Pedro Lopez-Cabanillas!).
 
-      // Method 2: Use the ALSA sequencer event time data.
-      // (thanks to Pedro Lopez-Cabanillas!).
-      time = ( ev->time.time.tv_sec * 1000000 ) + ( ev->time.time.tv_nsec/1000 );
-      lastTime = time;
-      time -= apiData->lastTime;
-      apiData->lastTime = lastTime;
-      if ( data->firstMessage == true )
-        data->firstMessage = false;
-      else
-        message.timeStamp = time * 0.000001;
+          // Using method from:
+          // https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
+
+          // Perform the carry for the later subtraction by updating y.
+          // Temp var y is timespec because computation requires signed types,
+          // while snd_seq_real_time_t has unsigned types.
+          snd_seq_real_time_t &x( ev->time.time );
+          struct timespec y;
+          y.tv_nsec = apiData->lastTime.tv_nsec;
+          y.tv_sec = apiData->lastTime.tv_sec;
+          if ( x.tv_nsec < y.tv_nsec ) {
+              int nsec = (y.tv_nsec - (int)x.tv_nsec) / 1000000000 + 1;
+              y.tv_nsec -= 1000000000 * nsec;
+              y.tv_sec += nsec;
+          }
+          if ( x.tv_nsec - y.tv_nsec > 1000000000 ) {
+              int nsec = ((int)x.tv_nsec - y.tv_nsec) / 1000000000;
+              y.tv_nsec += 1000000000 * nsec;
+              y.tv_sec -= nsec;
+          }
+
+          // Compute the time difference.
+          time = (int)x.tv_sec - y.tv_sec + ((int)x.tv_nsec - y.tv_nsec)*1e-9;
+
+          apiData->lastTime = ev->time.time;
+
+          if ( data->firstMessage == true )
+            data->firstMessage = false;
+          else
+            message.timeStamp = time;
+        }
+        else {
+#if defined(__RTMIDI_DEBUG__)
+          std::cerr << "\nMidiInAlsa::alsaMidiHandler: event parsing error or not a MIDI event!\n\n";
+#endif
+        }
+      }
     }
 
-    snd_seq_free_event(ev);
-    if ( message.bytes.size() == 0 ) continue;
+    snd_seq_free_event( ev );
+    if ( message.bytes.size() == 0 || continueSysex ) continue;
 
     if ( data->usingCallback ) {
       RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) data->userCallback;
@@ -964,106 +1744,201 @@ extern "C" void *alsaMidiHandler( void *ptr )
     }
     else {
       // As long as we haven't reached our queue size limit, push the message.
-      if ( data->queueLimit > data->queue.size() )
-        data->queue.push( message );
-      else
-        std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
+      if ( !data->queue.push( message ) )
+        std::cerr << "\nMidiInAlsa: message queue limit reached!!\n\n";
     }
   }
 
   if ( buffer ) free( buffer );
   snd_midi_event_free( apiData->coder );
   apiData->coder = 0;
+  apiData->thread = apiData->dummy_thread_id;
   return 0;
 }
 
-void RtMidiIn :: initialize( void )
+MidiInAlsa :: MidiInAlsa( const std::string &clientName, unsigned int queueSizeLimit )
+  : MidiInApi( queueSizeLimit )
 {
+  MidiInAlsa::initialize( clientName );
+}
+
+MidiInAlsa :: ~MidiInAlsa()
+{
+  // Close a connection if it exists.
+  MidiInAlsa::closePort();
+
+  // Shutdown the input thread.
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  if ( inputData_.doInput ) {
+    inputData_.doInput = false;
+    int res = write( data->trigger_fds[1], &inputData_.doInput, sizeof( inputData_.doInput ) );
+    (void) res;
+    if ( !pthread_equal(data->thread, data->dummy_thread_id) )
+      pthread_join( data->thread, NULL );
+  }
+
+  // Cleanup.
+  close ( data->trigger_fds[0] );
+  close ( data->trigger_fds[1] );
+  if ( data->vport >= 0 ) snd_seq_delete_port( data->seq, data->vport );
+#ifndef AVOID_TIMESTAMPING
+  snd_seq_free_queue( data->seq, data->queue_id );
+#endif
+  snd_seq_close( data->seq );
+  delete data;
+}
+
+void MidiInAlsa :: initialize( const std::string& clientName )
+{
   // Set up the ALSA sequencer client.
-    snd_seq_t *seq;
-  int result = snd_seq_open(&seq, "default", SND_SEQ_OPEN_DUPLEX, SND_SEQ_NONBLOCK);
+  snd_seq_t *seq;
+  int result = snd_seq_open( &seq, "default", SND_SEQ_OPEN_DUPLEX, SND_SEQ_NONBLOCK );
   if ( result < 0 ) {
-    errorString_ = "RtMidiIn::initialize: error creating ALSA sequencer input client object.";
-    error( RtMidiError::DRIVER_ERROR );
-    }
+    errorString_ = "MidiInAlsa::initialize: error creating ALSA sequencer client object.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
 
   // Set client name.
-  snd_seq_set_client_name(seq, "RtMidi Input Client");
+  snd_seq_set_client_name( seq, clientName.c_str() );
 
   // Save our api-specific connection information.
   AlsaMidiData *data = (AlsaMidiData *) new AlsaMidiData;
   data->seq = seq;
+  data->portNum = -1;
   data->vport = -1;
+  data->subscription = 0;
+  data->dummy_thread_id = pthread_self();
+  data->thread = data->dummy_thread_id;
+  data->trigger_fds[0] = -1;
+  data->trigger_fds[1] = -1;
   apiData_ = (void *) data;
   inputData_.apiData = (void *) data;
 
+  if ( pipe(data->trigger_fds) == -1 ) {
+    errorString_ = "MidiInAlsa::initialize: error creating pipe objects.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
+
   // Create the input queue
-  data->queue_id = snd_seq_alloc_named_queue(seq, "RtMidi Queue");
+#ifndef AVOID_TIMESTAMPING
+  data->queue_id = snd_seq_alloc_named_queue( seq, "RtMidi Queue" );
   // Set arbitrary tempo (mm=100) and resolution (240)
   snd_seq_queue_tempo_t *qtempo;
-  snd_seq_queue_tempo_alloca(&qtempo);
-  snd_seq_queue_tempo_set_tempo(qtempo, 600000);
-  snd_seq_queue_tempo_set_ppq(qtempo, 240);
-  snd_seq_set_queue_tempo(data->seq, data->queue_id, qtempo);
-  snd_seq_drain_output(data->seq);
+  snd_seq_queue_tempo_alloca( &qtempo );
+  snd_seq_queue_tempo_set_tempo( qtempo, 600000 );
+  snd_seq_queue_tempo_set_ppq( qtempo, 240 );
+  snd_seq_set_queue_tempo( data->seq, data->queue_id, qtempo );
+  snd_seq_drain_output( data->seq );
+#endif
 }
 
 // This function is used to count or get the pinfo structure for a given port number.
 unsigned int portInfo( snd_seq_t *seq, snd_seq_port_info_t *pinfo, unsigned int type, int portNumber )
 {
-    snd_seq_client_info_t *cinfo;
+  snd_seq_client_info_t *cinfo;
   int client;
   int count = 0;
-    snd_seq_client_info_alloca( &cinfo );
+  snd_seq_client_info_alloca( &cinfo );
 
-    snd_seq_client_info_set_client( cinfo, -1 );
-    while ( snd_seq_query_next_client( seq, cinfo ) >= 0 ) {
+  snd_seq_client_info_set_client( cinfo, -1 );
+  while ( snd_seq_query_next_client( seq, cinfo ) >= 0 ) {
     client = snd_seq_client_info_get_client( cinfo );
     if ( client == 0 ) continue;
-        // Reset query info
-        snd_seq_port_info_set_client( pinfo, client );
-        snd_seq_port_info_set_port( pinfo, -1 );
-        while ( snd_seq_query_next_port( seq, pinfo ) >= 0 ) {
-      if ( !PORT_TYPE( pinfo, type ) )  continue;
+    // Reset query info
+    snd_seq_port_info_set_client( pinfo, client );
+    snd_seq_port_info_set_port( pinfo, -1 );
+    while ( snd_seq_query_next_port( seq, pinfo ) >= 0 ) {
+      unsigned int atyp = snd_seq_port_info_get_type( pinfo );
+      if ( ( ( atyp & SND_SEQ_PORT_TYPE_MIDI_GENERIC ) == 0 ) &&
+           ( ( atyp & SND_SEQ_PORT_TYPE_SYNTH ) == 0 ) &&
+           ( ( atyp & SND_SEQ_PORT_TYPE_APPLICATION ) == 0 ) ) continue;
+
+      unsigned int caps = snd_seq_port_info_get_capability( pinfo );
+      if ( ( caps & type ) != type ) continue;
       if ( count == portNumber ) return 1;
-      count++;
-        }
+      ++count;
     }
+  }
 
   // If a negative portNumber was used, return the port count.
   if ( portNumber < 0 ) return count;
   return 0;
 }
 
-void RtMidiIn :: openPort( unsigned int portNumber )
+unsigned int MidiInAlsa :: getPortCount()
 {
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
+
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  return portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, -1 );
+}
+
+std::string MidiInAlsa :: getPortName( unsigned int portNumber )
+{
+  snd_seq_client_info_t *cinfo;
+  snd_seq_port_info_t *pinfo;
+  snd_seq_client_info_alloca( &cinfo );
+  snd_seq_port_info_alloca( &pinfo );
+
+  std::string stringName;
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, (int) portNumber ) ) {
+    int cnum = snd_seq_port_info_get_client( pinfo );
+    snd_seq_get_any_client_info( data->seq, cnum, cinfo );
+    std::ostringstream os;
+    os << snd_seq_client_info_get_name( cinfo );
+    os << ":";
+    os << snd_seq_port_info_get_name( pinfo );
+    os << " ";                                    // These lines added to make sure devices are listed
+    os << snd_seq_port_info_get_client( pinfo );  // with full portnames added to ensure individual device names
+    os << ":";
+    os << snd_seq_port_info_get_port( pinfo );
+    stringName = os.str();
+    return stringName;
+  }
+
+  // If we get here, we didn't find a match.
+  errorString_ = "MidiInAlsa::getPortName: error looking for port name!";
+  error( RtMidiError::WARNING, errorString_ );
+  return stringName;
+}
+
+void MidiInAlsa :: openPort( unsigned int portNumber, const std::string &portName )
+{
   if ( connected_ ) {
-    errorString_ = "RtMidiIn::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiInAlsa::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   unsigned int nSrc = this->getPortCount();
-  if (nSrc < 1) {
-    errorString_ = "RtMidiIn::openPort: no MIDI input sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+  if ( nSrc < 1 ) {
+    errorString_ = "MidiInAlsa::openPort: no MIDI input sources found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
-  std::ostringstream ost;
+  snd_seq_port_info_t *src_pinfo;
+  snd_seq_port_info_alloca( &src_pinfo );
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, (int) portNumber ) == 0 ) {
-    ost << "RtMidiIn::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+  if ( portInfo( data->seq, src_pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, (int) portNumber ) == 0 ) {
+    std::ostringstream ost;
+    ost << "MidiInAlsa::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
-
   snd_seq_addr_t sender, receiver;
-  sender.client = snd_seq_port_info_get_client( pinfo );
-  sender.port = snd_seq_port_info_get_port( pinfo );
+  sender.client = snd_seq_port_info_get_client( src_pinfo );
+  sender.port = snd_seq_port_info_get_port( src_pinfo );
   receiver.client = snd_seq_client_id( data->seq );
+
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
   if ( data->vport < 0 ) {
     snd_seq_port_info_set_client( pinfo, 0 );
     snd_seq_port_info_set_port( pinfo, 0 );
@@ -1074,253 +1949,306 @@ void RtMidiIn :: openPort( unsigned int portNumber )
                                 SND_SEQ_PORT_TYPE_MIDI_GENERIC |
                                 SND_SEQ_PORT_TYPE_APPLICATION );
     snd_seq_port_info_set_midi_channels(pinfo, 16);
-    snd_seq_port_info_set_timestamping(pinfo, 1);
-    snd_seq_port_info_set_timestamp_real(pinfo, 1);    
-    snd_seq_port_info_set_timestamp_queue(pinfo, data->queue_id);
-    snd_seq_port_info_set_name(pinfo, "RtMidi Input");
-    data->vport = snd_seq_create_port(data->seq, pinfo);
-  
+#ifndef AVOID_TIMESTAMPING
+    snd_seq_port_info_set_timestamping( pinfo, 1 );
+    snd_seq_port_info_set_timestamp_real( pinfo, 1 );
+    snd_seq_port_info_set_timestamp_queue( pinfo, data->queue_id );
+#endif
+    snd_seq_port_info_set_name( pinfo,  portName.c_str() );
+    data->vport = snd_seq_create_port( data->seq, pinfo );
+
     if ( data->vport < 0 ) {
-      errorString_ = "RtMidiIn::openPort: ALSA error creating input port.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiInAlsa::openPort: ALSA error creating input port.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
+    data->vport = snd_seq_port_info_get_port( pinfo );
   }
 
   receiver.port = data->vport;
 
-  // Make subscription
-  snd_seq_port_subscribe_malloc( &data->subscription );
-  snd_seq_port_subscribe_set_sender(data->subscription, &sender);
-  snd_seq_port_subscribe_set_dest(data->subscription, &receiver);
-  if ( snd_seq_subscribe_port(data->seq, data->subscription) ) {
-    errorString_ = "RtMidiIn::openPort: ALSA error making port connection.";
-    error( RtMidiError::DRIVER_ERROR );
+  if ( !data->subscription ) {
+    // Make subscription
+    if ( snd_seq_port_subscribe_malloc( &data->subscription ) < 0 ) {
+      errorString_ = "MidiInAlsa::openPort: ALSA error allocation port subscription.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
+    }
+    snd_seq_port_subscribe_set_sender( data->subscription, &sender );
+    snd_seq_port_subscribe_set_dest( data->subscription, &receiver );
+    if ( snd_seq_subscribe_port( data->seq, data->subscription ) ) {
+      snd_seq_port_subscribe_free( data->subscription );
+      data->subscription = 0;
+      errorString_ = "MidiInAlsa::openPort: ALSA error making port connection.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
+    }
   }
 
   if ( inputData_.doInput == false ) {
     // Start the input queue
+#ifndef AVOID_TIMESTAMPING
     snd_seq_start_queue( data->seq, data->queue_id, NULL );
     snd_seq_drain_output( data->seq );
+#endif
     // Start our MIDI input thread.
     pthread_attr_t attr;
-    pthread_attr_init(&attr);
-    // chuck
-    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
-    //pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
+    pthread_attr_init( &attr );
+    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
+    pthread_attr_setschedpolicy( &attr, SCHED_OTHER );
 
     inputData_.doInput = true;
-    int err = pthread_create(&data->thread, &attr, alsaMidiHandler, &inputData_);
-    pthread_attr_destroy(&attr);
-    if (err) {
+    int err = pthread_create( &data->thread, &attr, alsaMidiHandler, &inputData_ );
+    pthread_attr_destroy( &attr );
+    if ( err ) {
       snd_seq_unsubscribe_port( data->seq, data->subscription );
       snd_seq_port_subscribe_free( data->subscription );
+      data->subscription = 0;
       inputData_.doInput = false;
-      errorString_ = "RtMidiIn::openPort: error starting MIDI input thread!";
-      error( RtMidiError::THREAD_ERROR );
+      errorString_ = "MidiInAlsa::openPort: error starting MIDI input thread!";
+      error( RtMidiError::THREAD_ERROR, errorString_ );
+      return;
     }
   }
 
   connected_ = true;
 }
 
-void RtMidiIn :: openVirtualPort()
+void MidiInAlsa :: openVirtualPort( const std::string &portName )
 {
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
   if ( data->vport < 0 ) {
     snd_seq_port_info_t *pinfo;
     snd_seq_port_info_alloca( &pinfo );
     snd_seq_port_info_set_capability( pinfo,
-                      SND_SEQ_PORT_CAP_WRITE |
-                      SND_SEQ_PORT_CAP_SUBS_WRITE );
+                                      SND_SEQ_PORT_CAP_WRITE |
+                                      SND_SEQ_PORT_CAP_SUBS_WRITE );
     snd_seq_port_info_set_type( pinfo,
-                SND_SEQ_PORT_TYPE_MIDI_GENERIC |
-                SND_SEQ_PORT_TYPE_APPLICATION );
-    snd_seq_port_info_set_midi_channels(pinfo, 16);
-    snd_seq_port_info_set_timestamping(pinfo, 1);
-    snd_seq_port_info_set_timestamp_real(pinfo, 1);    
-    snd_seq_port_info_set_timestamp_queue(pinfo, data->queue_id);
-    snd_seq_port_info_set_name(pinfo, "RtMidi Input");
-    data->vport = snd_seq_create_port(data->seq, pinfo);
+                                SND_SEQ_PORT_TYPE_MIDI_GENERIC |
+                                SND_SEQ_PORT_TYPE_APPLICATION );
+    snd_seq_port_info_set_midi_channels( pinfo, 16 );
+#ifndef AVOID_TIMESTAMPING
+    snd_seq_port_info_set_timestamping( pinfo, 1 );
+    snd_seq_port_info_set_timestamp_real( pinfo, 1 );
+    snd_seq_port_info_set_timestamp_queue( pinfo, data->queue_id );
+#endif
+    snd_seq_port_info_set_name( pinfo, portName.c_str() );
+    data->vport = snd_seq_create_port( data->seq, pinfo );
 
     if ( data->vport < 0 ) {
-      errorString_ = "RtMidiIn::openVirtualPort: ALSA error creating virtual port.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiInAlsa::openVirtualPort: ALSA error creating virtual port.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
+    data->vport = snd_seq_port_info_get_port( pinfo );
   }
 
   if ( inputData_.doInput == false ) {
+    // Wait for old thread to stop, if still running
+    if ( !pthread_equal( data->thread, data->dummy_thread_id ) )
+      pthread_join( data->thread, NULL );
+
     // Start the input queue
+#ifndef AVOID_TIMESTAMPING
     snd_seq_start_queue( data->seq, data->queue_id, NULL );
     snd_seq_drain_output( data->seq );
+#endif
     // Start our MIDI input thread.
     pthread_attr_t attr;
-    pthread_attr_init(&attr);
-    // chuck
-    //pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
-    //pthread_attr_setschedpolicy(&attr, SCHED_OTHER);
+    pthread_attr_init( &attr );
+    pthread_attr_setdetachstate( &attr, PTHREAD_CREATE_JOINABLE );
+    pthread_attr_setschedpolicy( &attr, SCHED_OTHER );
 
     inputData_.doInput = true;
-    int err = pthread_create(&data->thread, &attr, alsaMidiHandler, &inputData_);
-    pthread_attr_destroy(&attr);
-    if (err) {
-      snd_seq_unsubscribe_port( data->seq, data->subscription );
-      snd_seq_port_subscribe_free( data->subscription );
+    int err = pthread_create( &data->thread, &attr, alsaMidiHandler, &inputData_ );
+    pthread_attr_destroy( &attr );
+    if ( err ) {
+      if ( data->subscription ) {
+        snd_seq_unsubscribe_port( data->seq, data->subscription );
+        snd_seq_port_subscribe_free( data->subscription );
+        data->subscription = 0;
+      }
       inputData_.doInput = false;
-      errorString_ = "RtMidiIn::openPort: error starting MIDI input thread!";
-      error( RtMidiError::THREAD_ERROR );
+      errorString_ = "MidiInAlsa::openPort: error starting MIDI input thread!";
+      error( RtMidiError::THREAD_ERROR, errorString_ );
+      return;
     }
   }
 }
 
-void RtMidiIn :: closePort( void )
+void MidiInAlsa :: closePort( void )
 {
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+
   if ( connected_ ) {
-    AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-    snd_seq_unsubscribe_port( data->seq, data->subscription );
-    snd_seq_port_subscribe_free( data->subscription );
+    if ( data->subscription ) {
+      snd_seq_unsubscribe_port( data->seq, data->subscription );
+      snd_seq_port_subscribe_free( data->subscription );
+      data->subscription = 0;
+    }
     // Stop the input queue
+#ifndef AVOID_TIMESTAMPING
     snd_seq_stop_queue( data->seq, data->queue_id, NULL );
     snd_seq_drain_output( data->seq );
+#endif
     connected_ = false;
   }
-}
 
-RtMidiIn :: ~RtMidiIn()
-{
-  // Close a connection if it exists.
-  closePort();
-
-  // Shutdown the input thread.
-  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  // Stop thread to avoid triggering the callback, while the port is intended to be closed
   if ( inputData_.doInput ) {
     inputData_.doInput = false;
-    pthread_join( data->thread, NULL );
+    int res = write( data->trigger_fds[1], &inputData_.doInput, sizeof( inputData_.doInput ) );
+    (void) res;
+    if ( !pthread_equal( data->thread, data->dummy_thread_id ) )
+      pthread_join( data->thread, NULL );
   }
-
-  // Cleanup.
-  if ( data->vport >= 0 ) snd_seq_delete_port( data->seq, data->vport );
-  snd_seq_free_queue( data->seq, data->queue_id );
-  snd_seq_close( data->seq );
-  delete data;
 }
 
-unsigned int RtMidiIn :: getPortCount()
+void MidiInAlsa :: setClientName( const std::string &clientName )
 {
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
 
-  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  return portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, -1 );
+  AlsaMidiData *data = static_cast<AlsaMidiData *> ( apiData_ );
+  snd_seq_set_client_name( data->seq, clientName.c_str() );
+
 }
 
-std::string RtMidiIn :: getPortName( unsigned int portNumber )
+void MidiInAlsa :: setPortName( const std::string &portName )
 {
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
-
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ, (int) portNumber ) ) {
-    std::string stringName = std::string( snd_seq_port_info_get_name( pinfo ) );
-    return stringName;
-  }
-
-  // If we get here, we didn't find a match.
-  errorString_ = "RtMidiIn::getPortName: error looking for port name!";
-  error( RtMidiError::INVALID_PARAMETER );
-  return 0;
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
+  snd_seq_get_port_info( data->seq, data->vport, pinfo );
+  snd_seq_port_info_set_name( pinfo, portName.c_str() );
+  snd_seq_set_port_info( data->seq, data->vport, pinfo );
 }
 
 //*********************************************************************//
 //  API: LINUX ALSA
-//  Class Definitions: RtMidiOut
+//  Class Definitions: MidiOutAlsa
 //*********************************************************************//
 
-unsigned int RtMidiOut :: getPortCount()
+MidiOutAlsa :: MidiOutAlsa( const std::string &clientName ) : MidiOutApi()
 {
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
-
-  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  return portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, -1 );
+  MidiOutAlsa::initialize( clientName );
 }
 
-std::string RtMidiOut :: getPortName( unsigned int portNumber )
+MidiOutAlsa :: ~MidiOutAlsa()
 {
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
+  // Close a connection if it exists.
+  MidiOutAlsa::closePort();
 
+  // Cleanup.
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, (int) portNumber ) ) {
-    std::string stringName = std::string( snd_seq_port_info_get_name( pinfo ) );
-    return stringName;
-  }
-
-  // If we get here, we didn't find a match.
-  errorString_ = "RtMidiOut::getPortName: error looking for port name!";
-  error( RtMidiError::INVALID_PARAMETER );
-  return 0;
+  if ( data->vport >= 0 ) snd_seq_delete_port( data->seq, data->vport );
+  if ( data->coder ) snd_midi_event_free( data->coder );
+  if ( data->buffer ) free( data->buffer );
+  snd_seq_close( data->seq );
+  delete data;
 }
 
-void RtMidiOut :: initialize( void )
+void MidiOutAlsa :: initialize( const std::string& clientName )
 {
   // Set up the ALSA sequencer client.
-    snd_seq_t *seq;
-  int result = snd_seq_open(&seq, "default", SND_SEQ_OPEN_OUTPUT, 0);
-  if ( result < 0 ) {
-    errorString_ = "RtMidiOut::initialize: error creating ALSA sequencer client object.";
-    error( RtMidiError::DRIVER_ERROR );
-    }
+  snd_seq_t *seq;
+  int result1 = snd_seq_open( &seq, "default", SND_SEQ_OPEN_OUTPUT, SND_SEQ_NONBLOCK );
+  if ( result1 < 0 ) {
+    errorString_ = "MidiOutAlsa::initialize: error creating ALSA sequencer client object.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
 
   // Set client name.
-  snd_seq_set_client_name(seq, "RtMidi Output Client");
+  snd_seq_set_client_name( seq, clientName.c_str() );
 
   // Save our api-specific connection information.
   AlsaMidiData *data = (AlsaMidiData *) new AlsaMidiData;
   data->seq = seq;
+  data->portNum = -1;
   data->vport = -1;
   data->bufferSize = 32;
   data->coder = 0;
   data->buffer = 0;
-  result = snd_midi_event_new( data->bufferSize, &data->coder );
+  int result = snd_midi_event_new( data->bufferSize, &data->coder );
   if ( result < 0 ) {
     delete data;
-    data = NULL; // 1.4.1.0 (ge)
-    errorString_ = "RtMidiOut::initialize: error initializing MIDI event parser!\n\n";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiOutAlsa::initialize: error initializing MIDI event parser!\n\n";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
   data->buffer = (unsigned char *) malloc( data->bufferSize );
   if ( data->buffer == NULL ) {
     delete data;
-    data = NULL; // 1.4.1.0 (ge)
-    errorString_ = "RtMidiOut::initialize: error allocating buffer memory!\n\n";
-    error( RtMidiError::MEMORY_ERROR );
+    errorString_ = "MidiOutAlsa::initialize: error allocating buffer memory!\n\n";
+    error( RtMidiError::MEMORY_ERROR, errorString_ );
+    return;
   }
   snd_midi_event_init( data->coder );
   apiData_ = (void *) data;
 }
 
-void RtMidiOut :: openPort( unsigned int portNumber )
+unsigned int MidiOutAlsa :: getPortCount()
 {
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
+
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  return portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, -1 );
+}
+
+std::string MidiOutAlsa :: getPortName( unsigned int portNumber )
+{
+  snd_seq_client_info_t *cinfo;
+  snd_seq_port_info_t *pinfo;
+  snd_seq_client_info_alloca( &cinfo );
+  snd_seq_port_info_alloca( &pinfo );
+
+  std::string stringName;
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, (int) portNumber ) ) {
+    int cnum = snd_seq_port_info_get_client( pinfo );
+    snd_seq_get_any_client_info( data->seq, cnum, cinfo );
+    std::ostringstream os;
+    os << snd_seq_client_info_get_name( cinfo );
+    os << ":";
+    os << snd_seq_port_info_get_name( pinfo );
+    os << " ";                                    // These lines added to make sure devices are listed
+    os << snd_seq_port_info_get_client( pinfo );  // with full portnames added to ensure individual device names
+    os << ":";
+    os << snd_seq_port_info_get_port( pinfo );
+    stringName = os.str();
+    return stringName;
+  }
+
+  // If we get here, we didn't find a match.
+  errorString_ = "MidiOutAlsa::getPortName: error looking for port name!";
+  error( RtMidiError::WARNING, errorString_ );
+  return stringName;
+}
+
+void MidiOutAlsa :: openPort( unsigned int portNumber, const std::string &portName )
+{
   if ( connected_ ) {
-    errorString_ = "RtMidiOut::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutAlsa::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   unsigned int nSrc = this->getPortCount();
-  if (nSrc < 1) {
-    errorString_ = "RtMidiOut::openPort: no MIDI output sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+  if ( nSrc < 1 ) {
+    errorString_ = "MidiOutAlsa::openPort: no MIDI output sources found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-    snd_seq_port_info_t *pinfo;
-    snd_seq_port_info_alloca( &pinfo );
-  std::ostringstream ost;
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
   if ( portInfo( data->seq, pinfo, SND_SEQ_PORT_CAP_WRITE|SND_SEQ_PORT_CAP_SUBS_WRITE, (int) portNumber ) == 0 ) {
-    ost << "RtMidiOut::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiOutAlsa::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
   snd_seq_addr_t sender, receiver;
@@ -1329,527 +2257,155 @@ void RtMidiOut :: openPort( unsigned int portNumber )
   sender.client = snd_seq_client_id( data->seq );
 
   if ( data->vport < 0 ) {
-    data->vport = snd_seq_create_simple_port( data->seq, "RtMidi Output",
+    data->vport = snd_seq_create_simple_port( data->seq, portName.c_str(),
                                               SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
-                                              SND_SEQ_PORT_TYPE_MIDI_GENERIC );
+                                              SND_SEQ_PORT_TYPE_MIDI_GENERIC|SND_SEQ_PORT_TYPE_APPLICATION );
     if ( data->vport < 0 ) {
-      errorString_ = "RtMidiOut::openPort: ALSA error creating output port.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutAlsa::openPort: ALSA error creating output port.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
   }
 
   sender.port = data->vport;
 
   // Make subscription
-  snd_seq_port_subscribe_malloc( &data->subscription );
-  snd_seq_port_subscribe_set_sender(data->subscription, &sender);
-  snd_seq_port_subscribe_set_dest(data->subscription, &receiver);
-  snd_seq_port_subscribe_set_time_update(data->subscription, 1);
-  snd_seq_port_subscribe_set_time_real(data->subscription, 1);
-  if ( snd_seq_subscribe_port(data->seq, data->subscription) ) {
-    errorString_ = "RtMidiOut::openPort: ALSA error making port connection.";
-    error( RtMidiError::DRIVER_ERROR );
+  if ( snd_seq_port_subscribe_malloc( &data->subscription ) < 0 ) {
+    snd_seq_port_subscribe_free( data->subscription );
+    errorString_ = "MidiOutAlsa::openPort: error allocating port subscription.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
+  snd_seq_port_subscribe_set_sender( data->subscription, &sender );
+  snd_seq_port_subscribe_set_dest( data->subscription, &receiver );
+  snd_seq_port_subscribe_set_time_update( data->subscription, 1 );
+  snd_seq_port_subscribe_set_time_real( data->subscription, 1 );
+  if ( snd_seq_subscribe_port( data->seq, data->subscription ) ) {
+    snd_seq_port_subscribe_free( data->subscription );
+    errorString_ = "MidiOutAlsa::openPort: ALSA error making port connection.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
 
   connected_ = true;
 }
 
-void RtMidiOut :: closePort( void )
+void MidiOutAlsa :: closePort( void )
 {
   if ( connected_ ) {
     AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
     snd_seq_unsubscribe_port( data->seq, data->subscription );
     snd_seq_port_subscribe_free( data->subscription );
+    data->subscription = 0;
     connected_ = false;
   }
 }
 
-void RtMidiOut :: openVirtualPort()
+void MidiOutAlsa :: setClientName( const std::string &clientName )
 {
+
+    AlsaMidiData *data = static_cast<AlsaMidiData *> ( apiData_ );
+    snd_seq_set_client_name( data->seq, clientName.c_str() );
+
+}
+
+void MidiOutAlsa :: setPortName( const std::string &portName )
+{
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
+  snd_seq_port_info_t *pinfo;
+  snd_seq_port_info_alloca( &pinfo );
+  snd_seq_get_port_info( data->seq, data->vport, pinfo );
+  snd_seq_port_info_set_name( pinfo, portName.c_str() );
+  snd_seq_set_port_info( data->seq, data->vport, pinfo );
+}
+
+void MidiOutAlsa :: openVirtualPort( const std::string &portName )
+{
+  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
   if ( data->vport < 0 ) {
-    data->vport = snd_seq_create_simple_port( data->seq, "RtMidi Output",
+    data->vport = snd_seq_create_simple_port( data->seq, portName.c_str(),
                                               SND_SEQ_PORT_CAP_READ|SND_SEQ_PORT_CAP_SUBS_READ,
-                                              SND_SEQ_PORT_TYPE_MIDI_GENERIC );
+                                              SND_SEQ_PORT_TYPE_MIDI_GENERIC|SND_SEQ_PORT_TYPE_APPLICATION );
 
     if ( data->vport < 0 ) {
-      errorString_ = "RtMidiOut::openVirtualPort: ALSA error creating virtual port.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutAlsa::openVirtualPort: ALSA error creating virtual port.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
     }
   }
 }
 
-RtMidiOut :: ~RtMidiOut()
+void MidiOutAlsa :: sendMessage( const unsigned char *message, size_t size )
 {
-  // Close a connection if it exists.
-  closePort();
-
-  // Cleanup.
+  long result;
   AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  if ( data->vport >= 0 ) snd_seq_delete_port( data->seq, data->vport );
-  if ( data->coder ) snd_midi_event_free( data->coder );
-  if ( data->buffer ) free( data->buffer );
-  snd_seq_close( data->seq );
-  delete data;
-}
-
-void RtMidiOut :: sendMessage( std::vector<unsigned char> *message )
-{
-  int result;
-  AlsaMidiData *data = static_cast<AlsaMidiData *> (apiData_);
-  unsigned int nBytes = message->size();
+  unsigned int nBytes = static_cast<unsigned int> (size);
   if ( nBytes > data->bufferSize ) {
     data->bufferSize = nBytes;
-    result = snd_midi_event_resize_buffer ( data->coder, nBytes);
+    result = snd_midi_event_resize_buffer( data->coder, nBytes );
     if ( result != 0 ) {
-      errorString_ = "RtMidiOut::sendMessage: ALSA error resizing MIDI event buffer.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutAlsa::sendMessage: ALSA error resizing MIDI event buffer.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
     free (data->buffer);
     data->buffer = (unsigned char *) malloc( data->bufferSize );
     if ( data->buffer == NULL ) {
-    errorString_ = "RtMidiOut::initialize: error allocating buffer memory!\n\n";
-    error( RtMidiError::MEMORY_ERROR );
+      errorString_ = "MidiOutAlsa::initialize: error allocating buffer memory!\n\n";
+      error( RtMidiError::MEMORY_ERROR, errorString_ );
+      return;
     }
   }
 
-  snd_seq_event_t ev;
-  snd_seq_ev_clear(&ev);
-  snd_seq_ev_set_source(&ev, data->vport);
-  snd_seq_ev_set_subs(&ev);
-  snd_seq_ev_set_direct(&ev);
-  for ( unsigned int i=0; i<nBytes; i++ ) data->buffer[i] = message->at(i);
-  result = snd_midi_event_encode( data->coder, data->buffer, (long)nBytes, &ev );
-  // commenting this out allows sending MIDI messages < and > 3 | 1.4.1.0 (mariobuoninfante)
-  // if( result < (int)nBytes ) {
-  //   errorString_ = "RtMidiOut::sendMessage: event parsing error!";
-  //   error( RtMidiError::WARNING );
-  //   return;
-  // }
+  for ( unsigned int i=0; i<nBytes; ++i ) data->buffer[i] = message[i];
 
-  // Send the event.
-  result = snd_seq_event_output(data->seq, &ev);
-  if ( result < 0 ) {
-    errorString_ = "RtMidiOut::sendMessage: error sending MIDI message to port.";
-    error( RtMidiError::WARNING );
-  }
-  snd_seq_drain_output(data->seq);
-}
-
-#endif // __LINUX_ALSA__
-
-
-//*********************************************************************//
-//  API: IRIX MD
-//*********************************************************************//
-
-// API information gleamed from:
-//   http://techpubs.sgi.com/library/tpl/cgi-bin/getdoc.cgi?cmd=getdoc&coll=0650&db=man&fname=3%20mdIntro
-
-// If the Makefile doesn't work, try the following:
-// CC -o midiinfo -LANG:std -D__IRIX_MD__ -I../ ../RtMidi.cpp midiinfo.cpp -lpthread -lmd
-// CC -o midiout -LANG:std -D__IRIX_MD__ -I../ ../RtMidi.cpp midiout.cpp -lpthread -lmd
-// CC -o qmidiin -LANG:std -D__IRIX_MD__ -I../ ../RtMidi.cpp qmidiin.cpp -lpthread -lmd
-// CC -o cmidiin -LANG:std -D__IRIX_MD__ -I../ ../RtMidi.cpp cmidiin.cpp -lpthread -lmd
-
-#if defined(__IRIX_MD__)
-
-#include <pthread.h>
-#include <sys/time.h>
-#include <unistd.h>
-
-// Irix MIDI header file.
-#include <dmedia/midi.h>
-
-// A structure to hold variables related to the IRIX API
-// implementation.
-struct IrixMidiData {
-  MDport port;
-  pthread_t thread;
-};
-
-//*********************************************************************//
-//  API: IRIX
-//  Class Definitions: RtMidiIn
-//*********************************************************************//
-
-extern "C" void *irixMidiHandler( void *ptr )
-{
-  RtMidiIn::RtMidiInData *data = static_cast<RtMidiIn::RtMidiInData *> (ptr);
-  IrixMidiData *apiData = static_cast<IrixMidiData *> (data->apiData);
-
-  bool continueSysex = false;
-  unsigned char status;
-  unsigned short size;
-  MDevent event;
-  int fd = mdGetFd( apiData->port );
-  if ( fd < 0 ) {
-    data->doInput = false;
-    std::cerr << "\nRtMidiIn::irixMidiHandler: error getting port descriptor!\n\n";
-    return 0;
-  }
-
-  fd_set mask, rmask;
-  FD_ZERO( &mask );
-  FD_SET( fd, &mask );
-  struct timeval timeout = {0, 0};
-  RtMidiIn::MidiMessage message;
-  int result;
-
-  while ( data->doInput ) {
-
-    rmask = mask;
-    timeout.tv_sec = 0;
-    timeout.tv_usec = 0;
-    if ( select( fd+1, &rmask, NULL, NULL, &timeout ) <= 0 ) {
-      // No data pending ... sleep a bit.
-      usleep( 1000 );
-      continue;
+  unsigned int offset = 0;
+  while (offset < nBytes) {
+    snd_seq_event_t ev;
+    snd_seq_ev_clear( &ev );
+    snd_seq_ev_set_source( &ev, data->vport );
+    snd_seq_ev_set_subs( &ev );
+    snd_seq_ev_set_direct( &ev );
+    result = snd_midi_event_encode( data->coder, data->buffer + offset,
+                                    (long)(nBytes - offset), &ev );
+    if ( result < 0 ) {
+      errorString_ = "MidiOutAlsa::sendMessage: event parsing error!";
+      error( RtMidiError::WARNING, errorString_ );
+      return;
     }
 
-    // If here, there should be data.
-    result = mdReceive( apiData->port, &event, 1);
-    if ( result <= 0 ) {
-      std::cerr << "\nRtMidiIn::irixMidiHandler: MIDI input read error!\n\n";
-      continue;
+    if ( ev.type == SND_SEQ_EVENT_NONE ) {
+      errorString_ = "MidiOutAlsa::sendMessage: incomplete message!";
+      error( RtMidiError::WARNING, errorString_ );
+      return;
     }
 
-    message.timeStamp = event.stamp * 0.000000001;
+    offset += result;
 
-    size = 0;
-    status = event.msg[0];
-    if ( !(status & 0x80) ) continue;
-    if ( status == 0xF0 ) {
-      // Sysex message ... can be segmented across multiple messages.
-      if ( !(data->ignoreFlags & 0x01) ) {
-        if ( continueSysex ) {
-          // We have a continuing, segmented sysex message.  Append
-          // the new bytes to our existing message.
-          for ( int i=0; i<event.msglen; i++ )
-            message.bytes.push_back( event.sysexmsg[i] );
-          if ( event.sysexmsg[event.msglen-1] == 0xF7 ) continueSysex = false;
-          if ( !continueSysex ) {
-            // If not a continuing sysex message, invoke the user callback function or queue the message.
-            if ( data->usingCallback && message.bytes.size() > 0 ) {
-              RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) data->userCallback;
-              callback( message.timeStamp, &message.bytes, data->userData );
-            }
-            else {
-              // As long as we haven't reached our queue size limit, push the message.
-              if ( data->queueLimit > data->queue.size() )
-                data->queue.push( message );
-              else
-                std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
-            }
-            message.bytes.clear();
-          }
-        }
-      }
-      mdFree( NULL );
-      continue;
+    // Send the event.
+    result = snd_seq_event_output( data->seq, &ev );
+    if ( result < 0 ) {
+      errorString_ = "MidiOutAlsa::sendMessage: error sending MIDI message to port.";
+      error( RtMidiError::WARNING, errorString_ );
+      return;
     }
-    else if ( status < 0xC0 ) size = 3;
-    else if ( status < 0xE0 ) size = 2;
-    else if ( status < 0xF0 ) size = 3;
-    else if ( status < 0xF3 ) {
-      if ( status == 0xF1 && !(data->ignoreFlags & 0x02) ) {
-        // A MIDI time code message and we're not ignoring it.
-        size = 3;
-      }
-    }
-    else if ( status == 0xF3 ) size = 2;
-    else if ( status == 0xF8 ) {
-      if ( !(data->ignoreFlags & 0x02) ) {
-        // A MIDI timing tick message and we're not ignoring it.
-        size = 1;
-      }
-    }
-    else if ( status == 0xFE ) { // MIDI active sensing
-      if ( !(data->ignoreFlags & 0x04) )
-        size = 1;
-    }
-    else size = 1;
-
-    // Copy the MIDI data to our vector.
-    if ( size ) {
-      message.bytes.assign( &event.msg[0], &event.msg[size] );
-      // Invoke the user callback function or queue the message.
-      if ( data->usingCallback ) {
-        RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) data->userCallback;
-        callback( message.timeStamp, &message.bytes, data->userData );
-      }
-      else {
-        // As long as we haven't reached our queue size limit, push the message.
-        if ( data->queueLimit > data->queue.size() )
-          data->queue.push( message );
-        else
-          std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
-      }
-      message.bytes.clear();
-    }
   }
-
-  return 0;
+  snd_seq_drain_output( data->seq );
 }
 
-void RtMidiIn :: initialize( void )
-{
-  // Initialize the Irix MIDI system.  At the moment, we will not
-  // worry about a return value of zero (ports) because there is a
-  // chance the user could plug something in after instantiation.
-  int nPorts = mdInit();
+#endif // __LINUX_ALSA__ || __FREEBSD_ALSA__
 
-  // Create our api-specific connection information.
-  IrixMidiData *data = (IrixMidiData *) new IrixMidiData;
-  apiData_ = (void *) data;
-  inputData_.apiData = (void *) data;
-}
 
-void RtMidiIn :: openPort( unsigned int portNumber )
-{
-  if ( connected_ ) {
-    errorString_ = "RtMidiIn::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
-    return;
-  }
-
-  int nPorts = mdInit();
-  if (nPorts < 1) {
-    errorString_ = "RtMidiIn::openPort: no Irix MIDI input sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
-  }
-
-  std::ostringstream ost;
-  if ( portNumber >= nPorts ) {
-    ost << "RtMidiIn::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
-
-  IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-  data->port = mdOpenInPort( mdGetName(portNumber) );
-  if ( data->port == NULL ) {
-    ost << "RtMidiIn::openPort: Irix error opening the port (" << portNumber << ").";
-    errorString_ = ost.str();
-    error( RtMidiError::DRIVER_ERROR );
-  }
-  mdSetStampMode(data->port, MD_DELTASTAMP);
-
-  // Start our MIDI input thread.
-  pthread_attr_t attr;
-  pthread_attr_init(&attr);
-  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
-  pthread_attr_setschedpolicy(&attr, SCHED_RR);
-
-  inputData_.doInput = true;
-  int err = pthread_create(&data->thread, &attr, irixMidiHandler, &inputData_);
-  pthread_attr_destroy(&attr);
-  if (err) {
-    mdClosePort( data->port );
-    inputData_.doInput = false;
-    errorString_ = "RtMidiIn::openPort: error starting MIDI input thread!";
-    error( RtMidiError::THREAD_ERROR );
-  }
-
-  connected_ = true;
-}
-
-void RtMidiIn :: openVirtualPort()
-{
-  // This function cannot be implemented for the Irix MIDI API.
-  errorString_ = "RtMidiIn::openVirtualPort: cannot be implemented in Irix MIDI API!";
-  error( RtMidiError::WARNING );
-}
-
-void RtMidiIn :: closePort( void )
-{
-  if ( connected_ ) {
-    IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-    mdClosePort( data->port );
-    connected_ = false;
-
-    // Shutdown the input thread.
-    inputData_.doInput = false;
-    pthread_join( data->thread, NULL );
-  }
-}
-
-RtMidiIn :: ~RtMidiIn()
-{
-  // Close a connection if it exists.
-  closePort();
-
-  // Cleanup.
-  IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-  delete data;
-}
-
-unsigned int RtMidiIn :: getPortCount()
-{
-  int nPorts = mdInit();
-  if ( nPorts >= 0 ) return nPorts;
-  else return 0;
-}
-
-std::string RtMidiIn :: getPortName( unsigned int portNumber )
-{
-  int nPorts = mdInit();
-
-  std::ostringstream ost;
-  if ( portNumber >= nPorts ) {
-    ost << "RtMidiIn::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
-
-  std::string stringName = std::string( mdGetName( portNumber ) );
-  return stringName;
-}
-
 //*********************************************************************//
-//  API: IRIX MD
-//  Class Definitions: RtMidiOut
-//*********************************************************************//
-
-unsigned int RtMidiOut :: getPortCount()
-{
-  int nPorts = mdInit();
-  if ( nPorts >= 0 ) return nPorts;
-  else return 0;
-}
-
-std::string RtMidiOut :: getPortName( unsigned int portNumber )
-{
-  int nPorts = mdInit();
-
-  std::ostringstream ost;
-  if ( portNumber >= nPorts ) {
-    ost << "RtMidiIn::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
-
-  std::string stringName = std::string( mdGetName( portNumber ) );
-  return stringName;
-}
-
-void RtMidiOut :: initialize( void )
-{
-  // Initialize the Irix MIDI system.  At the moment, we will not
-  // worry about a return value of zero (ports) because there is a
-  // chance the user could plug something in after instantiation.
-  int nPorts = mdInit();
-
-  // Create our api-specific connection information.
-  IrixMidiData *data = (IrixMidiData *) new IrixMidiData;
-  apiData_ = (void *) data;
-}
-
-void RtMidiOut :: openPort( unsigned int portNumber )
-{
-  if ( connected_ ) {
-    errorString_ = "RtMidiOut::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
-    return;
-  }
-
-  int nPorts = mdInit();
-  if (nPorts < 1) {
-    errorString_ = "RtMidiOut::openPort: no Irix MIDI output sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
-  }
-
-  std::ostringstream ost;
-  if ( portNumber >= nPorts ) {
-    ost << "RtMidiOut::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
-
-  IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-  data->port = mdOpenOutPort( mdGetName(portNumber) );
-  if ( data->port == NULL ) {
-    ost << "RtMidiOut::openPort: Irix error opening the port (" << portNumber << ").";
-    errorString_ = ost.str();
-    error( RtMidiError::DRIVER_ERROR );
-  }
-  mdSetStampMode(data->port, MD_NOSTAMP);
-
-  connected_ = true;
-}
-
-void RtMidiOut :: closePort( void )
-{
-  if ( connected_ ) {
-    IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-    mdClosePort( data->port );
-    connected_ = false;
-  }
-}
-
-void RtMidiOut :: openVirtualPort()
-{
-  // This function cannot be implemented for the Irix MIDI API.
-  errorString_ = "RtMidiOut::openVirtualPort: cannot be implemented in Irix MIDI API!";
-  error( RtMidiError::WARNING );
-}
-
-RtMidiOut :: ~RtMidiOut()
-{
-  // Close a connection if it exists.
-  closePort();
-
-  // Cleanup.
-  IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-  delete data;
-}
-
-void RtMidiOut :: sendMessage( std::vector<unsigned char> *message )
-{
-  int result;
-  MDevent event;
-  IrixMidiData *data = static_cast<IrixMidiData *> (apiData_);
-  char *buffer = 0;
-
-  unsigned int nBytes = message->size();
-  if ( nBytes == 0 ) return;
-  event.stamp = 0;
-  if ( message->at(0) == 0xF0 ) {
-    if ( nBytes < 3 ) return; // check for bogus sysex
-    event.msg[0] = 0xF0;
-    event.msglen = nBytes;
-    buffer = (char *) malloc( nBytes );
-    for ( int i=0; i<nBytes; i++ ) buffer[i] = message->at(i);
-    event.sysexmsg = buffer;
-  }
-  else {
-    for ( int i=0; i<nBytes; i++ )
-      event.msg[i] = message->at(i);
-  }
-
-  // Send the event.
-  result = mdSend( data->port, &event, 1 );
-  if ( buffer ) free( buffer );
-  if ( result < 1 ) {
-    errorString_ = "RtMidiOut::sendMessage: IRIX error sending MIDI message!";
-    error( RtMidiError::WARNING );
-    return;
-  }
-}
-
-#endif // __IRIX_MD__
-
-//*********************************************************************//
 //  API: Windows Multimedia Library (MM)
 //*********************************************************************//
 
 // API information deciphered from:
 //  - http://msdn.microsoft.com/library/default.asp?url=/library/en-us/multimed/htm/_win32_midi_reference.asp
 
-// chuck
-#if defined(__WINDOWS_DS__)
-//#if defined(__WINDOWS_MM__)
+// Thanks to Jean-Baptiste Berruchon for the sysex code.
 
+#if defined(__WINDOWS_MM__)
+
 // The Windows MM API is based on the use of a callback function for
 // MIDI input.  We convert the system specific time stamps to delta
 // time values.
@@ -1858,37 +2414,71 @@ void RtMidiOut :: sendMessage( std::vector<unsigned ch
 #include <windows.h>
 #include <mmsystem.h>
 
+// Convert a null-terminated wide string or ANSI-encoded string to UTF-8.
+static std::string ConvertToUTF8(const TCHAR *str)
+{
+  std::string u8str;
+  const WCHAR *wstr = L"";
+#if defined( UNICODE ) || defined( _UNICODE )
+  wstr = str;
+#else
+  // Convert from ANSI encoding to wide string
+  int wlength = MultiByteToWideChar( CP_ACP, 0, str, -1, NULL, 0 );
+  std::wstring wstrtemp;
+  if ( wlength )
+  {
+    wstrtemp.assign( wlength - 1, 0 );
+    MultiByteToWideChar( CP_ACP, 0, str, -1, &wstrtemp[0], wlength );
+    wstr = &wstrtemp[0];
+  }
+#endif
+  // Convert from wide string to UTF-8
+  int length = WideCharToMultiByte( CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL );
+  if ( length )
+  {
+    u8str.assign( length - 1, 0 );
+    length = WideCharToMultiByte( CP_UTF8, 0, wstr, -1, &u8str[0], length, NULL, NULL );
+  }
+  return u8str;
+}
+
+#define  RT_SYSEX_BUFFER_SIZE 1024
+#define  RT_SYSEX_BUFFER_COUNT 4
+
 // A structure to hold variables related to the CoreMIDI API
 // implementation.
 struct WinMidiData {
   HMIDIIN inHandle;    // Handle to Midi Input Device
   HMIDIOUT outHandle;  // Handle to Midi Output Device
   DWORD lastTime;
-  RtMidiIn::MidiMessage message;
+  MidiInApi::MidiMessage message;
+  LPMIDIHDR sysexBuffer[RT_SYSEX_BUFFER_COUNT];
+  CRITICAL_SECTION _mutex; // [Patrice] see https://groups.google.com/forum/#!topic/mididev/6OUjHutMpEo
 };
 
 //*********************************************************************//
 //  API: Windows MM
-//  Class Definitions: RtMidiIn
+//  Class Definitions: MidiInWinMM
 //*********************************************************************//
 
-static void CALLBACK midiInputCallback( HMIDIOUT hmin,
-                                        UINT inputStatus, 
-                                        DWORD_PTR instancePtr, // 1.4.1.0 DWORD changed to DWORD_PTR | PR #157 @dbadb
+static void CALLBACK midiInputCallback( HMIDIIN /*hmin*/,
+                                        UINT inputStatus,
+                                        DWORD_PTR instancePtr,
                                         DWORD_PTR midiMessage,
-                                        DWORD_PTR timestamp )
+                                        DWORD timestamp )
 {
-  if ( inputStatus != MIM_DATA && inputStatus != MIM_LONGDATA ) return;
+  if ( inputStatus != MIM_DATA && inputStatus != MIM_LONGDATA && inputStatus != MIM_LONGERROR ) return;
 
-  //RtMidiIn::RtMidiInData *data = static_cast<RtMidiIn::RtMidiInData *> (instancePtr);
-  RtMidiIn::RtMidiInData *data = (RtMidiIn::RtMidiInData *)instancePtr;
+  //MidiInApi::RtMidiInData *data = static_cast<MidiInApi::RtMidiInData *> (instancePtr);
+  MidiInApi::RtMidiInData *data = (MidiInApi::RtMidiInData *)instancePtr;
   WinMidiData *apiData = static_cast<WinMidiData *> (data->apiData);
 
   // Calculate time stamp.
-  apiData->message.timeStamp = 0.0;
-  if ( data->firstMessage == true ) data->firstMessage = false;
+  if ( data->firstMessage == true ) {
+    apiData->message.timeStamp = 0.0;
+    data->firstMessage = false;
+  }
   else apiData->message.timeStamp = (double) ( timestamp - apiData->lastTime ) * 0.001;
-  apiData->lastTime = timestamp;
 
   if ( inputStatus == MIM_DATA ) { // Channel or system message
 
@@ -1901,58 +2491,97 @@ static void CALLBACK midiInputCallback( HMIDIOUT hmin,
     if ( status < 0xC0 ) nBytes = 3;
     else if ( status < 0xE0 ) nBytes = 2;
     else if ( status < 0xF0 ) nBytes = 3;
-    else if ( status < 0xF3 ) {
-      // A MIDI time code message and we're ignoring it.
-      if ( status == 0xF1 && (data->ignoreFlags & 0x02) ) return;
-      nBytes = 3;
+    else if ( status == 0xF1 ) {
+      if ( data->ignoreFlags & 0x02 ) return;
+      else nBytes = 2;
     }
+    else if ( status == 0xF2 ) nBytes = 3;
     else if ( status == 0xF3 ) nBytes = 2;
-    else if ( status == 0xF8 && (data->ignoreFlags & 0x02) ) {
+    else if ( status == 0xF8 && ( data->ignoreFlags & 0x02 ) ) {
       // A MIDI timing tick message and we're ignoring it.
       return;
     }
-    else if ( status == 0xFE && (data->ignoreFlags & 0x04) ) {
+    else if ( status == 0xFE && ( data->ignoreFlags & 0x04 ) ) {
       // A MIDI active sensing message and we're ignoring it.
       return;
     }
 
     // Copy bytes to our MIDI message.
     unsigned char *ptr = (unsigned char *) &midiMessage;
-    for ( int i=0; i<nBytes; i++ ) apiData->message.bytes.push_back( *ptr++ );
+    for ( int i=0; i<nBytes; ++i ) apiData->message.bytes.push_back( *ptr++ );
   }
-  else { // Sysex message
+  else { // Sysex message ( MIM_LONGDATA or MIM_LONGERROR )
     MIDIHDR *sysex = ( MIDIHDR *) midiMessage;
-    for ( int i=0; i<(int)sysex->dwBytesRecorded; i++ )
-      apiData->message.bytes.push_back( sysex->lpData[i] );
-    if ( apiData->message.bytes.back() != 0xF7 ) return;
+    if ( !( data->ignoreFlags & 0x01 ) && inputStatus != MIM_LONGERROR ) {
+      // Sysex message and we're not ignoring it
+      for ( int i=0; i<(int)sysex->dwBytesRecorded; ++i )
+        apiData->message.bytes.push_back( sysex->lpData[i] );
+    }
+
+    // The WinMM API requires that the sysex buffer be requeued after
+    // input of each sysex message.  Even if we are ignoring sysex
+    // messages, we still need to requeue the buffer in case the user
+    // decides to not ignore sysex messages in the future.  However,
+    // it seems that WinMM calls this function with an empty sysex
+    // buffer when an application closes and in this case, we should
+    // avoid requeueing it, else the computer suddenly reboots after
+    // one or two minutes.
+    if ( apiData->sysexBuffer[sysex->dwUser]->dwBytesRecorded > 0 ) {
+      //if ( sysex->dwBytesRecorded > 0 ) {
+      EnterCriticalSection( &(apiData->_mutex) );
+      MMRESULT result = midiInAddBuffer( apiData->inHandle, apiData->sysexBuffer[sysex->dwUser], sizeof(MIDIHDR) );
+      LeaveCriticalSection( &(apiData->_mutex) );
+      if ( result != MMSYSERR_NOERROR )
+        std::cerr << "\nRtMidiIn::midiInputCallback: error sending sysex to Midi device!!\n\n";
+
+      if ( data->ignoreFlags & 0x01 ) return;
+    }
+    else return;
   }
 
+  // Save the time of the last non-filtered message
+  apiData->lastTime = timestamp;
+
   if ( data->usingCallback ) {
     RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) data->userCallback;
     callback( apiData->message.timeStamp, &apiData->message.bytes, data->userData );
   }
   else {
     // As long as we haven't reached our queue size limit, push the message.
-    if ( data->queueLimit > data->queue.size() )
-      data->queue.push( apiData->message );
-    else
-      std::cerr << "\nRtMidiIn: message queue limit reached!!\n\n";
+    if ( !data->queue.push( apiData->message ) )
+      std::cerr << "\nMidiInWinMM: message queue limit reached!!\n\n";
   }
 
-  // Clear the vector for the next input message.  Note that doing
-  // this here allows our code to work for sysex messages which are
-  // segmented across multiple buffers.
+  // Clear the vector for the next input message.
   apiData->message.bytes.clear();
 }
 
-void RtMidiIn :: initialize( void )
+MidiInWinMM :: MidiInWinMM( const std::string &clientName, unsigned int queueSizeLimit )
+  : MidiInApi( queueSizeLimit )
 {
+  MidiInWinMM::initialize( clientName );
+}
+
+MidiInWinMM :: ~MidiInWinMM()
+{
+  // Close a connection if it exists.
+  MidiInWinMM::closePort();
+
+  WinMidiData *data = static_cast<WinMidiData *> (apiData_);
+  DeleteCriticalSection( &(data->_mutex) );
+
+  // Cleanup.
+  delete data;
+}
+
+void MidiInWinMM :: initialize( const std::string& /*clientName*/ )
+{
   // We'll issue a warning here if no devices are available but not
   // throw an error since the user can plugin something later.
   unsigned int nDevices = midiInGetNumDevs();
   if ( nDevices == 0 ) {
-    errorString_ = "RtMidiIn::initialize: no MIDI input devices currently available.";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiInWinMM::initialize: no MIDI input devices currently available.";
+    error( RtMidiError::WARNING, errorString_ );
   }
 
   // Save our api-specific connection information.
@@ -1960,135 +2589,201 @@ void RtMidiIn :: initialize( void )
   apiData_ = (void *) data;
   inputData_.apiData = (void *) data;
   data->message.bytes.clear();  // needs to be empty for first input message
+
+  if ( !InitializeCriticalSectionAndSpinCount( &(data->_mutex), 0x00000400 ) ) {
+    errorString_ = "MidiInWinMM::initialize: InitializeCriticalSectionAndSpinCount failed.";
+    error( RtMidiError::WARNING, errorString_ );
+  }
 }
 
-void RtMidiIn :: openPort( unsigned int portNumber )
+void MidiInWinMM :: openPort( unsigned int portNumber, const std::string &/*portName*/ )
 {
   if ( connected_ ) {
-    errorString_ = "RtMidiIn::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiInWinMM::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   unsigned int nDevices = midiInGetNumDevs();
   if (nDevices == 0) {
-    errorString_ = "RtMidiIn::openPort: no MIDI input sources found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+    errorString_ = "MidiInWinMM::openPort: no MIDI input sources found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-  std::ostringstream ost;
   if ( portNumber >= nDevices ) {
-    ost << "RtMidiIn::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiInWinMM::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
   WinMidiData *data = static_cast<WinMidiData *> (apiData_);
   MMRESULT result = midiInOpen( &data->inHandle,
                                 portNumber,
-                                (DWORD_PTR)&midiInputCallback, // 1.4.1.0 DWORD changed to DWORD_PTR | PR #157 @dbadb
+                                (DWORD_PTR)&midiInputCallback,
                                 (DWORD_PTR)&inputData_,
                                 CALLBACK_FUNCTION );
   if ( result != MMSYSERR_NOERROR ) {
-    errorString_ = "RtMidiIn::openPort: error creating Windows MM MIDI input port.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiInWinMM::openPort: error creating Windows MM MIDI input port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
+  // Allocate and init the sysex buffers.
+  for ( int i=0; i<RT_SYSEX_BUFFER_COUNT; ++i ) {
+    data->sysexBuffer[i] = (MIDIHDR*) new char[ sizeof(MIDIHDR) ];
+    data->sysexBuffer[i]->lpData = new char[ RT_SYSEX_BUFFER_SIZE ];
+    data->sysexBuffer[i]->dwBufferLength = RT_SYSEX_BUFFER_SIZE;
+    data->sysexBuffer[i]->dwUser = i; // We use the dwUser parameter as buffer indicator
+    data->sysexBuffer[i]->dwFlags = 0;
+
+    result = midiInPrepareHeader( data->inHandle, data->sysexBuffer[i], sizeof(MIDIHDR) );
+    if ( result != MMSYSERR_NOERROR ) {
+      midiInClose( data->inHandle );
+      data->inHandle = 0;
+      errorString_ = "MidiInWinMM::openPort: error starting Windows MM MIDI input port (PrepareHeader).";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
+    }
+
+    // Register the buffer.
+    result = midiInAddBuffer( data->inHandle, data->sysexBuffer[i], sizeof(MIDIHDR) );
+    if ( result != MMSYSERR_NOERROR ) {
+      midiInClose( data->inHandle );
+      data->inHandle = 0;
+      errorString_ = "MidiInWinMM::openPort: error starting Windows MM MIDI input port (AddBuffer).";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
+    }
+  }
+
   result = midiInStart( data->inHandle );
   if ( result != MMSYSERR_NOERROR ) {
     midiInClose( data->inHandle );
-    errorString_ = "RtMidiIn::openPort: error starting Windows MM MIDI input port.";
-    error( RtMidiError::DRIVER_ERROR );
+    data->inHandle = 0;
+    errorString_ = "MidiInWinMM::openPort: error starting Windows MM MIDI input port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   connected_ = true;
 }
 
-void RtMidiIn :: openVirtualPort()
+void MidiInWinMM :: openVirtualPort( const std::string &/*portName*/ )
 {
   // This function cannot be implemented for the Windows MM MIDI API.
-  errorString_ = "RtMidiIn::openVirtualPort: cannot be implemented in Windows MM MIDI API!";
-  error( RtMidiError::WARNING );
+  errorString_ = "MidiInWinMM::openVirtualPort: cannot be implemented in Windows MM MIDI API!";
+  error( RtMidiError::WARNING, errorString_ );
 }
 
-void RtMidiIn :: closePort( void )
+void MidiInWinMM :: closePort( void )
 {
   if ( connected_ ) {
     WinMidiData *data = static_cast<WinMidiData *> (apiData_);
+    EnterCriticalSection( &(data->_mutex) );
     midiInReset( data->inHandle );
     midiInStop( data->inHandle );
+
+    for ( int i=0; i<RT_SYSEX_BUFFER_COUNT; ++i ) {
+      int result = midiInUnprepareHeader(data->inHandle, data->sysexBuffer[i], sizeof(MIDIHDR));
+      delete [] data->sysexBuffer[i]->lpData;
+      delete [] data->sysexBuffer[i];
+      if ( result != MMSYSERR_NOERROR ) {
+        midiInClose( data->inHandle );
+        data->inHandle = 0;
+        errorString_ = "MidiInWinMM::openPort: error closing Windows MM MIDI input port (midiInUnprepareHeader).";
+        error( RtMidiError::DRIVER_ERROR, errorString_ );
+        return;
+      }
+    }
+
     midiInClose( data->inHandle );
+    data->inHandle = 0;
     connected_ = false;
+    LeaveCriticalSection( &(data->_mutex) );
   }
 }
 
-RtMidiIn :: ~RtMidiIn()
+void MidiInWinMM :: setClientName ( const std::string& )
 {
-  // Close a connection if it exists.
-  closePort();
 
-  // Cleanup.
-  WinMidiData *data = static_cast<WinMidiData *> (apiData_);
-  delete data;
+  errorString_ = "MidiInWinMM::setClientName: this function is not implemented for the WINDOWS_MM API!";
+  error( RtMidiError::WARNING, errorString_ );
+
 }
 
-unsigned int RtMidiIn :: getPortCount()
+void MidiInWinMM :: setPortName ( const std::string& )
 {
+
+  errorString_ = "MidiInWinMM::setPortName: this function is not implemented for the WINDOWS_MM API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+unsigned int MidiInWinMM :: getPortCount()
+{
   return midiInGetNumDevs();
 }
 
-std::string RtMidiIn :: getPortName( unsigned int portNumber )
+std::string MidiInWinMM :: getPortName( unsigned int portNumber )
 {
+  std::string stringName;
   unsigned int nDevices = midiInGetNumDevs();
   if ( portNumber >= nDevices ) {
     std::ostringstream ost;
-    ost << "RtMidiIn::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
+    ost << "MidiInWinMM::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::WARNING, errorString_ );
+    return stringName;
   }
 
   MIDIINCAPS deviceCaps;
-  MMRESULT result = midiInGetDevCaps( portNumber, &deviceCaps, sizeof(MIDIINCAPS));
+  midiInGetDevCaps( portNumber, &deviceCaps, sizeof(MIDIINCAPS));
+  stringName = ConvertToUTF8( deviceCaps.szPname );
 
-  std::string stringName = std::string( deviceCaps.szPname );
+  // Next lines added to add the portNumber to the name so that
+  // the device's names are sure to be listed with individual names
+  // even when they have the same brand name
+#ifndef RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES
+  std::ostringstream os;
+  os << " ";
+  os << portNumber;
+  stringName += os.str();
+#endif
+
   return stringName;
 }
 
 //*********************************************************************//
 //  API: Windows MM
-//  Class Definitions: RtMidiOut
+//  Class Definitions: MidiOutWinMM
 //*********************************************************************//
 
-unsigned int RtMidiOut :: getPortCount()
+MidiOutWinMM :: MidiOutWinMM( const std::string &clientName ) : MidiOutApi()
 {
-  return midiOutGetNumDevs();
+  MidiOutWinMM::initialize( clientName );
 }
 
-std::string RtMidiOut :: getPortName( unsigned int portNumber )
+MidiOutWinMM :: ~MidiOutWinMM()
 {
-  unsigned int nDevices = midiOutGetNumDevs();
-  if ( portNumber >= nDevices ) {
-    std::ostringstream ost;
-    ost << "RtMidiOut::getPortName: 'portNumber' argument (" << portNumber << ") is invalid.";
-    errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
-  }
+  // Close a connection if it exists.
+  MidiOutWinMM::closePort();
 
-  MIDIOUTCAPS deviceCaps;
-  MMRESULT result = midiOutGetDevCaps( portNumber, &deviceCaps, sizeof(MIDIOUTCAPS));
-
-  std::string stringName = std::string( deviceCaps.szPname );
-  return stringName;
+  // Cleanup.
+  WinMidiData *data = static_cast<WinMidiData *> (apiData_);
+  delete data;
 }
 
-void RtMidiOut :: initialize( void )
+void MidiOutWinMM :: initialize( const std::string& /*clientName*/ )
 {
   // We'll issue a warning here if no devices are available but not
   // throw an error since the user can plug something in later.
   unsigned int nDevices = midiOutGetNumDevs();
   if ( nDevices == 0 ) {
-    errorString_ = "RtMidiOut::initialize: no MIDI output devices currently available.";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutWinMM::initialize: no MIDI output devices currently available.";
+    error( RtMidiError::WARNING, errorString_ );
   }
 
   // Save our api-specific connection information.
@@ -2096,25 +2791,61 @@ void RtMidiOut :: initialize( void )
   apiData_ = (void *) data;
 }
 
-void RtMidiOut :: openPort( unsigned int portNumber )
+unsigned int MidiOutWinMM :: getPortCount()
 {
+  return midiOutGetNumDevs();
+}
+
+std::string MidiOutWinMM :: getPortName( unsigned int portNumber )
+{
+  std::string stringName;
+  unsigned int nDevices = midiOutGetNumDevs();
+  if ( portNumber >= nDevices ) {
+    std::ostringstream ost;
+    ost << "MidiOutWinMM::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
+    errorString_ = ost.str();
+    error( RtMidiError::WARNING, errorString_ );
+    return stringName;
+  }
+
+  MIDIOUTCAPS deviceCaps;
+  midiOutGetDevCaps( portNumber, &deviceCaps, sizeof( MIDIOUTCAPS ) );
+  stringName = ConvertToUTF8( deviceCaps.szPname );
+
+  // Next lines added to add the portNumber to the name so that
+  // the device's names are sure to be listed with individual names
+  // even when they have the same brand name
+  std::ostringstream os;
+#ifndef RTMIDI_DO_NOT_ENSURE_UNIQUE_PORTNAMES
+  os << " ";
+  os << portNumber;
+  stringName += os.str();
+#endif
+
+  return stringName;
+}
+
+void MidiOutWinMM :: openPort( unsigned int portNumber, const std::string &/*portName*/ )
+{
   if ( connected_ ) {
-    errorString_ = "RtMidiOut::openPort: a valid connection already exists!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutWinMM::openPort: a valid connection already exists!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   unsigned int nDevices = midiOutGetNumDevs();
-  if (nDevices < 1) {
-    errorString_ = "RtMidiOut::openPort: no MIDI output destinations found!";
-    error( RtMidiError::NO_DEVICES_FOUND );
+  if ( nDevices < 1 ) {
+    errorString_ = "MidiOutWinMM::openPort: no MIDI output destinations found!";
+    error( RtMidiError::NO_DEVICES_FOUND, errorString_ );
+    return;
   }
 
-  std::ostringstream ost;
   if ( portNumber >= nDevices ) {
-    ost << "RtMidiOut::openPort: 'portNumber' argument (" << portNumber << ") is invalid.";
+    std::ostringstream ost;
+    ost << "MidiOutWinMM::openPort: the 'portNumber' argument (" << portNumber << ") is invalid.";
     errorString_ = ost.str();
-    error( RtMidiError::INVALID_PARAMETER );
+    error( RtMidiError::INVALID_PARAMETER, errorString_ );
+    return;
   }
 
   WinMidiData *data = static_cast<WinMidiData *> (apiData_);
@@ -2124,110 +2855,122 @@ void RtMidiOut :: openPort( unsigned int portNumber )
                                  (DWORD)NULL,
                                  CALLBACK_NULL );
   if ( result != MMSYSERR_NOERROR ) {
-    errorString_ = "RtMidiOut::openPort: error creating Windows MM MIDI output port.";
-    error( RtMidiError::DRIVER_ERROR );
+    errorString_ = "MidiOutWinMM::openPort: error creating Windows MM MIDI output port.";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
   }
 
   connected_ = true;
 }
 
-void RtMidiOut :: closePort( void )
+void MidiOutWinMM :: closePort( void )
 {
   if ( connected_ ) {
     WinMidiData *data = static_cast<WinMidiData *> (apiData_);
     midiOutReset( data->outHandle );
     midiOutClose( data->outHandle );
+    data->outHandle = 0;
     connected_ = false;
   }
 }
 
-void RtMidiOut :: openVirtualPort()
+void MidiOutWinMM :: setClientName ( const std::string& )
 {
-  // This function cannot be implemented for the Windows MM MIDI API.
-  errorString_ = "RtMidiOut::openVirtualPort: cannot be implemented in Windows MM MIDI API!";
-  error( RtMidiError::WARNING );
+
+  errorString_ = "MidiOutWinMM::setClientName: this function is not implemented for the WINDOWS_MM API!";
+  error( RtMidiError::WARNING, errorString_ );
+
 }
 
-RtMidiOut :: ~RtMidiOut()
+void MidiOutWinMM :: setPortName ( const std::string& )
 {
-  // Close a connection if it exists.
-  closePort();
 
-  // Cleanup.
-  WinMidiData *data = static_cast<WinMidiData *> (apiData_);
-  delete data;
+  errorString_ = "MidiOutWinMM::setPortName: this function is not implemented for the WINDOWS_MM API!";
+  error( RtMidiError::WARNING, errorString_ );
+
 }
 
-void RtMidiOut :: sendMessage( std::vector<unsigned char> *message )
+void MidiOutWinMM :: openVirtualPort( const std::string &/*portName*/ )
 {
-  unsigned int nBytes = message->size();
+  // This function cannot be implemented for the Windows MM MIDI API.
+  errorString_ = "MidiOutWinMM::openVirtualPort: cannot be implemented in Windows MM MIDI API!";
+  error( RtMidiError::WARNING, errorString_ );
+}
+
+void MidiOutWinMM :: sendMessage( const unsigned char *message, size_t size )
+{
+  if ( !connected_ ) return;
+
+  unsigned int nBytes = static_cast<unsigned int>(size);
   if ( nBytes == 0 ) {
-    errorString_ = "RtMidiOut::sendMessage: message argument is empty!";
-    error( RtMidiError::WARNING );
+    errorString_ = "MidiOutWinMM::sendMessage: message argument is empty!";
+    error( RtMidiError::WARNING, errorString_ );
     return;
   }
 
   MMRESULT result;
   WinMidiData *data = static_cast<WinMidiData *> (apiData_);
-  if ( message->at(0) == 0xF0 ) { // Sysex message
+  if ( message[0] == 0xF0 ) { // Sysex message
 
     // Allocate buffer for sysex data.
     char *buffer = (char *) malloc( nBytes );
     if ( buffer == NULL ) {
-      errorString_ = "RtMidiOut::sendMessage: error allocating sysex message memory!";
-      error( RtMidiError::MEMORY_ERROR );
+      errorString_ = "MidiOutWinMM::sendMessage: error allocating sysex message memory!";
+      error( RtMidiError::MEMORY_ERROR, errorString_ );
+      return;
     }
 
     // Copy data to buffer.
-    for ( unsigned int i=0; i<nBytes; i++ ) buffer[i] = message->at(i);
+    for ( unsigned int i=0; i<nBytes; ++i ) buffer[i] = message[i];
 
     // Create and prepare MIDIHDR structure.
     MIDIHDR sysex;
     sysex.lpData = (LPSTR) buffer;
     sysex.dwBufferLength = nBytes;
     sysex.dwFlags = 0;
-    result = midiOutPrepareHeader( data->outHandle,  &sysex, sizeof(MIDIHDR) ); 
+    result = midiOutPrepareHeader( data->outHandle,  &sysex, sizeof( MIDIHDR ) );
     if ( result != MMSYSERR_NOERROR ) {
       free( buffer );
-      errorString_ = "RtMidiOut::sendMessage: error preparing sysex header.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutWinMM::sendMessage: error preparing sysex header.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
 
     // Send the message.
-    result = midiOutLongMsg( data->outHandle, &sysex, sizeof(MIDIHDR) );
+    result = midiOutLongMsg( data->outHandle, &sysex, sizeof( MIDIHDR ) );
     if ( result != MMSYSERR_NOERROR ) {
       free( buffer );
-      errorString_ = "RtMidiOut::sendMessage: error sending sysex message.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutWinMM::sendMessage: error sending sysex message.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
+      return;
     }
 
     // Unprepare the buffer and MIDIHDR.
-    while ( MIDIERR_STILLPLAYING == midiOutUnprepareHeader( data->outHandle, &sysex, sizeof (MIDIHDR) ) ) Sleep( 1 );
+    while ( MIDIERR_STILLPLAYING == midiOutUnprepareHeader( data->outHandle, &sysex, sizeof ( MIDIHDR ) ) ) Sleep( 1 );
     free( buffer );
-
   }
   else { // Channel or system message.
 
     // Make sure the message size isn't too big.
     if ( nBytes > 3 ) {
-      errorString_ = "RtMidiOut::sendMessage: message size is greater than 3 bytes (and not sysex)!";
-      error( RtMidiError::WARNING );
+      errorString_ = "MidiOutWinMM::sendMessage: message size is greater than 3 bytes (and not sysex)!";
+      error( RtMidiError::WARNING, errorString_ );
       return;
     }
 
     // Pack MIDI bytes into double word.
     DWORD packet;
     unsigned char *ptr = (unsigned char *) &packet;
-    for ( unsigned int i=0; i<nBytes; i++ ) {
-      *ptr = message->at(i);
-      ptr++;
+    for ( unsigned int i=0; i<nBytes; ++i ) {
+      *ptr = message[i];
+      ++ptr;
     }
 
     // Send the message immediately.
     result = midiOutShortMsg( data->outHandle, packet );
     if ( result != MMSYSERR_NOERROR ) {
-      errorString_ = "RtMidiOut::sendMessage: error sending MIDI message.";
-      error( RtMidiError::DRIVER_ERROR );
+      errorString_ = "MidiOutWinMM::sendMessage: error sending MIDI message.";
+      error( RtMidiError::DRIVER_ERROR, errorString_ );
     }
   }
 }
@@ -2235,91 +2978,524 @@ void RtMidiOut :: sendMessage( std::vector<unsigned ch
 #endif  // __WINDOWS_MM__
 
 
-#if defined(__LINUX_OSS__)  // dummy
+//*********************************************************************//
+//  API: UNIX JACK
+//
+//  Written primarily by Alexander Svetalkin, with updates for delta
+//  time by Gary Scavone, April 2011.
+//
+//  *********************************************************************//
 
-/*void midiInputCallback( const MIDIPacketList *list, void *procRef, void *srcRef )
+#if defined(__UNIX_JACK__) || defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)
+
+// JACK header files
+#include <jack/jack.h>
+#include <jack/midiport.h>
+#include <jack/ringbuffer.h>
+#ifdef HAVE_SEMAPHORE
+  #include <semaphore.h>
+#endif
+
+#define JACK_RINGBUFFER_SIZE 16384 // Default size for ringbuffer
+
+struct JackMidiData {
+  jack_client_t *client;
+  jack_port_t *port;
+  jack_ringbuffer_t *buffSize;
+  jack_ringbuffer_t *buffMessage;
+  jack_time_t lastTime;
+#ifdef HAVE_SEMAPHORE
+  sem_t sem_cleanup;
+  sem_t sem_needpost;
+#endif
+  MidiInApi :: RtMidiInData *rtMidiIn;
+  };
+
+//*********************************************************************//
+//  API: JACK
+//  Class Definitions: MidiInJack
+//*********************************************************************//
+
+static int jackProcessIn( jack_nframes_t nframes, void *arg )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *jData = (JackMidiData *) arg;
+  MidiInApi :: RtMidiInData *rtData = jData->rtMidiIn;
+  jack_midi_event_t event;
+  jack_time_t time;
+
+  // Is port created?
+  if ( jData->port == NULL ) return 0;
+
+  void *buff = jack_port_get_buffer( jData->port, nframes );
+  bool& continueSysex = rtData->continueSysex;
+  unsigned char& ignoreFlags = rtData->ignoreFlags;
+
+  // We have midi events in buffer
+  int evCount = jack_midi_get_event_count( buff );
+  for (int j = 0; j < evCount; j++) {
+    MidiInApi::MidiMessage& message = rtData->message;
+    jack_midi_event_get( &event, buff, j );
+
+    // Compute the delta time.
+    time = jack_get_time();
+    if ( rtData->firstMessage == true ) {
+      message.timeStamp = 0.0;
+      rtData->firstMessage = false;
+    } else
+      message.timeStamp = ( time - jData->lastTime ) * 0.000001;
+
+    jData->lastTime = time;
+
+    if ( !continueSysex )
+      message.bytes.clear();
+
+    if ( !( ( continueSysex || event.buffer[0] == 0xF0 ) && ( ignoreFlags & 0x01 ) ) ) {
+      // Unless this is a (possibly continued) SysEx message and we're ignoring SysEx,
+      // copy the event buffer into the MIDI message struct.
+      for ( unsigned int i = 0; i < event.size; i++ )
+        message.bytes.push_back( event.buffer[i] );
+    }
+
+    switch ( event.buffer[0] ) {
+      case 0xF0:
+        // Start of a SysEx message
+        continueSysex = event.buffer[event.size - 1] != 0xF7;
+        if ( ignoreFlags & 0x01 ) continue;
+        break;
+      case 0xF1:
+      case 0xF8:
+        // MIDI Time Code or Timing Clock message
+        if ( ignoreFlags & 0x02 ) continue;
+        break;
+      case 0xFE:
+        // Active Sensing message
+        if ( ignoreFlags & 0x04 ) continue;
+        break;
+      default:
+        if ( continueSysex ) {
+          // Continuation of a SysEx message
+          continueSysex = event.buffer[event.size - 1] != 0xF7;
+          if ( ignoreFlags & 0x01 ) continue;
+        }
+        // All other MIDI messages
+    }
+
+    if ( !continueSysex ) {
+      // If not a continuation of a SysEx message,
+      // invoke the user callback function or queue the message.
+      if ( rtData->usingCallback ) {
+        RtMidiIn::RtMidiCallback callback = (RtMidiIn::RtMidiCallback) rtData->userCallback;
+        callback( message.timeStamp, &message.bytes, rtData->userData );
+      }
+      else {
+        // As long as we haven't reached our queue size limit, push the message.
+        if ( !rtData->queue.push( message ) )
+          std::cerr << "\nMidiInJack: message queue limit reached!!\n\n";
+      }
+    }
+  }
+
+  return 0;
 }
-*/
-void RtMidiIn :: initialize( void )
+
+MidiInJack :: MidiInJack( const std::string &clientName, unsigned int queueSizeLimit )
+  : MidiInApi( queueSizeLimit )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  MidiInJack::initialize( clientName );
 }
 
-void RtMidiIn :: openPort( unsigned int portNumber )
+void MidiInJack :: initialize( const std::string& clientName )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = new JackMidiData;
+  apiData_ = (void *) data;
+
+  data->rtMidiIn = &inputData_;
+  data->port = NULL;
+  data->client = NULL;
+  this->clientName = clientName;
+
+  connect();
 }
 
-void RtMidiIn :: openVirtualPort()
+void MidiInJack :: connect()
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  if ( data->client )
+    return;
+
+  // Initialize JACK client
+  if (( data->client = jack_client_open( clientName.c_str(), JackNoStartServer, NULL )) == 0) {
+    errorString_ = "MidiInJack::initialize: JACK server not running?";
+    error( RtMidiError::WARNING, errorString_ );
+    return;
+  }
+
+  jack_set_process_callback( data->client, jackProcessIn, data );
+  jack_activate( data->client );
 }
 
-void RtMidiIn :: closePort( void )
+MidiInJack :: ~MidiInJack()
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  MidiInJack::closePort();
+
+  if ( data->client )
+    jack_client_close( data->client );
+  delete data;
 }
 
-RtMidiIn :: ~RtMidiIn()
+void MidiInJack :: openPort( unsigned int portNumber, const std::string &portName )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  connect();
+
+  // Creating new port
+  if ( data->port == NULL )
+    data->port = jack_port_register( data->client, portName.c_str(),
+                                     JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0 );
+
+  if ( data->port == NULL ) {
+    errorString_ = "MidiInJack::openPort: JACK error creating port";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
+
+  // Connecting to the output
+  std::string name = getPortName( portNumber );
+  jack_connect( data->client, name.c_str(), jack_port_name( data->port ) );
+
+  connected_ = true;
 }
 
-unsigned int RtMidiIn :: getPortCount()
+void MidiInJack :: openVirtualPort( const std::string &portName )
 {
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  connect();
+  if ( data->port == NULL )
+    data->port = jack_port_register( data->client, portName.c_str(),
+                                     JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0 );
+
+  if ( data->port == NULL ) {
+    errorString_ = "MidiInJack::openVirtualPort: JACK error creating virtual port";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+  }
+}
+
+unsigned int MidiInJack :: getPortCount()
+{
+  int count = 0;
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  connect();
+  if ( !data->client )
     return 0;
+
+  // List of available ports
+  const char **ports = jack_get_ports( data->client, NULL, JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput );
+
+  if ( ports == NULL ) return 0;
+  while ( ports[count] != NULL )
+    count++;
+
+  free( ports );
+
+  return count;
 }
 
-std::string RtMidiIn :: getPortName( unsigned int portNumber )
+std::string MidiInJack :: getPortName( unsigned int portNumber )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
-    return "";
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  std::string retStr( "" );
+
+  connect();
+
+  // List of available ports
+  const char **ports = jack_get_ports( data->client, NULL,
+                                       JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput );
+
+  // Check port validity
+  if ( ports == NULL ) {
+    errorString_ = "MidiInJack::getPortName: no ports available!";
+    error( RtMidiError::WARNING, errorString_ );
+    return retStr;
+  }
+
+  unsigned int i;
+  for ( i=0; i<portNumber && ports[i]; i++ ) {}
+  if ( i < portNumber || !ports[portNumber] ) {
+    std::ostringstream ost;
+    ost << "MidiInJack::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
+    errorString_ = ost.str();
+    error( RtMidiError::WARNING, errorString_ );
+  }
+  else retStr.assign( ports[portNumber] );
+
+  jack_free( ports );
+  return retStr;
 }
 
+void MidiInJack :: closePort()
+{
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  if ( data->port == NULL ) return;
+  jack_port_unregister( data->client, data->port );
+  data->port = NULL;
+
+  connected_ = false;
+}
+
+void MidiInJack:: setClientName( const std::string& )
+{
+
+  errorString_ = "MidiInJack::setClientName: this function is not implemented for the UNIX_JACK API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+void MidiInJack :: setPortName( const std::string &portName )
+{
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+#ifdef JACK_HAS_PORT_RENAME
+  jack_port_rename( data->client, data->port, portName.c_str() );
+#else
+  jack_port_set_name( data->port, portName.c_str() );
+#endif
+}
+
 //*********************************************************************//
-//  API: OS-X
-//  Class Definitions: RtMidiOut
+//  API: JACK
+//  Class Definitions: MidiOutJack
 //*********************************************************************//
 
-unsigned int RtMidiOut :: getPortCount()
+// Jack process callback
+static int jackProcessOut( jack_nframes_t nframes, void *arg )
 {
-    return 0;
+  JackMidiData *data = (JackMidiData *) arg;
+  jack_midi_data_t *midiData;
+  int space;
+
+  // Is port created?
+  if ( data->port == NULL ) return 0;
+
+  void *buff = jack_port_get_buffer( data->port, nframes );
+  jack_midi_clear_buffer( buff );
+
+  while ( jack_ringbuffer_read_space( data->buffSize ) > 0 ) {
+    jack_ringbuffer_read( data->buffSize, (char *) &space, (size_t) sizeof( space ) );
+    midiData = jack_midi_event_reserve( buff, 0, space );
+
+    jack_ringbuffer_read( data->buffMessage, (char *) midiData, (size_t) space );
+  }
+
+#ifdef HAVE_SEMAPHORE
+  if ( !sem_trywait( &data->sem_needpost ) )
+    sem_post( &data->sem_cleanup );
+#endif
+
+  return 0;
 }
 
-std::string RtMidiOut :: getPortName( unsigned int portNumber )
+MidiOutJack :: MidiOutJack( const std::string &clientName ) : MidiOutApi()
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
-    return "";
+  MidiOutJack::initialize( clientName );
 }
 
-void RtMidiOut :: initialize( void )
+void MidiOutJack :: initialize( const std::string& clientName )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = new JackMidiData;
+  apiData_ = (void *) data;
+
+  data->port = NULL;
+  data->client = NULL;
+#ifdef HAVE_SEMAPHORE
+  sem_init( &data->sem_cleanup, 0, 0 );
+  sem_init( &data->sem_needpost, 0, 0 );
+#endif
+  this->clientName = clientName;
+
+  connect();
 }
 
-void RtMidiOut :: openPort( unsigned int portNumber )
+void MidiOutJack :: connect()
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  if ( data->client )
+    return;
+
+  // Initialize output ringbuffers
+  data->buffSize = jack_ringbuffer_create( JACK_RINGBUFFER_SIZE );
+  data->buffMessage = jack_ringbuffer_create( JACK_RINGBUFFER_SIZE );
+
+  // Initialize JACK client
+  if ( ( data->client = jack_client_open( clientName.c_str(), JackNoStartServer, NULL ) ) == 0 ) {
+    errorString_ = "MidiOutJack::initialize: JACK server not running?";
+    error( RtMidiError::WARNING, errorString_ );
+    return;
+  }
+
+  jack_set_process_callback( data->client, jackProcessOut, data );
+  jack_activate( data->client );
 }
 
-void RtMidiOut :: closePort( void )
+MidiOutJack :: ~MidiOutJack()
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  MidiOutJack::closePort();
+
+  // Cleanup
+  jack_ringbuffer_free( data->buffSize );
+  jack_ringbuffer_free( data->buffMessage );
+  if ( data->client ) {
+    jack_client_close( data->client );
+  }
+
+#ifdef HAVE_SEMAPHORE
+  sem_destroy( &data->sem_cleanup );
+  sem_destroy( &data->sem_needpost );
+#endif
+
+  delete data;
 }
 
-void RtMidiOut :: openVirtualPort()
+void MidiOutJack :: openPort( unsigned int portNumber, const std::string &portName )
 {
-    fprintf( stderr, "[chuck](via rtmidi): midi not supported for this platform\n" );
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  connect();
+
+  // Creating new port
+  if ( data->port == NULL )
+    data->port = jack_port_register( data->client, portName.c_str(),
+                                     JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0 );
+
+  if ( data->port == NULL ) {
+    errorString_ = "MidiOutJack::openPort: JACK error creating port";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+    return;
+  }
+
+  // Connecting to the output
+  std::string name = getPortName( portNumber );
+  jack_connect( data->client, jack_port_name( data->port ), name.c_str() );
+
+  connected_ = true;
 }
 
-RtMidiOut :: ~RtMidiOut()
+void MidiOutJack :: openVirtualPort( const std::string &portName )
 {
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  connect();
+  if ( data->port == NULL )
+    data->port = jack_port_register( data->client, portName.c_str(),
+                                     JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0 );
+
+  if ( data->port == NULL ) {
+    errorString_ = "MidiOutJack::openVirtualPort: JACK error creating virtual port";
+    error( RtMidiError::DRIVER_ERROR, errorString_ );
+  }
 }
 
-void RtMidiOut :: sendMessage( std::vector<unsigned char> *message )
+unsigned int MidiOutJack :: getPortCount()
 {
+  int count = 0;
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  connect();
+  if ( !data->client )
+    return 0;
+
+  // List of available ports
+  const char **ports = jack_get_ports( data->client, NULL,
+                                       JACK_DEFAULT_MIDI_TYPE, JackPortIsInput );
+
+  if ( ports == NULL ) return 0;
+  while ( ports[count] != NULL )
+    count++;
+
+  free( ports );
+
+  return count;
 }
 
-#endif  // dummy
+std::string MidiOutJack :: getPortName( unsigned int portNumber )
+{
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+  std::string retStr("");
+
+  connect();
+
+  // List of available ports
+  const char **ports = jack_get_ports( data->client, NULL,
+                                       JACK_DEFAULT_MIDI_TYPE, JackPortIsInput );
+
+  // Check port validity
+  if ( ports == NULL ) {
+    errorString_ = "MidiOutJack::getPortName: no ports available!";
+    error( RtMidiError::WARNING, errorString_ );
+    return retStr;
+  }
+
+  if ( ports[portNumber] == NULL ) {
+    std::ostringstream ost;
+    ost << "MidiOutJack::getPortName: the 'portNumber' argument (" << portNumber << ") is invalid.";
+    errorString_ = ost.str();
+    error( RtMidiError::WARNING, errorString_ );
+  }
+  else retStr.assign( ports[portNumber] );
+
+  free( ports );
+  return retStr;
+}
+
+void MidiOutJack :: closePort()
+{
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  if ( data->port == NULL ) return;
+
+#ifdef HAVE_SEMAPHORE
+  struct timespec ts;
+  if ( clock_gettime( CLOCK_REALTIME, &ts ) != -1 ) {
+    ts.tv_sec += 1; // wait max one second
+    sem_post( &data->sem_needpost );
+    sem_timedwait( &data->sem_cleanup, &ts );
+  }
+#endif
+
+  jack_port_unregister( data->client, data->port );
+  data->port = NULL;
+
+  connected_ = false;
+}
+
+void MidiOutJack:: setClientName( const std::string& )
+{
+
+  errorString_ = "MidiOutJack::setClientName: this function is not implemented for the UNIX_JACK API!";
+  error( RtMidiError::WARNING, errorString_ );
+
+}
+
+void MidiOutJack :: setPortName( const std::string &portName )
+{
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+#ifdef JACK_HAS_PORT_RENAME
+  jack_port_rename( data->client, data->port, portName.c_str() );
+#else
+  jack_port_set_name( data->port, portName.c_str() );
+#endif
+}
+
+void MidiOutJack :: sendMessage( const unsigned char *message, size_t size )
+{
+  int nBytes = static_cast<int>(size);
+  JackMidiData *data = static_cast<JackMidiData *> (apiData_);
+
+  // Write full message to buffer
+  jack_ringbuffer_write( data->buffMessage, ( const char * ) message, nBytes );
+  jack_ringbuffer_write( data->buffSize, ( char * ) &nBytes, sizeof( nBytes ) );
+}
+
+#endif  // __UNIX_JACK__ || __FREEBSD_OSS__ || __LINUX_OSS__

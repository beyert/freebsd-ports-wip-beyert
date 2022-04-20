--- libs/JUCE/modules/juce_audio_processors/format_types/VST3_SDK/pluginterfaces/base/funknown.cpp.orig	2021-09-09 12:31:55 UTC
+++ libs/JUCE/modules/juce_audio_processors/format_types/VST3_SDK/pluginterfaces/base/funknown.cpp
@@ -49,13 +49,16 @@
 #if defined (__ANDROID__) || defined(_LIBCPP_VERSION)
 #define SMTG_USE_STDATOMIC_H 1
 #else
-#include <ext/atomicity.h>
+//#include <ext/atomicity.h>
 #endif
 #endif // !defined (SMTG_USE_STDATOMIC_H)
 #include <stdlib.h>
 #endif
 
 #if defined (SMTG_USE_STDATOMIC_H) && SMTG_USE_STDATOMIC_H 
+// #include <sys/types.h>
+#include <stdbool.h>
+typedef bool _Bool;
 #include <stdatomic.h>
 #endif
 
@@ -100,7 +103,7 @@ int32 PLUGIN_API atomicAdd (int32& var, int32 d)
 	return OSAtomicAdd32Barrier (d, (int32_t*)&var);
 #elif defined(__ANDROID__)
 	return atomic_fetch_add ((atomic_int*)&var, d) + d;
-#elif SMTG_OS_LINUX
+#elif SMTG_OS_LINUX && !defined(__FreeBSD__)
 	__gnu_cxx::__atomic_add (&var, d);
 	return var;
 #else

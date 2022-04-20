--- libs/JUCE/modules/juce_audio_processors/format_types/juce_VST3Headers.h.orig	2021-09-09 12:31:55 UTC
+++ libs/JUCE/modules/juce_audio_processors/format_types/juce_VST3Headers.h
@@ -23,10 +23,6 @@
   ==============================================================================
 */
 
-#if JUCE_BSD && ! JUCE_CUSTOM_VST3_SDK
- #error To build JUCE VST3 plug-ins on BSD you must use an external BSD-compatible VST3 SDK with JUCE_CUSTOM_VST3_SDK=1
-#endif
-
 // Wow, those Steinberg guys really don't worry too much about compiler warnings.
 JUCE_BEGIN_IGNORE_WARNINGS_LEVEL_MSVC (0, 4505 4702 6011 6031 6221 6386 6387 6330 6001 28199)
 

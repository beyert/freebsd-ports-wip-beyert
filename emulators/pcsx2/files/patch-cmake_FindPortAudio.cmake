--- cmake/FindPortAudio.cmake.orig	2014-01-24 10:07:08.000000000 -0800
+++ cmake/FindPortAudio.cmake	2014-03-23 20:47:47.000000000 -0700
@@ -16,7 +16,7 @@
 # finally the library itself
 find_library(libPortAudio NAMES portaudio)
 # Run OK without libportaudiocpp so do not pull additional dependency
-set(PORTAUDIO_LIBRARIES ${libPortAudio})
+set(PORTAUDIO_LIBRARIES "/usr/local/lib/portaudio2")
 
 # handle the QUIETLY and REQUIRED arguments and set PORTAUDIO_FOUND to TRUE if 
 # all listed variables are TRUE

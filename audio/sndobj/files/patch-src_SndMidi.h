--- src/SndMidi.h.orig	2011-06-03 13:17:13 UTC
+++ src/SndMidi.h
@@ -34,7 +34,7 @@
 
 #if defined(OSS) || defined (SGI) 
 
-#include <stropts.h>
+// #include <stropts.h>
 #include <poll.h>
 
 #ifndef SGI

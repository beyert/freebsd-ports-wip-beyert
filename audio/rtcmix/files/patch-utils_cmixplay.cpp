--- utils/cmixplay.cpp.orig	2022-06-20 19:29:55 UTC
+++ utils/cmixplay.cpp
@@ -8,7 +8,7 @@
    rev'd again, for OSX support  -JGG, 12/01.
    rev'd again, to work with Doug's AudioDevice class  -JGG, 6/04.
 */
-#if defined(LINUX) || defined(MACOSX)
+#if defined(LINUX) || defined(FREEBSD) || defined(MACOSX)
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -32,7 +32,7 @@
 #ifdef LINUX
    #include <values.h>
 #endif
-#ifdef MACOSX
+#if defined(FREEBSD) || defined(MACOSX)
    #include <limits.h>
 #endif
 
@@ -1175,4 +1175,4 @@ main(int argc, char *argv[])
    return EXIT_SUCCESS;
 }
 
-#endif /* #if defined(LINUX) || defined(MACOSX) */
+#endif /* #if defined(LINUX) || defined(FREEBSD) || defined(MACOSX) */

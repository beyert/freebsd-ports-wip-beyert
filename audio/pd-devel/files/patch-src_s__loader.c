--- src/s_loader.c.orig	2022-03-28 05:20:02 UTC
+++ src/s_loader.c
@@ -37,7 +37,7 @@ objects.  The specific name is the letter b, l, d, or 
 darwin, or microsoft, followed by a more specific string, either "fat" for
 a fat binary or an indication of the instruction set. */
 
-#if defined(__x86_64__) || defined(_M_X64)
+#if defined(__amd64__) || defined(_M_X64)
 # define ARCHEXT "amd64"
 #elif defined(__i386__) || defined(_M_IX86)
 # define ARCHEXT "i386"
@@ -57,9 +57,9 @@ a fat binary or an indication of the instruction set. 
 
 
 static const char*sys_dllextent[] = {
-#if defined(__linux__) || defined(__FreeBSD_kernel__) || defined(__GNU__) || defined(__FreeBSD__)
+#if defined(__linux__) || defined(__GNU__)
     ARCHDLLEXT(".l_")
-#if defined(__x86_64__) || defined(_M_X64)
+#if defined(__amd64__) || defined(_M_X64)
     ".l_ia64",      /* incorrect but probably in wide use */
 #endif
     ".pd_linux",
@@ -68,6 +68,10 @@ static const char*sys_dllextent[] = {
     ".d_fat",
     ARCHDLLEXT(".d_")
     ".pd_darwin",
+    ".so",
+#elif defined(__FreeBSD__)
+    ARCHDLLEXT(".f_")
+    ".pd_freebsd",
     ".so",
 #elif defined(__OPENBSD__)
     ARCHDLLEXT(".o_")

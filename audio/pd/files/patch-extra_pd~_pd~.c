--- extra/pd~/pd~.c.orig	2022-03-23 23:28:43 UTC
+++ extra/pd~/pd~.c
@@ -24,6 +24,7 @@ typedef int socklen_t;
 #include <stdlib.h>
 #include <errno.h>
 #include <ctype.h>
+#include <signal.h>
 #include <sys/wait.h>
 #include <fcntl.h>
 #include <signal.h>
@@ -84,6 +85,8 @@ static t_class *pd_tilde_class;
 
 #if defined(__x86_64__) || defined(_M_X64)
 # define ARCHEXT "amd64"
+#elif defined(__amd64__) || defined(_M_X64)
+# define ARCHEXT "amd64"
 #elif defined(__i386__) || defined(_M_IX86)
 # define ARCHEXT "i386"
 #elif defined(__arm__)
@@ -102,8 +105,7 @@ static t_class *pd_tilde_class;
 
 
 static const char *pd_tilde_dllextent[] = {
-#if defined(__linux__) || defined(__FreeBSD_kernel__) || defined(__GNU__) || \
-    defined(__FreeBSD__)
+#if defined(__linux__) || defined(__GNU__)
     ARCHDLLEXT(".l_")
     ".pd_linux",
     ".so",
@@ -115,6 +117,10 @@ static const char *pd_tilde_dllextent[] = {
 #elif defined(__OPENBSD__)
     ARCHDLLEXT(".o_")
     ".pd_openbsd",
+    ".so",
+#elif defined(__FreeBSD__)
+    ARCHDLLEXT(".o_")
+    ".pd_freebsd",
     ".so",
 #elif defined(_WIN32) || defined(__CYGWIN__)
     ARCHDLLEXT(".m_")

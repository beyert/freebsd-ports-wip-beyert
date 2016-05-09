--- stest.c.orig	2015-02-10 20:52:44 UTC
+++ stest.c
@@ -8,6 +8,7 @@
 #include <sys/stat.h>
 
 #define FLAG(x)  (flag[(x)-'a'])
+#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */
 
 static void test(const char *, const char *);
 

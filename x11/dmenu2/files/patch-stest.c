--- stest.c.orig	2013-11-26 00:15:04.000000000 -0800
+++ stest.c	2016-05-08 22:52:14.277094000 -0700
@@ -8,6 +8,7 @@
 #include <sys/stat.h>
 
 #define FLAG(x)  (flag[(x)-'a'])
+#define	S_ISLNK(m)	(((m) & 0170000) == 0120000)	/* symbolic link */
 
 static void test(const char *, const char *);
 

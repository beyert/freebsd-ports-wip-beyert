--- src/event-Xt.c.orig	2007-08-20 12:52:27.000000000 -0700
+++ src/event-Xt.c	2014-09-04 12:54:12.000000000 -0700
@@ -564,7 +564,7 @@
   /* If there was no Meta key, then try using the Alt key instead.
      If there is both a Meta key and an Alt key, then the Alt key
      is not disturbed and remains an Alt key. */
-  if (! meta_bit && alt_bit)
+  if (! meta_bit)
     meta_bit = alt_bit, alt_bit = 0;
 
   /* mode_bit overrides everything, since it's processed down inside of

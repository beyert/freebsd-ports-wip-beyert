--- src/event-Xt.c.orig	2007-08-20 19:52:27 UTC
+++ src/event-Xt.c
@@ -564,7 +564,7 @@ x_reset_modifier_mapping (struct device *d)
   /* If there was no Meta key, then try using the Alt key instead.
      If there is both a Meta key and an Alt key, then the Alt key
      is not disturbed and remains an Alt key. */
-  if (! meta_bit && alt_bit)
+  if (! meta_bit)
     meta_bit = alt_bit, alt_bit = 0;
 
   /* mode_bit overrides everything, since it's processed down inside of

--- src/generate_events.c.orig	2014-05-20 06:05:31 UTC
+++ src/generate_events.c
@@ -147,7 +147,7 @@ void generate_relative_motion_event2(int xMove, int yM
 /* my own (first?) line algorithm, not as good as Bresenham's line algorithm,
    though.  Not very good. */
 void generate_relative_motion_event(int xpps, int ypps) {
-  int i = 0, x = 0, y = 0, delay = 0, xdelay, ydelay;
+  int i = 0, x = 0, y = 0, delay, xdelay, ydelay;
   int axpps = abs(xpps), aypps = abs(ypps);
   if (axpps < 1000) { x = make1(xpps); }
   else { x = xpps / 1000; }

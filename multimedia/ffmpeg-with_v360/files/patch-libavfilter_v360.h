--- libavfilter/v360.h.orig	2021-10-24 20:47:07 UTC
+++ libavfilter/v360.h
@@ -121,6 +121,7 @@ typedef struct V360Context {
     int in, out;
     int interp;
     int alpha;
+    int reset_rot;
     int width, height;
     char *in_forder;
     char *out_forder;

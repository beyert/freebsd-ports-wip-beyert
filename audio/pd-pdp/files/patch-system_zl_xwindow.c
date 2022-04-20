--- system/zl/xwindow.c.orig	2014-01-06 18:40:48 UTC
+++ system/zl/xwindow.c
@@ -328,8 +328,9 @@ void zl_xwindow_for_parsed_events(zl_xwindow_p xwin,
     }
 }
 
+void handle(void *x, XEvent *e) {}
+
 void zl_xwindow_drop_events(zl_xwindow_p x) {
-    void handle(void *x, XEvent *e) {}
     zl_xwindow_for_events(x, handle, NULL);
 }
 

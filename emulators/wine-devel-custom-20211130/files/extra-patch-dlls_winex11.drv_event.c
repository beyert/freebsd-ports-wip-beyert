--- dlls/winex11.drv/event.c.orig	2021-10-08 19:10:44 UTC
+++ dlls/winex11.drv/event.c
@@ -1102,7 +1102,7 @@ static BOOL X11DRV_ConfigureNotify( HWND hwnd, XEvent 
     if (!data->mapped || data->iconic) goto done;
     if (data->whole_window && !data->managed) goto done;
     /* ignore synthetic events on foreign windows */
-    if (event->send_event && !data->whole_window) goto done;
+    // if (event->send_event && !data->whole_window) goto done;
     if (data->configure_serial && (long)(data->configure_serial - event->serial) > 0)
     {
         TRACE( "win %p/%lx event %d,%d,%dx%d ignoring old serial %lu/%lu\n",

--- dlls/winex11.drv/window.c.orig	2021-10-08 19:10:44 UTC
+++ dlls/winex11.drv/window.c
@@ -1130,7 +1130,12 @@ static void map_window( HWND hwnd, DWORD new_style )
             if (data->surface && data->vis.visualid != default_visual.visualid)
                 data->surface->funcs->flush( data->surface );
         }
-        else set_xembed_flags( data, XEMBED_MAPPED );
+        // else set_xembed_flags( data, XEMBED_MAPPED );
+        else {
+            XMapWindow( data->display, data->whole_window );
+            XFlush( data->display );
+            set_xembed_flags( data, XEMBED_MAPPED );
+        }
 
         data->mapped = TRUE;
         data->iconic = (new_style & WS_MINIMIZE) != 0;

--- system/image/pdp_imageproc_portable.c.orig	2014-01-06 18:40:48 UTC
+++ system/image/pdp_imageproc_portable.c
@@ -570,6 +570,10 @@ void *pdp_imageproc_resample_affinemap_new(void)
     return (void *)a;
 }
 
+/* affine x, y mappings in screen coordinates */
+double mapx(double _x, double _y, double cx, double cy, double c, double s, double izx, double izy){return cx + izx * ( c * (_x-cx) + s * (_y-cy));}
+double mapy(double _x, double _y, double cx, double cy, double c, double s, double izx, double izy){return cy + izy * (-s * (_x-cx) + c * (_y-cy));}
+
 void pdp_imageproc_resample_affinemap_delete(void *x){pdp_dealloc(x);}
 void pdp_imageproc_resample_affinemap_setcenterx(void *x, float f){((t_affine_map *)x)->centerx = f;}
 void pdp_imageproc_resample_affinemap_setcentery(void *x, float f){((t_affine_map *)x)->centery = f;}
@@ -590,19 +594,15 @@ void pdp_imageproc_resample_affinemap_process(void *x,
     double c = cos(angle);
     double s = sin(angle);
 
-    /* affine x, y mappings in screen coordinates */
-    double mapx(double _x, double _y){return cx + izx * ( c * (_x-cx) + s * (_y-cy));}
-    double mapy(double _x, double _y){return cy + izy * (-s * (_x-cx) + c * (_y-cy));}
-
-    u32 colstate_x = (u32)(scalew * mapx(0,0));
-    u32 colstate_y = (u32)(scaleh * mapy(0,0));
+    u32 colstate_x = (u32)(scalew * mapx(0,0,cx,cy,c,s,izx,izy));
+    u32 colstate_y = (u32)(scaleh * mapy(0,0,cx,cy,c,s,izx,izy));
     u32 rowstate_x = colstate_x;
     u32 rowstate_y = colstate_y;
 
-    u32 row_inc_x = (u32)(scalew * (mapx(1,0)-mapx(0,0)));
-    u32 row_inc_y = (u32)(scaleh * (mapy(1,0)-mapy(0,0)));
-    u32 col_inc_x = (u32)(scalew * (mapx(0,1)-mapx(0,0)));
-    u32 col_inc_y = (u32)(scaleh * (mapy(0,1)-mapy(0,0)));
+    u32 row_inc_x = (u32)(scalew * (mapx(1,0,cx,cy,c,s,izx,izy)-mapx(0,0,cx,cy,c,s,izx,izy)));
+    u32 row_inc_y = (u32)(scaleh * (mapy(1,0,cx,cy,c,s,izx,izy)-mapy(0,0,cx,cy,c,s,izx,izy)));
+    u32 col_inc_x = (u32)(scalew * (mapx(0,1,cx,cy,c,s,izx,izy)-mapx(0,0,cx,cy,c,s,izx,izy)));
+    u32 col_inc_y = (u32)(scaleh * (mapy(0,1,cx,cy,c,s,izx,izy)-mapy(0,0,cx,cy,c,s,izx,izy)));
 
     u32 i,j;
 

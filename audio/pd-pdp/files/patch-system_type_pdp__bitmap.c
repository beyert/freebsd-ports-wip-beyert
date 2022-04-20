--- system/type/pdp_bitmap.c.orig	2014-01-06 18:40:48 UTC
+++ system/type/pdp_bitmap.c
@@ -509,6 +509,11 @@ static int _pdp_packet_bitmap_convert_yv12_to_image(in
     return new_p;
 }
 
+static inline u8 _map(s32 pixel){
+	s32 mask = ~(pixel>>16);
+	return ((pixel >> 7) & mask);
+}
+
 static int _pdp_packet_bitmap_convert_mchp_to_rgb8(int packet, t_pdp_symbol *dest_template)
 {
     t_pdp *header = pdp_packet_header(packet);
@@ -520,12 +525,6 @@ static int _pdp_packet_bitmap_convert_mchp_to_rgb8(int
     int plane = w*h;
     int nb_channels = image->depth;
     int new_p, i;
-
-    //    static inline u8 _map(s32 pixel){
-    inline u8 _map(s32 pixel){
-	s32 mask = ~(pixel>>16);
-	return ((pixel >> 7) & mask);
-    }
 
     switch(nb_channels){
     default: return -1;

--- tools/sfnt2fon/sfnt2fon.c.orig	2016-10-07 13:00:34.000000000 -0700
+++ tools/sfnt2fon/sfnt2fon.c	2020-08-07 08:40:53.000000000 -0700
@@ -41,8 +41,8 @@
 #include FT_TRUETYPE_TABLES_H
 #include FT_TRUETYPE_TAGS_H
 
-#define WINE_UNICODE_API /* nothing */
-#include "wine/unicode.h"
+#include "windef.h"
+#include "winbase.h"
 #include "wingdi.h"
 #include "basetsd.h"
 
@@ -341,15 +341,40 @@
     return OEM_CHARSET;
 }
 
-static int get_char(const union cptable *cptable, int enc, int index)
+#ifdef _WIN32
+
+static void get_char_table(int enc, WCHAR tableW[0x100])
 {
-    /* Korean has the Won sign in place of '\\' */
-    if(enc == 949 && index == '\\')
-        return 0x20a9;
+    int i;
+    char tableA[0x100];
 
-    return cptable->sbcs.cp2uni[index];
+    if (!GetCPInfo( enc, &info )) error("Can't find codepage %d\n", enc);
+    if (info.MaxCharSize > 1) enc = 1252;
+
+    for (i = 0; i < 0x100; i++) tableA[i] = i;
+    MultiByteToWideChar( enc, 0, tableA, 0x100, tableW, 0x100 );
 }
 
+#else  /* _WIN32 */
+
+#include "wine/unicode.h"
+
+static void get_char_table(int enc, WCHAR tableW[0x100])
+{
+    int i;
+    char tableA[0x100];
+    const union cptable *cptable = wine_cp_get_table(enc);
+
+    if (!cptable) error("Can't find codepage %d\n", enc);
+    /* for double byte charsets we actually want to use cp1252 */
+    if (cptable->info.char_size != 1) cptable = wine_cp_get_table(1252);
+
+    for (i = 0; i < 0x100; i++) tableA[i] = i;
+    wine_cp_mbstowcs( cptable, 0, tableA, 0x100, tableW, 0x100 );
+}
+
+#endif  /* _WIN32 */
+
 static struct fontinfo *fill_fontinfo( const char *face_name, int ppem, int enc, int dpi,
                                        unsigned char def_char, int avg_width )
 {
@@ -360,7 +385,6 @@
     int i, x, y, x_off, x_end, first_char;
     FT_UInt gi;
     int num_names;
-    const union cptable *cptable;
     FT_SfntName sfntname;
     TT_OS2 *os2;
     FT_ULong needed;
@@ -369,22 +393,17 @@
     int num_sizes;
     struct fontinfo *info;
     size_t data_pos;
+    WCHAR table[0x100];
 
     if (FT_New_Face(ft_library, face_name, 0, &face)) error( "Cannot open face %s\n", face_name );
     if (FT_Set_Pixel_Sizes(face, ppem, ppem)) error( "cannot set face size to %u\n", ppem );
 
-    cptable = wine_cp_get_table(enc);
-    if(!cptable)
-        error("Can't find codepage %d\n", enc);
+    assert( face->size->metrics.y_ppem == ppem );
 
-    if(cptable->info.char_size != 1) {
-        /* for double byte charsets we actually want to use cp1252 */
-        cptable = wine_cp_get_table(1252);
-        if(!cptable)
-            error("Can't find codepage 1252\n");
-    }
+    get_char_table( enc, table );
 
-    assert( face->size->metrics.y_ppem == ppem );
+    /* Korean has the Won sign in place of '\\' */
+    if (enc == 949) table['\\'] = 0x20a9;
 
     needed = 0;
     if (FT_Load_Sfnt_Table(face, TTAG_EBLC, 0, NULL, &needed))
@@ -440,9 +459,9 @@
         el = 0;
 
     first_char = FT_Get_First_Char(face, &gi);
-    if(first_char == 0xd) /* fontforge's first glyph is 0xd, we'll catch this and skip it */
-        first_char = 32; /* FT_Get_Next_Char for some reason returns too high
-                            number in this case */
+    if(first_char < 0x20)  /* Ignore glyphs below 0x20 */
+        first_char = 0x20; /* FT_Get_Next_Char for some reason returns too high
+                              number in this case */
 
     info = calloc( 1, sizeof(*info) );
 
@@ -463,12 +482,11 @@
 
     os2 = FT_Get_Sfnt_Table(face, ft_sfnt_os2);
     for(i = first_char; i < 0x100; i++) {
-        int c = get_char(cptable, enc, i);
-        gi = FT_Get_Char_Index(face, c);
+        gi = FT_Get_Char_Index(face, table[i]);
         if(gi == 0 && !option_quiet)
             fprintf(stderr, "warning: %s %u: missing glyph for char %04x\n",
-                    face->family_name, ppem, cptable->sbcs.cp2uni[i]);
-        if(FT_Load_Char(face, c, FT_LOAD_DEFAULT)) {
+                    face->family_name, ppem, table[i]);
+        if(FT_Load_Char(face, table[i], FT_LOAD_DEFAULT)) {
             fprintf(stderr, "error loading char %d - bad news!\n", i);
             continue;
         }
@@ -547,8 +565,7 @@
     data_pos = 0;
 
     for(i = first_char; i < 0x100; i++) {
-        int c = get_char(cptable, enc, i);
-        if(FT_Load_Char(face, c, FT_LOAD_DEFAULT)) {
+        if(FT_Load_Char(face, table[i], FT_LOAD_DEFAULT)) {
             continue;
         }
         assert(info->dfCharTable[i].width == face->glyph->metrics.horiAdvance >> 6);

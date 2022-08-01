--- src/parser/parse_with_minc.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/parser/parse_with_minc.cpp
@@ -13,8 +13,12 @@
 #include <Option.h>
 
 typedef struct yy_buffer_state * YY_BUFFER_STATE;
-#if BISON_VERSION >= 3 || !defined(MACOSX)
+#if BISON_VERSION >= 3 || !(defined(MACOSX) || defined(FREEBSD))
+#ifdef FLEX_GT_2_6_0
 extern YY_BUFFER_STATE yy_scan_bytes(const char * buf, int len);
+#else
+extern YY_BUFFER_STATE yy_scan_bytes(const char * buf, size_t len);
+#endif
 #else
 extern YY_BUFFER_STATE yy_scan_bytes(const char * buf, size_t len);
 #endif

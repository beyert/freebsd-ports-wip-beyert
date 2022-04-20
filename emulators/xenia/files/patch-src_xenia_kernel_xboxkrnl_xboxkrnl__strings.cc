--- src/xenia/kernel/xboxkrnl/xboxkrnl_strings.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/kernel/xboxkrnl/xboxkrnl_strings.cc
@@ -117,8 +117,8 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
                     const bool wide) {
   int32_t count = 0;
 
-  char work8[512];
-  char16_t work16[4];
+  char work[512];
+  wchar_t wwork[4];
 
   struct {
     const void* buffer;
@@ -339,13 +339,13 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
             auto value = args.get32();
 
             if (!is_wide) {
-              work8[0] = (uint8_t)value;
-              text.buffer = &work8[0];
+              work[0] = (uint8_t)value;
+              text.buffer = &work[0];
               text.length = 1;
               text.is_wide = false;
             } else {
-              work16[0] = (uint16_t)value;
-              text.buffer = &work16[0];
+              wwork[0] = (uint16_t)value;
+              text.buffer = &wwork[0];
               text.length = 1;
               text.is_wide = true;
               text.swap_wide = false;
@@ -378,7 +378,7 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
             }
 
             if (precision >= 0) {
-              precision = std::min(precision, (int32_t)xe::countof(work8));
+              precision = std::min(precision, (int32_t)xe::countof(work));
             } else {
               precision = 1;
             }
@@ -396,7 +396,7 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
               prefix.length = 0;
             }
 
-            char* end = &work8[xe::countof(work8) - 1];
+            char* end = &work[xe::countof(work) - 1];
             char* start = end;
             start[0] = '\0';
 
@@ -471,9 +471,9 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
 
             auto s = format_double(value, precision, c, flags);
             auto length = (int32_t)s.size();
-            assert_true(length < xe::countof(work8));
+            assert_true(length < xe::countof(work));
 
-            auto start = &work8[0];
+            auto start = &work[0];
             auto end = &start[length];
 
             std::memcpy(start, s.c_str(), length);
@@ -637,7 +637,7 @@ int32_t format_core(PPCContext* ppc_context, FormatDat
         }
       }
     } else {
-      // it's a const char16_t*
+      // it's a const wchar_t*
       auto b = (const uint16_t*)text.buffer;
       if (text.swap_wide) {
         while (remaining-- > 0) {
@@ -768,15 +768,15 @@ class WideStringFormatData : public FormatData {
   }
 
   bool put(uint16_t c) {
-    output_ << (char16_t)c;
+    output_ << (wchar_t)c;
     return true;
   }
 
-  std::u16string wstr() const { return output_.str(); }
+  std::wstring wstr() const { return output_.str(); }
 
  private:
   const uint16_t* input_;
-  std::basic_stringstream<char16_t> output_;
+  std::wostringstream output_;
 };
 
 class WideCountFormatData : public FormatData {
@@ -830,7 +830,7 @@ SHIM_CALL DbgPrint_shim(PPCContext* ppc_context, Kerne
     return;
   }
 
-  XELOGD("(DbgPrint) {}", data.str());
+  XELOGD("(DbgPrint) %s", data.str().c_str());
 
   SHIM_SET_RETURN_32(X_STATUS_SUCCESS);
 }
@@ -841,7 +841,7 @@ SHIM_CALL _snprintf_shim(PPCContext* ppc_context, Kern
   int32_t buffer_count = SHIM_GET_ARG_32(1);
   uint32_t format_ptr = SHIM_GET_ARG_32(2);
 
-  XELOGD("_snprintf({:08X}, {}, {:08X}, ...)", buffer_ptr, buffer_count,
+  XELOGD("_snprintf(%08X, %i, %08X, ...)", buffer_ptr, buffer_count,
          format_ptr);
 
   if (buffer_ptr == 0 || buffer_count <= 0 || format_ptr == 0) {
@@ -877,7 +877,7 @@ SHIM_CALL sprintf_shim(PPCContext* ppc_context, Kernel
   uint32_t buffer_ptr = SHIM_GET_ARG_32(0);
   uint32_t format_ptr = SHIM_GET_ARG_32(1);
 
-  XELOGD("sprintf({:08X}, {:08X}, ...)", buffer_ptr, format_ptr);
+  XELOGD("sprintf(%08X, %08X, ...)", buffer_ptr, format_ptr);
 
   if (buffer_ptr == 0 || format_ptr == 0) {
     SHIM_SET_RETURN_32(-1);
@@ -906,7 +906,7 @@ SHIM_CALL _snwprintf_shim(PPCContext* ppc_context, Ker
   int32_t buffer_count = SHIM_GET_ARG_32(1);
   uint32_t format_ptr = SHIM_GET_ARG_32(2);
 
-  XELOGD("_snwprintf({:08X}, {}, {:08X}, ...)", buffer_ptr, buffer_count,
+  XELOGD("_snwprintf(%08X, %i, %08X, ...)", buffer_ptr, buffer_count,
          format_ptr);
 
   if (buffer_ptr == 0 || buffer_count <= 0 || format_ptr == 0) {
@@ -942,7 +942,7 @@ SHIM_CALL swprintf_shim(PPCContext* ppc_context, Kerne
   uint32_t buffer_ptr = SHIM_GET_ARG_32(0);
   uint32_t format_ptr = SHIM_GET_ARG_32(1);
 
-  XELOGD("swprintf({:08X}, {:08X}, ...)", buffer_ptr, format_ptr);
+  XELOGD("swprintf(%08X, %08X, ...)", buffer_ptr, format_ptr);
 
   if (buffer_ptr == 0 || format_ptr == 0) {
     SHIM_SET_RETURN_32(-1);
@@ -972,7 +972,7 @@ SHIM_CALL _vsnprintf_shim(PPCContext* ppc_context, Ker
   uint32_t format_ptr = SHIM_GET_ARG_32(2);
   uint32_t arg_ptr = SHIM_GET_ARG_32(3);
 
-  XELOGD("_vsnprintf({:08X}, {}, {:08X}, {:08X})", buffer_ptr, buffer_count,
+  XELOGD("_vsnprintf(%08X, %i, %08X, %08X)", buffer_ptr, buffer_count,
          format_ptr, arg_ptr);
 
   if (buffer_ptr == 0 || buffer_count <= 0 || format_ptr == 0) {
@@ -1012,7 +1012,7 @@ SHIM_CALL _vsnwprintf_shim(PPCContext* ppc_context, Ke
   uint32_t format_ptr = SHIM_GET_ARG_32(2);
   uint32_t arg_ptr = SHIM_GET_ARG_32(3);
 
-  XELOGD("_vsnwprintf({:08X}, {}, {:08X}, {:08X})", buffer_ptr, buffer_count,
+  XELOGD("_vsnwprintf(%08X, %i, %08X, %08X)", buffer_ptr, buffer_count,
          format_ptr, arg_ptr);
 
   if (buffer_ptr == 0 || buffer_count <= 0 || format_ptr == 0) {
@@ -1051,7 +1051,7 @@ SHIM_CALL vsprintf_shim(PPCContext* ppc_context, Kerne
   uint32_t format_ptr = SHIM_GET_ARG_32(1);
   uint32_t arg_ptr = SHIM_GET_ARG_32(2);
 
-  XELOGD("vsprintf({:08X}, {:08X}, {:08X})", buffer_ptr, format_ptr, arg_ptr);
+  XELOGD("vsprintf(%08X, %08X, %08X)", buffer_ptr, format_ptr, arg_ptr);
 
   if (buffer_ptr == 0 || format_ptr == 0) {
     SHIM_SET_RETURN_32(-1);
@@ -1079,7 +1079,7 @@ SHIM_CALL _vscwprintf_shim(PPCContext* ppc_context, Ke
   uint32_t format_ptr = SHIM_GET_ARG_32(0);
   uint32_t arg_ptr = SHIM_GET_ARG_32(1);
 
-  XELOGD("_vscwprintf({:08X}, {:08X})", format_ptr, arg_ptr);
+  XELOGD("_vscwprintf(%08X, %08X)", format_ptr, arg_ptr);
 
   if (format_ptr == 0) {
     SHIM_SET_RETURN_32(-1);
@@ -1102,7 +1102,7 @@ SHIM_CALL vswprintf_shim(PPCContext* ppc_context, Kern
   uint32_t format_ptr = SHIM_GET_ARG_32(1);
   uint32_t arg_ptr = SHIM_GET_ARG_32(2);
 
-  XELOGD("vswprintf({:08X}, {:08X}, {:08X})", buffer_ptr, format_ptr, arg_ptr);
+  XELOGD("vswprintf(%08X, %08X, %08X)", buffer_ptr, format_ptr, arg_ptr);
 
   if (buffer_ptr == 0 || format_ptr == 0) {
     SHIM_SET_RETURN_32(-1);

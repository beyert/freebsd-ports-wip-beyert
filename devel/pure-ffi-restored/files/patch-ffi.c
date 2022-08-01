--- ffi.c.orig	2014-03-11 21:15:31 UTC
+++ ffi.c
@@ -3,6 +3,7 @@
 #include <stdlib.h>
 #include <string.h>
 #include <ffi.h>
+#include <ffitarget.h>
 #include <pure/runtime.h>
 
 #if FFI_TYPE_LONGDOUBLE != FFI_TYPE_DOUBLE
@@ -31,8 +32,10 @@ void ffi_defs(void)
   pure_def(pure_sym("FFI_SYSV"), pure_int(FFI_SYSV));
   pure_def(pure_sym("FFI_STDCALL"), pure_int(FFI_STDCALL));
 #else
-#if defined(__i386__) || defined(__x86_64__)
+#if defined(__i386__)
   pure_def(pure_sym("FFI_SYSV"), pure_int(FFI_SYSV));
+#endif
+#if defined(__x86_64__)
   pure_def(pure_sym("FFI_UNIX64"), pure_int(FFI_UNIX64));
 #endif
 #endif

--- src/xenia/kernel/xsocket.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/kernel/xsocket.cc
@@ -44,9 +44,9 @@ X_STATUS XSocket::Initialize(AddressFamily af, Type ty
   type_ = type;
   proto_ = proto;
 
-  if (proto == Protocol::IPPROTO_VDP) {
+  if (proto == Protocol::IPPROTO_VDP_CXX) {
     // VDP is a layer on top of UDP.
-    proto = Protocol::IPPROTO_UDP;
+    proto = Protocol::IPPROTO_UDP_CXX;
   }
 
   native_handle_ = socket(af, type, proto);
@@ -60,7 +60,7 @@ X_STATUS XSocket::Initialize(AddressFamily af, Type ty
 X_STATUS XSocket::Close() {
 #if XE_PLATFORM_WIN32
   int ret = closesocket(native_handle_);
-#elif XE_PLATFORM_LINUX
+#elif XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
   int ret = close(native_handle_);
 #endif
 
@@ -103,7 +103,7 @@ X_STATUS XSocket::IOControl(uint32_t cmd, uint8_t* arg
   }
 
   return X_STATUS_SUCCESS;
-#elif XE_PLATFORM_LINUX
+#elif XE_PLATFORM_LINUX || XE_PLATFORM_FREEBSD
   return X_STATUS_UNSUCCESSFUL;
 #endif
 }
@@ -256,4 +256,4 @@ bool XSocket::QueuePacket(uint32_t src_ip, uint16_t sr
 }
 
 }  // namespace kernel
-}  // namespace xe
\ No newline at end of file
+}  // namespace xe

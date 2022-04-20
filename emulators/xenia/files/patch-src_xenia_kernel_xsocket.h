--- src/xenia/kernel/xsocket.h.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/kernel/xsocket.h
@@ -78,13 +78,13 @@ class XSocket : public XObject {
   };
 
   enum Protocol {
-    IPPROTO_TCP = 6,
-    IPPROTO_UDP = 17,
+    IPPROTO_TCP_CXX = 6,
+    IPPROTO_UDP_CXX = 17,
 
     // LIVE Voice and Data Protocol
     // https://blog.csdn.net/baozi3026/article/details/4277227
     // Format: [cbGameData][GameData(encrypted)][VoiceData(unencrypted)]
-    IPPROTO_VDP = 254,
+    IPPROTO_VDP_CXX = 254,
   };
 
   XSocket(KernelState* kernel_state);
@@ -149,4 +149,4 @@ class XSocket : public XObject {
 }  // namespace kernel
 }  // namespace xe
 
-#endif  // XENIA_KERNEL_XSOCKET_H_
\ No newline at end of file
+#endif  // XENIA_KERNEL_XSOCKET_H_

--- src/SndPVOCEX.h.orig	2011-06-03 13:17:13 UTC
+++ src/SndPVOCEX.h
@@ -67,7 +67,7 @@ struct WAVEFORMATPVOCEX {
 };
 
 const GUID KSDATAFORMAT_SUBTYPE_PVOC = {
-  0x8312b9c2,
+  (int)0x8312b9c2,
   0x2e6e,
   0x11d4,
   { 0xa8, 0x24, 0xde, 0x5b, 0x96, 0xc3, 0xab, 0x21 }

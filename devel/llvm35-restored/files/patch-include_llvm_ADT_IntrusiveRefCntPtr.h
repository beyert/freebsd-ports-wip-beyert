------------------------------------------------------------------------
r218295 | akirtzidis | 2014-09-23 08:06:43 +0200 (Tue, 23 Sep 2014) | 2 lines

[ADT/IntrusiveRefCntPtr] Give friend access to IntrusiveRefCntPtr<X> so the relevant move constructor can access 'Obj'.

------------------------------------------------------------------------
Index: include/llvm/ADT/IntrusiveRefCntPtr.h
===================================================================
--- include/llvm/ADT/IntrusiveRefCntPtr.h.orig	2014-07-05 22:20:59 UTC
+++ include/llvm/ADT/IntrusiveRefCntPtr.h
@@ -197,6 +197,9 @@ class ThreadSafeRefCountedBase { (public)
   private:
     void retain() { if (Obj) IntrusiveRefCntPtrInfo<T>::retain(Obj); }
     void release() { if (Obj) IntrusiveRefCntPtrInfo<T>::release(Obj); }
+
+    template <typename X>
+    friend class IntrusiveRefCntPtr;
   };
 
   template<class T, class U>

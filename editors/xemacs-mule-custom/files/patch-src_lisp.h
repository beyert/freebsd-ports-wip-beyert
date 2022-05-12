--- src/lisp.h.orig	2005-02-01 03:55:02 UTC
+++ src/lisp.h
@@ -195,6 +195,7 @@ void xfree (void *);
 
 /* No type has a greater alignment requirement than max_align_t.
    (except perhaps for types we don't use, like long double) */
+/*
 typedef union
 {
   struct { long l; } l;
@@ -202,6 +203,7 @@ typedef union
   struct { void (*f)(void); } f;
   struct { double d; } d;
 } max_align_t;
+*/
 
 #ifndef ALIGNOF
 # if defined (__GNUC__) && (__GNUC__ >= 2)

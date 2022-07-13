--- m_pd.h.orig	2021-09-10 22:38:47 UTC
+++ m_pd.h
@@ -723,7 +723,7 @@ defined, there is a "te_xpix" field in objects, not a 
 #define PD_USE_TE_XPIX
 
 #ifndef _MSC_VER /* Microoft compiler can't handle "inline" function/macros */
-#if defined(__i386__) || defined(__x86_64__) || defined(__arm__)
+#if defined(__i386__) || defined(__x86_64__) || defined(__amd64__) || defined(__arm__)
 /* a test for NANs and denormals.  Should only be necessary on i386. */
 #if PD_FLOATSIZE == 32
 

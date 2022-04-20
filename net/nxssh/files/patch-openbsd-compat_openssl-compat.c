--- openbsd-compat/openssl-compat.c.orig	2018-11-25 15:34:22 UTC
+++ openbsd-compat/openssl-compat.c
@@ -70,12 +70,19 @@ ssh_compatible_openssl(long headerver, long libver)
 void
 ssh_OpenSSL_add_all_algorithms(void)
 {
+#if OPENSSL_VERSION_NUMBER < 0x10100000L
 	OpenSSL_add_all_algorithms();
 
 	/* Enable use of crypto hardware */
 	ENGINE_load_builtin_engines();
+#if OPENSSL_VERSION_NUMBER < 0x10001000L
 	ENGINE_register_all_complete();
+#endif
 	OPENSSL_config(NULL);
+#else
+	OPENSSL_init_crypto(OPENSSL_INIT_ADD_ALL_DIGESTS |
+	    OPENSSL_INIT_ADD_ALL_DIGESTS | OPENSSL_INIT_LOAD_CONFIG, NULL);
+#endif
 }
 #endif
 

--- rsa.h.orig	2018-11-25 15:34:22 UTC
+++ rsa.h
@@ -21,6 +21,6 @@
 
 int	 rsa_public_encrypt(BIGNUM *, BIGNUM *, RSA *);
 int	 rsa_private_decrypt(BIGNUM *, BIGNUM *, RSA *);
-int	 rsa_generate_additional_parameters(RSA *);
+int	 rsa_generate_additional_parameters(RSA *, BIGNUM *);
 
 #endif				/* RSA_H */

--- ssh-pkcs11-client.c.orig	2018-11-25 15:34:22 UTC
+++ ssh-pkcs11-client.c
@@ -143,12 +143,14 @@ pkcs11_rsa_private_encrypt(int flen, const u_char *fro
 static int
 wrap_key(RSA *rsa)
 {
-	static RSA_METHOD helper_rsa;
+	static RSA_METHOD *helper_rsa;
 
-	memcpy(&helper_rsa, RSA_get_default_method(), sizeof(helper_rsa));
-	helper_rsa.name = "ssh-pkcs11-helper";
-	helper_rsa.rsa_priv_enc = pkcs11_rsa_private_encrypt;
-	RSA_set_method(rsa, &helper_rsa);
+	if (helper_rsa == NULL) {
+		helper_rsa = RSA_meth_dup(RSA_get_default_method());
+		RSA_meth_set1_name(helper_rsa, "ssh-pkcs11-helper");
+		RSA_meth_set_priv_enc(helper_rsa, pkcs11_rsa_private_encrypt);
+	}
+	RSA_set_method(rsa, helper_rsa);
 	return (0);
 }
 

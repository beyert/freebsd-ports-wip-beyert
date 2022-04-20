--- dh.h.orig	2018-11-25 15:34:22 UTC
+++ dh.h
@@ -42,7 +42,7 @@ DH	*dh_new_group18(void);
 DH	*dh_new_group_fallback(int);
 
 int	 dh_gen_key(DH *, int);
-int	 dh_pub_is_valid(DH *, BIGNUM *);
+int	 dh_pub_is_valid(const DH *, const BIGNUM *);
 
 u_int	 dh_estimate(int);
 

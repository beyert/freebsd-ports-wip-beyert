--- auth-pam.c.orig	2018-11-25 15:34:22 UTC
+++ auth-pam.c
@@ -129,6 +129,10 @@ extern u_int utmp_len;
 typedef pthread_t sp_pthread_t;
 #else
 typedef pid_t sp_pthread_t;
+# define pthread_create(a, b, c, d)	_ssh_compat_pthread_create(a, b, c, d)
+# define pthread_exit(a)		_ssh_compat_pthread_exit(a)
+# define pthread_cancel(a)		_ssh_compat_pthread_cancel(a)
+# define pthread_join(a, b)		_ssh_compat_pthread_join(a, b)
 #endif
 
 struct pam_ctxt {

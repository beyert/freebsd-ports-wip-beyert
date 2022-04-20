--- sshconnect.c.orig	2018-11-25 15:34:22 UTC
+++ sshconnect.c
@@ -1752,6 +1752,7 @@ ssh_login(Sensitive *sensitive, const char *orighost,
 	char *server_user, *local_user;
 
 	local_user = xstrdup(pw->pw_name);
+	free(pw);
 	server_user = options.user ? options.user : local_user;
 
 	/* Convert the user-supplied hostname into all lowercase. */

--- sshconnect2.c.orig	2018-11-25 15:34:22 UTC
+++ sshconnect2.c
@@ -257,6 +257,7 @@ ssh_kex2(char *host, struct sockaddr *hostaddr, u_shor
 	packet_send();
 	packet_write_wait();
 #endif
+	/* XXX free myproposal ?? */
 }
 
 /*

--- dlls/wineoss.drv/midi.c.orig	2016-10-07 13:00:34.000000000 -0700
+++ dlls/wineoss.drv/midi.c	2014-01-10 12:37:29.000000000 -0800
@@ -542,7 +542,7 @@
 
     if (MidiInDev[wDevID].state & 2) { /* system exclusive */
 	LPMIDIHDR	lpMidiHdr;
-        BOOL            sbfb = FALSE;
+	WORD 		sbfb = FALSE;
 
 	EnterCriticalSection(&crit_sect);
 	if ((lpMidiHdr = MidiInDev[wDevID].lpQueueHdr) != NULL) {
@@ -642,7 +642,7 @@
     TRACE("Thread startup\n");
 
     pfd.fd = midiSeqFD;
-    pfd.events = POLLIN;
+    pfd.fd = POLLIN;
     
     while(!end_thread) {
 	TRACE("Thread loop\n");

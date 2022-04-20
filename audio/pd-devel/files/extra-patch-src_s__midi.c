--- src/s_midi.c.orig	2022-03-29 08:12:49 UTC
+++ src/s_midi.c
@@ -515,7 +515,7 @@ void sys_pollmidiqueue(void)
 void midi_alsa_init(void);
 #endif
 #ifdef USEAPI_OSS
-void midi_oss_init(void);
+/* void midi_oss_init(void); */
 #endif
 
     /* last requested parameters */
@@ -594,7 +594,7 @@ void sys_open_midi(int nmidiindev, int *midiindev,
         midi_alsa_init();
 #endif
 #ifdef USEAPI_OSS
-        midi_oss_init();
+/*        midi_oss_init(); */
 #endif
 #ifdef USEAPI_ALSA
         if (sys_midiapi == API_ALSA)

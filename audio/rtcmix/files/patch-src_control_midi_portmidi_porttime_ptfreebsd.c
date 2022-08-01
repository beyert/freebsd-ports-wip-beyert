--- src/control/midi/portmidi/porttime/ptfreebsd.c.orig	2022-03-28 23:24:30 UTC
+++ src/control/midi/portmidi/porttime/ptfreebsd.c
@@ -0,0 +1,124 @@
+/* ptfreebsd.c -- portable timer implementation for freebsd */
+
+
+/*
+
+CHANGE LOG
+
+18-Jul-03 Roger Dannenberg -- Simplified code to set priority of timer
+            thread. Simplified implementation notes. 
+
+*/
+/* stdlib, stdio, unistd, and sys/types were added because they appeared
+ * in a Gentoo patch, but I'm not sure why they are needed. -RBD
+ */
+#include <stdlib.h>
+#include <stdio.h>
+#include <unistd.h>
+#include <sys/types.h>
+#include "porttime.h"
+#include "time.h"
+#include "sys/resource.h"
+#include "sys/timeb.h"
+#include "pthread.h"
+
+#define TRUE 1
+#define FALSE 0
+
+static int time_started_flag = FALSE;
+static struct timespec time_offset = {0, 0};
+static pthread_t pt_thread_pid;
+static int pt_thread_created = FALSE;
+
+/* note that this is static data -- we only need one copy */
+typedef struct {
+    int id;
+    int resolution;
+    PtCallback *callback;
+    void *userData;
+} pt_callback_parameters;
+
+static int pt_callback_proc_id = 0;
+
+static void *Pt_CallbackProc(void *p)
+{
+    pt_callback_parameters *parameters = (pt_callback_parameters *) p;
+    int mytime = 1;
+    /* to kill a process, just increment the pt_callback_proc_id */
+    /* printf("pt_callback_proc_id %d, id %d\n", pt_callback_proc_id,
+           parameters->id); */
+    if (geteuid() == 0) setpriority(PRIO_PROCESS, 0, -20);
+    while (pt_callback_proc_id == parameters->id) {
+        /* wait for a multiple of resolution ms */
+        struct timeval timeout;
+        int delay = mytime++ * parameters->resolution - Pt_Time();
+        if (delay < 0) delay = 0;
+        timeout.tv_sec = 0;
+        timeout.tv_usec = delay * 1000;
+        select(0, NULL, NULL, NULL, &timeout);
+        (*(parameters->callback))(Pt_Time(), parameters->userData);
+    }
+    /* printf("Pt_CallbackProc exiting\n"); */
+    // free(parameters);
+    return NULL;
+}
+
+
+PtError Pt_Start(int resolution, PtCallback *callback, void *userData)
+{
+    if (time_started_flag) return ptNoError;
+    /* need this set before process runs: */
+    clock_gettime(CLOCK_MONOTONIC, &time_offset);
+    if (callback) {
+        int res;
+        pt_callback_parameters *parms = (pt_callback_parameters *) 
+            malloc(sizeof(pt_callback_parameters));
+        if (!parms) return ptInsufficientMemory;
+        parms->id = pt_callback_proc_id;
+        parms->resolution = resolution;
+        parms->callback = callback;
+        parms->userData = userData;
+        res = pthread_create(&pt_thread_pid, NULL, 
+                             Pt_CallbackProc, parms);
+        if (res != 0) return ptHostError;
+        pt_thread_created = TRUE;
+    }
+    time_started_flag = TRUE;
+    return ptNoError;
+}
+
+
+PtError Pt_Stop()
+{
+    /* printf("Pt_Stop called\n"); */
+    pt_callback_proc_id++;
+    if (pt_thread_created) {
+        pthread_join(pt_thread_pid, NULL);
+        pt_thread_created = FALSE;
+    }
+    time_started_flag = FALSE;
+    return ptNoError;
+}
+
+
+int Pt_Started()
+{
+    return time_started_flag;
+}
+
+
+PtTimestamp Pt_Time()
+{
+    long seconds, ms;
+    struct timespec now;
+    clock_gettime(CLOCK_MONOTONIC, &now);
+    seconds = now.tv_sec - time_offset.tv_sec;
+    ms = (now.tv_nsec - time_offset.tv_nsec) / 1000000; /* round down */
+    return seconds * 1000 + ms;
+}
+
+
+void Pt_Sleep(int32_t duration)
+{
+    usleep(duration * 1000);
+}

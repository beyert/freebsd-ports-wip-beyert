--- dlls/wineoss.drv/mmdevdrv.c.orig	2016-10-07 13:00:34.000000000 -0700
+++ dlls/wineoss.drv/mmdevdrv.c	2014-01-10 12:37:29.000000000 -0800
@@ -16,6 +16,7 @@
  * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
  */
 
+#define NONAMELESSUNION
 #define COBJMACROS
 #include "config.h"
 
@@ -56,8 +57,8 @@
 
 #define NULL_PTR_ERR MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, RPC_X_NULL_REF_POINTER)
 
-static const REFERENCE_TIME DefaultPeriod = 100000;
-static const REFERENCE_TIME MinimumPeriod = 50000;
+static const REFERENCE_TIME DefaultPeriod = 200000;
+static const REFERENCE_TIME MinimumPeriod = 100000;
 
 struct ACImpl;
 typedef struct ACImpl ACImpl;
@@ -100,7 +101,6 @@
     LONG ref;
 
     IMMDevice *parent;
-    IUnknown *pUnkFTMarshal;
 
     WAVEFORMATEX *fmt;
 
@@ -116,7 +116,7 @@
 
     BOOL initted, playing;
     UINT64 written_frames, last_pos_frames;
-    UINT32 period_us, period_frames, bufsize_frames, held_frames, tmp_buffer_frames, in_oss_frames;
+    UINT32 period_us, period_frames, bufsize_frames, held_frames, tmp_buffer_frames;
     UINT32 oss_bufsize_bytes, lcl_offs_frames; /* offs into local_buffer where valid data starts */
 
     BYTE *local_buffer, *tmp_buffer;
@@ -149,6 +149,9 @@
 
 static struct list g_devices = LIST_INIT(g_devices);
 
+static const WCHAR drv_keyW[] = {'S','o','f','t','w','a','r','e','\\',
+    'W','i','n','e','\\','D','r','i','v','e','r','s','\\',
+    'w','i','n','e','o','s','s','.','d','r','v',0};
 static const WCHAR drv_key_devicesW[] = {'S','o','f','t','w','a','r','e','\\',
     'W','i','n','e','\\','D','r','i','v','e','r','s','\\',
     'w','i','n','e','o','s','s','.','d','r','v','\\','d','e','v','i','c','e','s',0};
@@ -592,7 +595,6 @@
 {
     ACImpl *This;
     const OSSDevice *oss_dev;
-    HRESULT hr;
 
     TRACE("%s %p %p\n", debugstr_guid(guid), dev, out);
 
@@ -606,13 +608,6 @@
     if(!This)
         return E_OUTOFMEMORY;
 
-    hr = CoCreateFreeThreadedMarshaler((IUnknown *)&This->IAudioClient_iface,
-        (IUnknown **)&This->pUnkFTMarshal);
-    if (FAILED(hr)) {
-         HeapFree(GetProcessHeap(), 0, This);
-         return hr;
-    }
-
     if(oss_dev->flow == eRender)
         This->fd = open(oss_dev->devnode, O_WRONLY | O_NONBLOCK, 0);
     else if(oss_dev->flow == eCapture)
@@ -677,7 +672,6 @@
 static HRESULT WINAPI AudioClient_QueryInterface(IAudioClient *iface,
         REFIID riid, void **ppv)
 {
-    ACImpl *This = impl_from_IAudioClient(iface);
     TRACE("(%p)->(%s, %p)\n", iface, debugstr_guid(riid), ppv);
 
     if(!ppv)
@@ -685,8 +679,6 @@
     *ppv = NULL;
     if(IsEqualIID(riid, &IID_IUnknown) || IsEqualIID(riid, &IID_IAudioClient))
         *ppv = iface;
-    else if(IsEqualIID(riid, &IID_IMarshal))
-        return IUnknown_QueryInterface(This->pUnkFTMarshal, riid, ppv);
     if(*ppv){
         IUnknown_AddRef((IUnknown*)*ppv);
         return S_OK;
@@ -708,24 +700,11 @@
 {
     ACImpl *This = impl_from_IAudioClient(iface);
     ULONG ref;
-
     ref = InterlockedDecrement(&This->ref);
     TRACE("(%p) Refcount now %u\n", This, ref);
     if(!ref){
-        if(This->timer){
-            HANDLE event;
-            DWORD wait;
-            event = CreateEventW(NULL, TRUE, FALSE, NULL);
-            wait = !DeleteTimerQueueTimer(g_timer_q, This->timer, event);
-            wait = wait && GetLastError() == ERROR_IO_PENDING;
-            if(event && wait)
-                WaitForSingleObject(event, INFINITE);
-            CloseHandle(event);
-        }
-
         IAudioClient_Stop(iface);
         IMMDevice_Release(This->parent);
-        IUnknown_Release(This->pUnkFTMarshal);
         This->lock.DebugInfo->Spare[0] = 0;
         DeleteCriticalSection(&This->lock);
         close(This->fd);
@@ -1107,8 +1086,6 @@
     This->period_frames = MulDiv(fmt->nSamplesPerSec, period, 10000000);
 
     This->bufsize_frames = MulDiv(duration, fmt->nSamplesPerSec, 10000000);
-    if(mode == AUDCLNT_SHAREMODE_EXCLUSIVE)
-        This->bufsize_frames -= This->bufsize_frames % This->period_frames;
     This->local_buffer = HeapAlloc(GetProcessHeap(), 0,
             This->bufsize_frames * fmt->nBlockAlign);
     if(!This->local_buffer){
@@ -1392,10 +1369,19 @@
 static void oss_write_data(ACImpl *This)
 {
     ssize_t written_bytes;
-    UINT32 written_frames, in_oss_frames, write_limit, max_period, write_offs_frames, new_frames;
-    SIZE_T to_write_frames, to_write_bytes, advanced;
+    UINT32 written_frames, in_oss_frames, write_limit, max_period;
+    size_t to_write_frames, to_write_bytes;
     audio_buf_info bi;
-    BYTE *buf;
+    BYTE *buf =
+        This->local_buffer + (This->lcl_offs_frames * This->fmt->nBlockAlign);
+
+    if(This->held_frames == 0)
+        return;
+
+    if(This->lcl_offs_frames + This->held_frames > This->bufsize_frames)
+        to_write_frames = This->bufsize_frames - This->lcl_offs_frames;
+    else
+        to_write_frames = This->held_frames;
 
     if(ioctl(This->fd, SNDCTL_DSP_GETOSPACE, &bi) < 0){
         WARN("GETOSPACE failed: %d (%s)\n", errno, strerror(errno));
@@ -1409,56 +1395,19 @@
                 bi.bytes, This->oss_bufsize_bytes);
         This->oss_bufsize_bytes = bi.bytes;
         in_oss_frames = 0;
-    }else
+    }else if(This->oss_bufsize_bytes - bi.bytes <= bi.fragsize)
+        in_oss_frames = 0;
+    else
         in_oss_frames = (This->oss_bufsize_bytes - bi.bytes) / This->fmt->nBlockAlign;
 
-    if(in_oss_frames > This->in_oss_frames){
-        TRACE("Capping reported frames from %u to %u\n",
-                in_oss_frames, This->in_oss_frames);
-        in_oss_frames = This->in_oss_frames;
-    }
-
     write_limit = 0;
     while(write_limit + in_oss_frames < max_period * 3)
         write_limit += max_period;
     if(write_limit == 0)
         return;
 
-    /*        vvvvvv - in_oss_frames
-     * [--xxxxxxxxxx]
-     *       [xxxxxxxxxx--]
-     *        ^^^^^^^^^^ - held_frames
-     *        ^ - lcl_offs_frames
-     */
-    advanced = This->in_oss_frames - in_oss_frames;
-    if(advanced > This->held_frames)
-        advanced = This->held_frames;
-    This->lcl_offs_frames += advanced;
-    This->lcl_offs_frames %= This->bufsize_frames;
-    This->held_frames -= advanced;
-    This->in_oss_frames = in_oss_frames;
-    TRACE("advanced by %lu, lcl_offs: %u, held: %u, in_oss: %u\n",
-            advanced, This->lcl_offs_frames, This->held_frames, This->in_oss_frames);
-
-
-    if(This->held_frames == This->in_oss_frames)
-        return;
-
-    write_offs_frames = (This->lcl_offs_frames + This->in_oss_frames) % This->bufsize_frames;
-    new_frames = This->held_frames - This->in_oss_frames;
-
-    if(write_offs_frames + new_frames > This->bufsize_frames)
-        to_write_frames = This->bufsize_frames - write_offs_frames;
-    else
-        to_write_frames = new_frames;
-
     to_write_frames = min(to_write_frames, write_limit);
     to_write_bytes = to_write_frames * This->fmt->nBlockAlign;
-    TRACE("going to write %lu frames from %u (%lu of %u)\n", to_write_frames,
-            write_offs_frames, to_write_frames + write_offs_frames,
-            This->bufsize_frames);
-
-    buf = This->local_buffer + write_offs_frames * This->fmt->nBlockAlign;
 
     if(This->session->mute)
         silence_buffer(This, buf, to_write_frames);
@@ -1471,42 +1420,54 @@
     }
     written_frames = written_bytes / This->fmt->nBlockAlign;
 
-    This->in_oss_frames += written_frames;
+    This->lcl_offs_frames += written_frames;
+    This->lcl_offs_frames %= This->bufsize_frames;
+    This->held_frames -= written_frames;
 
     if(written_frames < to_write_frames){
         /* OSS buffer probably full */
         return;
     }
 
-    if(new_frames > written_frames && written_frames < write_limit){
+    if(This->held_frames && written_frames < write_limit){
         /* wrapped and have some data back at the start to write */
 
-        to_write_frames = min(write_limit - written_frames, new_frames - written_frames);
+        to_write_frames = min(write_limit - written_frames, This->held_frames);
         to_write_bytes = to_write_frames * This->fmt->nBlockAlign;
 
         if(This->session->mute)
             silence_buffer(This, This->local_buffer, to_write_frames);
 
-        TRACE("wrapping to write %lu frames from beginning\n", to_write_frames);
-
         written_bytes = write(This->fd, This->local_buffer, to_write_bytes);
         if(written_bytes < 0){
             WARN("write failed: %d (%s)\n", errno, strerror(errno));
             return;
         }
         written_frames = written_bytes / This->fmt->nBlockAlign;
-        This->in_oss_frames += written_frames;
+
+        This->lcl_offs_frames += written_frames;
+        This->lcl_offs_frames %= This->bufsize_frames;
+        This->held_frames -= written_frames;
     }
 }
 
 static void oss_read_data(ACImpl *This)
 {
     UINT64 pos, readable;
+    audio_buf_info bi;
     ssize_t nread;
 
+    if(ioctl(This->fd, SNDCTL_DSP_GETISPACE, &bi) < 0){
+        WARN("GETISPACE failed: %d (%s)\n", errno, strerror(errno));
+        return;
+    }
+
     pos = (This->held_frames + This->lcl_offs_frames) % This->bufsize_frames;
     readable = (This->bufsize_frames - pos) * This->fmt->nBlockAlign;
 
+    if(bi.bytes < readable)
+        readable = bi.bytes;
+
     nread = read(This->fd, This->local_buffer + pos * This->fmt->nBlockAlign,
             readable);
     if(nread < 0){
@@ -1566,12 +1527,10 @@
         return AUDCLNT_E_NOT_STOPPED;
     }
 
-    if(!This->timer){
-        if(!CreateTimerQueueTimer(&This->timer, g_timer_q,
-                    oss_period_callback, This, 0, This->period_us / 1000,
-                    WT_EXECUTEINTIMERTHREAD))
-            ERR("Unable to create period timer: %u\n", GetLastError());
-    }
+    if(!CreateTimerQueueTimer(&This->timer, g_timer_q,
+                oss_period_callback, This, 0, This->period_us / 1000,
+                WT_EXECUTEINTIMERTHREAD))
+        ERR("Unable to create period timer: %u\n", GetLastError());
 
     This->playing = TRUE;
 
@@ -1583,6 +1542,8 @@
 static HRESULT WINAPI AudioClient_Stop(IAudioClient *iface)
 {
     ACImpl *This = impl_from_IAudioClient(iface);
+    HANDLE event;
+    DWORD wait;
 
     TRACE("(%p)\n", This);
 
@@ -1598,11 +1559,20 @@
         return S_FALSE;
     }
 
+    event = CreateEventW(NULL, TRUE, FALSE, NULL);
+    wait = !DeleteTimerQueueTimer(g_timer_q, This->timer, event);
+    if(wait)
+        WARN("DeleteTimerQueueTimer error %u\n", GetLastError());
+    wait = wait && GetLastError() == ERROR_IO_PENDING;
+
     This->playing = FALSE;
-    This->in_oss_frames = 0;
 
     LeaveCriticalSection(&This->lock);
 
+    if(event && wait)
+        WaitForSingleObject(event, INFINITE);
+    CloseHandle(event);
+
     return S_OK;
 }
 
@@ -1637,7 +1607,6 @@
     }
     This->held_frames = 0;
     This->lcl_offs_frames = 0;
-    This->in_oss_frames = 0;
 
     LeaveCriticalSection(&This->lock);
 
@@ -1785,7 +1754,6 @@
 static HRESULT WINAPI AudioRenderClient_QueryInterface(
         IAudioRenderClient *iface, REFIID riid, void **ppv)
 {
-    ACImpl *This = impl_from_IAudioRenderClient(iface);
     TRACE("(%p)->(%s, %p)\n", iface, debugstr_guid(riid), ppv);
 
     if(!ppv)
@@ -1795,8 +1763,6 @@
     if(IsEqualIID(riid, &IID_IUnknown) ||
             IsEqualIID(riid, &IID_IAudioRenderClient))
         *ppv = iface;
-    else if(IsEqualIID(riid, &IID_IMarshal))
-        return IUnknown_QueryInterface(This->pUnkFTMarshal, riid, ppv);
     if(*ppv){
         IUnknown_AddRef((IUnknown*)*ppv);
         return S_OK;
@@ -1951,7 +1917,6 @@
 static HRESULT WINAPI AudioCaptureClient_QueryInterface(
         IAudioCaptureClient *iface, REFIID riid, void **ppv)
 {
-    ACImpl *This = impl_from_IAudioCaptureClient(iface);
     TRACE("(%p)->(%s, %p)\n", iface, debugstr_guid(riid), ppv);
 
     if(!ppv)
@@ -1961,8 +1926,6 @@
     if(IsEqualIID(riid, &IID_IUnknown) ||
             IsEqualIID(riid, &IID_IAudioCaptureClient))
         *ppv = iface;
-    else if(IsEqualIID(riid, &IID_IMarshal))
-        return IUnknown_QueryInterface(This->pUnkFTMarshal, riid, ppv);
     if(*ppv){
         IUnknown_AddRef((IUnknown*)*ppv);
         return S_OK;
@@ -2161,10 +2124,7 @@
 
     TRACE("(%p)->(%p)\n", This, freq);
 
-    if(This->share == AUDCLNT_SHAREMODE_SHARED)
-        *freq = (UINT64)This->fmt->nSamplesPerSec * This->fmt->nBlockAlign;
-    else
-        *freq = This->fmt->nSamplesPerSec;
+    *freq = This->fmt->nSamplesPerSec;
 
     return S_OK;
 }
@@ -2173,6 +2133,7 @@
         UINT64 *qpctime)
 {
     ACImpl *This = impl_from_IAudioClock(iface);
+    int delay;
 
     TRACE("(%p)->(%p, %p)\n", This, pos, qpctime);
 
@@ -2182,9 +2143,18 @@
     EnterCriticalSection(&This->lock);
 
     if(This->dataflow == eRender){
-        *pos = This->written_frames - This->held_frames;
-        if(*pos < This->last_pos_frames)
+        if(!This->playing || !This->held_frames ||
+                ioctl(This->fd, SNDCTL_DSP_GETODELAY, &delay) < 0)
+            delay = 0;
+        else
+            delay /= This->fmt->nBlockAlign;
+        if(This->held_frames + delay >= This->written_frames)
             *pos = This->last_pos_frames;
+        else{
+            *pos = This->written_frames - This->held_frames - delay;
+            if(*pos < This->last_pos_frames)
+                *pos = This->last_pos_frames;
+        }
     }else if(This->dataflow == eCapture){
         audio_buf_info bi;
         UINT32 held;
@@ -2204,10 +2174,6 @@
 
     This->last_pos_frames = *pos;
 
-    TRACE("returning: %s\n", wine_dbgstr_longlong(*pos));
-    if(This->share == AUDCLNT_SHAREMODE_SHARED)
-        *pos *= This->fmt->nBlockAlign;
-
     LeaveCriticalSection(&This->lock);
 
     if(qpctime){

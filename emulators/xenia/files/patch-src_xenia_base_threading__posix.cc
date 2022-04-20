--- src/xenia/base/threading_posix.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/base/threading_posix.cc
@@ -25,6 +25,11 @@
 #include <ctime>
 #include <memory>
 
+#if XE_PLATFORM_FREEBSD
+  #include <pthread_np.h>
+  #include <sys/cpuset.h>
+#endif
+
 #if XE_PLATFORM_ANDROID
 #include <sched.h>
 
@@ -93,7 +98,11 @@ void EnableAffinityConfiguration() {}
 // uint64_t ticks() { return mach_absolute_time(); }
 
 uint32_t current_thread_system_id() {
+#if XE_PLATFORM_FREEBSD
+  return static_cast<uint32_t>((unsigned int)pthread_getthreadid_np());
+#else
   return static_cast<uint32_t>(syscall(SYS_gettid));
+#endif
 }
 
 void MaybeYield() {
@@ -617,10 +626,17 @@ class PosixCondition<Thread> : public PosixConditionBa
   }
 #endif
 
+#if XE_PLATFORM_FREEBSD
+  uint32_t system_id() const { return static_cast<uint32_t>((unsigned long)thread_); }
+#else
   uint32_t system_id() const { return static_cast<uint32_t>(thread_); }
+#endif
 
   uint64_t affinity_mask() {
     WaitStarted();
+#if XE_PLATFORM_FREEBSD
+    typedef cpuset_t cpu_set_t;
+#endif
     cpu_set_t cpu_set;
 #if XE_PLATFORM_ANDROID
     if (sched_getaffinity(pthread_gettid_np(thread_), sizeof(cpu_set_t),
@@ -643,6 +659,9 @@ class PosixCondition<Thread> : public PosixConditionBa
 
   void set_affinity_mask(uint64_t mask) {
     WaitStarted();
+    #if XE_PLATFORM_FREEBSD
+    typedef cpuset_t cpu_set_t;
+    #endif
     cpu_set_t cpu_set;
     CPU_ZERO(&cpu_set);
     for (auto i = 0u; i < 64; i++) {
@@ -691,6 +710,8 @@ class PosixCondition<Thread> : public PosixConditionBa
 #if XE_PLATFORM_ANDROID
     sigqueue(pthread_gettid_np(thread_),
              GetSystemSignal(SignalType::kThreadUserCallback), value);
+#elif XE_PLATFORM_FREEBSD
+    pthread_kill(thread_, GetSystemSignal(SignalType::kThreadUserCallback));
 #else
     pthread_sigqueue(thread_, GetSystemSignal(SignalType::kThreadUserCallback),
                      value);

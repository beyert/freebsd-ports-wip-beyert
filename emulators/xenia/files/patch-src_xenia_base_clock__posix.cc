--- src/xenia/base/clock_posix.cc.orig	2021-06-09 19:56:36 UTC
+++ src/xenia/base/clock_posix.cc
@@ -16,14 +16,14 @@ namespace xe {
 
 uint64_t Clock::host_tick_frequency_platform() {
   timespec res;
-  clock_getres(CLOCK_MONOTONIC_RAW, &res);
+  clock_getres(CLOCK_MONOTONIC, &res);
 
   return uint64_t(res.tv_sec) + uint64_t(res.tv_nsec) * 1000000000ull;
 }
 
 uint64_t Clock::host_tick_count_platform() {
   timespec res;
-  clock_gettime(CLOCK_MONOTONIC_RAW, &res);
+  clock_gettime(CLOCK_MONOTONIC, &res);
 
   return uint64_t(res.tv_sec) + uint64_t(res.tv_nsec) * 1000000000ull;
 }
@@ -43,4 +43,4 @@ uint64_t Clock::QueryHostUptimeMillis() {
   return host_tick_count_platform() * 1000 / host_tick_frequency_platform();
 }
 
-}  // namespace xe
\ No newline at end of file
+}  // namespace xe

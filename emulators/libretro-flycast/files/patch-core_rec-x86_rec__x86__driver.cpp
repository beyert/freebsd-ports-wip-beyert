--- core/rec-x86/rec_x86_driver.cpp.orig	2022-05-19 09:00:59 UTC
+++ core/rec-x86/rec_x86_driver.cpp
@@ -31,7 +31,9 @@ RuntimeBlockInfo* ngen_AllocateBlock(void)
 
 x86_block* x86e;
 
+#if HOST_CPU != CPU_X86
 static int cycle_counter;
+#endif
 
 void* loop_no_update;
 void* intc_sched;

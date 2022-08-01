------------------------------------------------------------------------
r219512 | hfinkel | 2014-10-10 17:06:20 +0000 (Fri, 10 Oct 2014) | 10 lines

[MiSched] Fix a logic error in tryPressure()

Fixes a logic error in the MachineScheduler found by Steve Montgomery (and
confirmed by Andy). This has gone unfixed for months because the fix has been
found to introduce some small performance regressions. However, Andy has
recommended that, at this point, we fix this to avoid further dependence on the
incorrect behavior (and then follow-up separately on any regressions), and I
agree.

Fixes PR18883.
------------------------------------------------------------------------
Index: lib/CodeGen/MachineScheduler.cpp
===================================================================
--- lib/CodeGen/MachineScheduler.cpp.orig	2014-07-02 16:46:08 UTC
+++ lib/CodeGen/MachineScheduler.cpp
@@ -2482,8 +2482,8 @@ static bool tryPressure(const PressureChange &TryP,
   }
   // If one candidate decreases and the other increases, go with it.
   // Invalid candidates have UnitInc==0.
-  if (tryLess(TryP.getUnitInc() < 0, CandP.getUnitInc() < 0, TryCand, Cand,
-              Reason)) {
+  if (tryGreater(TryP.getUnitInc() < 0, CandP.getUnitInc() < 0, TryCand, Cand,
+                 Reason)) {
     return true;
   }
   // If the candidates are decreasing pressure, reverse priority.

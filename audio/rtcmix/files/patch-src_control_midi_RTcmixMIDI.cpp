--- src/control/midi/RTcmixMIDI.cpp.orig	2022-06-20 19:29:55 UTC
+++ src/control/midi/RTcmixMIDI.cpp
@@ -445,7 +445,7 @@ int RTcmixMIDIOutput::stop()
 
 inline uchar make_status(uchar type, uchar chan) { return chan | type; }
 
-void RTcmixMIDIOutput::sendNoteOn(PmTimestamp timestamp, uchar chan, uchar pitch, uchar vel)
+void RTcmixMIDIOutput::sendNoteOn(long timestamp, uchar chan, uchar pitch, uchar vel)
 {
     PmEvent buffer;
     buffer.message = Pm_Message(make_status(kNoteOn, chan), pitch, vel);
@@ -455,7 +455,7 @@ void RTcmixMIDIOutput::sendNoteOn(PmTimestamp timestam
     unlock();
 }
 
-void RTcmixMIDIOutput::sendNoteOff(PmTimestamp timestamp, uchar chan, uchar pitch, uchar vel)
+void RTcmixMIDIOutput::sendNoteOff(long timestamp, uchar chan, uchar pitch, uchar vel)
 {
     PmEvent buffer;
     buffer.message = Pm_Message(make_status(kNoteOff, chan), pitch, vel);
@@ -465,7 +465,7 @@ void RTcmixMIDIOutput::sendNoteOff(PmTimestamp timesta
     unlock();
 }
 
-void RTcmixMIDIOutput::sendControl(PmTimestamp timestamp, uchar chan, uchar control, unsigned value)
+void RTcmixMIDIOutput::sendControl(long timestamp, uchar chan, uchar control, unsigned value)
 {
     PmEvent buffer;
     buffer.message = Pm_Message(make_status(kControl, chan), control, value);
@@ -487,7 +487,7 @@ void RTcmixMIDIOutput::sendPitchBend(long timestamp, u
     unlock();
 }
 
-void RTcmixMIDIOutput::sendProgramChange(PmTimestamp timestamp, uchar chan, uchar program)
+void RTcmixMIDIOutput::sendProgramChange(long timestamp, uchar chan, uchar program)
 {
     PmEvent buffer;
     buffer.message = Pm_Message(make_status(kProgram, chan), program, 0);

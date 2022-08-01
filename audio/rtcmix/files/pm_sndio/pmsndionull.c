/*
 * pmsndionull.c -- system specific definitions
 * 
 * written by:
 *  Roger Dannenberg
 * 
 * If there is no SNDIO or ALSA, you can define PMNULL and build
 * PortMidi. It will not report any devices, so you will not be able
 * to open any, but if you wanted to disable MIDI from some
 * application, this could be used.  Mainly, this code shows the
 * possibility of supporting multiple interfaces, e.g., ALSA and
 * Sndio on BSD, or ALSA and Jack on Linux.
 */

#ifdef PMNULL

#include "portmidi.h"
#include "pmsndionull.h"


PmError pm_sndionull_init(void)
{
    return pmNoError;
}


void pm_sndionull_term(void)
{
}

#endif

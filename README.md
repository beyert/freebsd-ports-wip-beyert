# FreeBSD ports work in progress

Author: Timothy Beyer (beyert)

## Purpose of repository

To better navigate the process of submitting and maintaining ports for FreeBSD, I figured that since I tend to port applications that are extremely niche (this is in part because certain types of software are neglected by FreeBSD developers, and I wish to remedy those gaps, as I think FreeBSD could potentially be much more general purpose in some application domains), there may not be enough committers with time to review my submissions, nor do I necessarily have time to get every port up to standard for submission.

In addition to this, many of my ports require custom versions of libraries that will take a lot of persuading committers to accept those submissions, particularly in the case of useful software depending on poorly maintained upstream libraries, or software that is (correctly or not) perceived as "obsolete" (to be fair, this is understandable from the mentality of a project such as FreeBSD with limited resources to maintain an extremely high standard of quality for the FreeBSD ports tree).  I wanted to provide a way for people to run this software and to give feedback on new ported applications.

These ports mostly work quite well as long as I updated them to my latest revision from my private Fossil repository of custom ports, but please provide feedback on which ports you would like to see PRs opened for submission.  Note that most of these are audio or emulators, which are not a high priority for accepting in the ports tree, but nonetheless there are some highlights in this collection, including the following:

  *  emulators: Libretro-PCSX2, Reicast, Libretro-Reicast, Libretro-Flycast, Experimental port of Xenia, Libretro ports of beetle saturn, kronos, fbneo, bsnes, mame, and numerous hacks on wine, including ALSA MIDI support, fixes for OSS audio echoing problem (on games like Mushihimesama), depending on the version

  *  audio: (the most interesting part of this repository, by far) the newest version of Pure Data, wineasio, wineasio-devel, submitted version of chuck, experimental unfinished VST version of bespokesynth, vst3sdk, several versions of portmidi, including multiple versions using sndio, ports of the old and new versions of cyclone, scheme for pd, pd-creamlibrary, pd-cicmwrapper, pd-footils, multiple versions of freeverb~, and about 20 other externals, an unsubmitted version of a2jmidid, an attempt at jamrouter, an attempt at porting airwave which doesn't fully work, and much more 

I've seen the potential of NetBSD's "ports-wip" concept, and I think it would suit my workflow well to get ports of niche software to people that want such applications on FreeBSD as quickly as possible, without increasing maintenance burden on committers.

## Note on redports repository

There used to be a build site called redports.org, which this repository was originally intended to 

If redports.org ever goes online again, I will use this repository to test my FreeBSD port contributions...

## Copyright / License

The license of this repository is either that of the respective project (at least for patches), or in the cases where it is derived from the Mk/ directory, or common port patterns the same as the license of the FreeBSD ports tree.  Many of these ports are derived from FreeBSD ports.

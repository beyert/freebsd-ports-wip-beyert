# FreeBSD ports work in progress

Author: Timothy Beyer (beyert)

## Purpose of repository

To better navigate the process of submitting and maintaining ports for FreeBSD, I decided to prepare a collection of ports that I am working on, or have completed but have PRs that have not yet been applied (I don't think anyone besides developers check FreeBSD's bugzilla PRs).

I've seen the potential of NetBSD's "ports-wip" concept, and I think it would suit my workflow well to make ports of niche software for FreeBSD ready more quickly for users who want such applications, without increasing maintenance burden on committers.

Certain types of software are mostly neglected by FreeBSD developers, but some of these applications are desired by users.  I wish to remedy those gaps, as I think FreeBSD could potentially be much more general purpose in some application domains, even in domains such as gaming or audio production.

To be fair, there may not be enough committers with time to review my submissions, nor do I necessarily have time to get every port up to standard for submission, as their QC process requires a lot of time and effort to navigate.  I also think that this will improve my quality control process, especially when I'm porting lots of different applications that are unrelated.

In addition to this, many of my ports require custom versions of libraries that will require me to persuade committers to accept those submissions, particularly in the case where an old but useful application depends on poorly maintained upstream libraries, or software that is (correctly or not) perceived as "obsolete" (to be fair, this is understandable from the mentality of a project such as FreeBSD with limited resources to maintain an extremely high standard of quality for the FreeBSD ports tree).

These ports mostly work quite well as long as I updated them to my latest revision from my private Fossil repository of custom ports, but please provide feedback on any ports you would like to see PRs opened for submission, recommend missing software not yet available on FreeBSD, or report any build or runtime issues that you encounter.

## Notable ports

Most of the ports in this repository are in the audio or emulators categories.  Some highlights in this collection include:

 *  audio: (the most interesting part of this repository, by far) the newest version of Pure Data, wineasio, wineasio-devel, submitted version of chuck, experimental unfinished VST version of bespokesynth, vst3sdk, several versions of portmidi, including multiple versions using sndio, ports of the old and new versions of cyclone, scheme for pd, pd-creamlibrary, pd-cicmwrapper, pd-footils, multiple versions of freeverb~, and about 20 other externals, an unsubmitted version of a2jmidid, an attempt at jamrouter, an attempt at porting airwave which doesn't fully work, and much more

  *  emulators: libretro-pcsx2, reicast, libretro-reicast, libretro-flycast, experimental port of xenia, libretro ports of beetle saturn, kronos, fbneo, bsnes, mame, and numerous hacks on wine (not all working, but can be fixed or documented upon request), including ALSA MIDI support, fixes for OSS audio echoing problem (on games like the Steam port of Mushihimesama), depending on the version
 
  *  lang: (mostly functional language implementations) numerous experimental versions of mlton, a custom port of scsh suitable for usage in 32-bit jails on amd64, updated versions of twelf and urweb that work on current versions of FreeBSD are notable


## Note on redports repository

There used to be a build site called redports.org, which this repository was originally intended to 

If redports.org ever goes online again, I will use this repository to test my FreeBSD port contributions...

## Copyright / License

The license of this repository is either that of the respective project (at least for patches), or in the cases where it is derived from the Mk/ directory, or common port patterns the same as the license of the FreeBSD ports tree.  Many of these ports are derived from FreeBSD ports.

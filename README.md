# FreeBSD ports work in progress

Author: Timothy Beyer (beyert)

## Purpose of repository

In order to better navigate the process of submitting and maintaining ports for FreeBSD, I decided to prepare a collection of ports that I am working on, or have completed, but have PRs that have not yet been applied (I don't think any non-developers check FreeBSD's bugzilla PRs).

I've seen the potential of NetBSD's "ports-wip" concept, and I think a similar process would suit my workflow well to more rapidly make ports on FreeBSD available of niche software for users who want such applications, without increasing maintenance burden on committers.

Some types of software are neglected on FreeBSD, or are even ridiculed by a few vocal FreeBSD users and developers, but in spite of some of this software having a tiny userbase, these applications are still desired by a segment of users.  I wish to remedy those gaps, as I think FreeBSD could be useful to a wider audience using unexpected application domains, including games/emulators and audio/music production (especially Pure Data has a lot of potential, but also wine runs most VST plugins).

To be fair, there may not be enough committers with time available to review my submissions, nor do I necessarily have time to get every port up to standard for submission, as their QC process requires a lot of time and effort to navigate.  I also think that this repository will improve my quality control process, especially when I'm porting lots of different applications in a short time frame that are unrelated.

This is also useful because many of the ports here require custom versions of libraries that will require persuading committers to accept those submissions, particularly in the case where an old but useful application depends on poorly maintained upstream libraries, or software that is (correctly or not) perceived as "obsolete" (this is understandable from the mentality of a project such as FreeBSD with limited resources and limited volunteer time to maintain an extremely high standard of quality for the FreeBSD ports tree).

The ports in this tree should generally work, as long as I remembered to update each port to the latest version from my private Fossil repository of custom ports.  I also need to remove some stale or obsolete ports to make this tree easier to navigate.  Please provide feedback on any ports you would like to see PRs opened for submission, recommend missing software not yet available on FreeBSD, or report any build or runtime issues that you encounter.

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

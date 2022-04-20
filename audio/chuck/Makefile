# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	chuck
PORTVERSION=	20210815
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Strongly-timed, Concurrent, and On-the-fly Music Programming Language

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/notes/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/linux/joystick.h:devel/evdev-proto \
	${LOCALBASE}/include/linux/types.h:multimedia/v4l_compat
LIB_DEPENDS=	libsndfile.so:audio/libsndfile \
	libudev.so:devel/libudev-devd
RUN_DEPENDS=	${LOCALBASE}/include/linux/joystick.h:devel/evdev-proto \
	${LOCALBASE}/include/linux/types.h:multimedia/v4l_compat

USES=	compiler:c++11-lib gmake dos2unix

OPTIONS_DEFINE=	DOCS EXAMPLES
OPTIONS_DEFAULT=	JACK SAME

OPTIONS_SINGLE=	BACKEND MIDI
OPTIONS_SINGLE_BACKEND=	JACK ALSA OSSV4
OPTIONS_SINGLE_MIDI=	SAME OSSJACK OSSALSA

JACK_DESC=	Jack sound system
ALSA_DESC=	ALSA sound system
OSSV4_DESC=	OSSv4 sound system

SAME_DESC=	Default MIDI for JACK or ALSA backends
OSSJACK_DESC=	JACK MIDI for OSSV4 backend
OSSALSA_DESC=	ALSA MIDI for OSSV4 backend

OSSV4_BUILD_DEPENDS+=	${LOCALBASE}/lib/oss/include/sys/soundcard.h:audio/oss
ALSA_LIB_DEPENDS+=	libasound.so:audio/alsa-lib
JACK_LIB_DEPENDS+=	libjack.so:audio/jack

OSSALSA_LIB_DEPENDS+=	libasound.so:audio/alsa-lib
OSSJACK_LIB_DEPENDS+=	libjack.so:audio/jack

.include <bsd.port.options.mk>

.if ${PORT_OPTIONS:MDOCS}
USE_TEX=	latex:formats dvipsk:build
.endif

DOS2UNIX_FILES=	${BUILD_WRKSRC}/host/RtAudio/RtAudio.cpp

USE_GITHUB=	yes
GH_ACCOUNT=	ccrma
GH_PROJECT=	chuck
GH_TAGNAME=	461d11f

CFLAGS+=	-I${LOCALBASE}/include

.if ${PORT_OPTIONS:MOSSV4}
CFLAGS+=	-I${LOCALBASE}/lib/oss/include
.endif

LDFLAGS+=	-L${LOCALBASE}/lib -L/usr/lib -L/lib

BUILD_WRKSRC=	${WRKSRC}/src
INSTALL_WRKSRC=	${BUILD_WRKSRC}
.if ${PORT_OPTIONS:MOSSV4}
ALL_TARGET=	freebsd-oss
.elif ${PORT_OPTIONS:MALSA}
ALL_TARGET=	freebsd-alsa
.elif ${PORT_OPTIONS:MJACK}
ALL_TARGET=	freebsd-jack
.else
ALL_TARGET=	freebsd-oss
.endif
MAKEFILE=	makefile

.if ${PORT_OPTIONS:MOSSV4} && ${PORT_OPTIONS:MSAME}
IGNORE+=	backend OSSV4 lacks MIDI, so for OSSV4 MIDI, use OSSJACK or OSSALSA
.elif ${PORT_OPTIONS:MJACK} && ! ${PORT_OPTIONS:MSAME}
IGNORE+=	backend JACK must use SAME MIDI
.elif ${PORT_OPTIONS:MALSA} && ! ${PORT_OPTIONS:MSAME}
IGNORE+=	backend ALSA must use SAME MIDI
.elif ${PORT_OPTIONS:MOSSJACK} || ${PORT_OPTIONS:MJACK}
EXTRA_PATCHES=	${PATCHDIR}/extra-patch-src_core_rtmidi-oss_jack.cpp
.elif ${PORT_OPTIONS:MOSSALSA} || ${PORT_OPTIONS:MALSA}
EXTRA_PATCHES=	${PATCHDIR}/extra-patch-src_core_rtmidi-oss_alsa.cpp
.endif

post-patch:
	@${REINPLACE_CMD} -e 's|make $(MAKECMDGOALS)|gmake $(MAKECMDGOALS)|' \
		-e 's|CC=gcc|CC=${CC}|' \
		-e 's|CXX=g++|CXX=${CXX}|' \
		-e 's|LD=g++|LD=${CXX}|' \
		-e 's|CFLAGS+= -O3|CFLAGS+=|' \
		${BUILD_WRKSRC}/${MAKEFILE} ${BUILD_WRKSRC}/core/${MAKEFILE}
.if ${PORT_OPTIONS:MOSSALSA}
	@${REINPLACE_CMD} \
		-e 's|linux-alsa|freebsd-oss linux-oss linux-alsa freebsd-alsa|g' \
		-e 's|linux-jack|linux-jack freebsd-jack|g' \
		${BUILD_WRKSRC}/${MAKEFILE} ${BUILD_WRKSRC}/core/${MAKEFILE}
.elif ${PORT_OPTIONS:MOSSJACK}
	@${REINPLACE_CMD} \
		-e 's|linux-alsa|linux-alsa freebsd-alsa|g' \
		-e 's|linux-jack|freebsd-oss linux-oss linux-jack freebsd-jack|g' \
		${BUILD_WRKSRC}/${MAKEFILE} ${BUILD_WRKSRC}/core/${MAKEFILE}
.else
	@${REINPLACE_CMD} \
		-e 's|linux-alsa|linux-alsa freebsd-alsa|g' \
		-e 's|linux-jack|linux-jack freebsd-jack|g' \
		${BUILD_WRKSRC}/${MAKEFILE} ${BUILD_WRKSRC}/core/${MAKEFILE}
.endif
.if ${PORT_OPTIONS:MOSSV4} && ${PORT_OPTIONS:MOSSALSA}
	@${REINPLACE_CMD} -e 's|__PLATFORM_LINUX__|__PLATFORM_FREEBSD__|' \
		-e 's|__LINUX_ALSA__|__FREEBSD_OSS__|' \
		-e 's| -lstdc++| -lc++ -lc|' \
		-e 's| -ldl||' \
		-e 's|-O3||' \
		${BUILD_WRKSRC}/core/makefile.x/makefile.alsa
.elif ${PORT_OPTIONS:MOSSV4} && ${PORT_OPTIONS:MOSSJACK}
	@${REINPLACE_CMD} -e 's|__PLATFORM_LINUX__|__PLATFORM_FREEBSD__|' \
		-e 's|__UNIX_JACK__|__FREEBSD_OSS__|' \
		-e 's| -lstdc++| -lc++ -lc|' \
		-e 's| -ldl||' \
		-e 's|-O3||' \
		-e 's| -lasound||' \
		${BUILD_WRKSRC}/core/makefile.x/makefile.jack
.elif ${PORT_OPTIONS:MALSA}
	@${REINPLACE_CMD} -e 's|__PLATFORM_LINUX__|__PLATFORM_FREEBSD__|' \
		-e 's|__LINUX_ALSA__|__FREEBSD_ALSA__|' \
		-e 's| -lstdc++| -lc++ -lc|' \
		-e 's| -ldl||' \
		-e 's|-O3||' \
		${BUILD_WRKSRC}/core/makefile.x/makefile.alsa
.else
	@${REINPLACE_CMD} -e 's|__PLATFORM_LINUX__|__PLATFORM_FREEBSD__|' \
		-e 's| -lstdc++| -lc++ -lc|' \
		-e 's| -ldl||' \
		-e 's|-O3||' \
		-e 's| -lasound||' \
		${BUILD_WRKSRC}/core/makefile.x/makefile.jack \
		${BUILD_WRKSRC}/core/makefile.x/makefile.pulse
.endif
	@${REINPLACE_CMD} 's/__PLATFORM_LINUX__/__PLATFORM_FREEBSD__/g' \
		${BUILD_WRKSRC}/core/chuck_io.cpp \
		${BUILD_WRKSRC}/core/lo/lo_endian.h
	@${REINPLACE_CMD} 's/defined(__PLATFORM_LINUX__)/defined(__PLATFORM_LINUX__) || defined(__PLATFORM_FREEBSD__)/g' \
		${BUILD_WRKSRC}/core/chuck_shell.cpp \
		${BUILD_WRKSRC}/core/lo/config.h \
		${BUILD_WRKSRC}/core/ugen_stk.h \
		${BUILD_WRKSRC}/core/util_sndfile.h \
		${BUILD_WRKSRC}/core/util_thread.cpp \
		${BUILD_WRKSRC}/core/util_thread.h \
		${BUILD_WRKSRC}/host/chuck_audio.h
	@${REINPLACE_CMD} 's/defined(__LINUX_OSS__)/defined(__FREEBSD_OSS__) || defined(__LINUX_OSS__)/g' \
		${BUILD_WRKSRC}/core/chuck_def.h
	@${REINPLACE_CMD} 's/\#ifdef __LINUX_ALSA__/\#if defined(__LINUX_ALSA__) || defined(__FREEBSD_ALSA__)/g' \
		${BUILD_WRKSRC}/core/util_sndfile.h
	@${REINPLACE_CMD} 's|\#define TYPEOF_SF_COUNT_T loff_t|\#define TYPEOF_SF_COUNT_T off_t|g' \
		${BUILD_WRKSRC}/core/util_sndfile.h

post-build:
.if ${PORT_OPTIONS:MDOCS}
	@cd ${WRKSRC}/doc/manual && ${MAKE} pdf
.endif

post-install:
.if ${PORT_OPTIONS:MDOCS}
	@${MKDIR} ${STAGEDIR}${DOCSDIR}
	@${CP} -p ${WRKSRC}/doc/manual/ChucK_manual.pdf ${STAGEDIR}${DOCSDIR}/
.endif
.if ${PORT_OPTIONS:MEXAMPLES}
	@${MKDIR} ${STAGEDIR}${EXAMPLESDIR}
	@${CP} -pR ${WRKSRC}/doc/manual/examples/* ${STAGEDIR}${EXAMPLESDIR}/
	@${CP} -pR ${WRKSRC}/examples/* ${STAGEDIR}${EXAMPLESDIR}/
.endif
	@${MV} ${STAGEDIR}/${PORTNAME} ${STAGEDIR}${PREFIX}/bin/${PORTNAME}

.include <bsd.port.mk>

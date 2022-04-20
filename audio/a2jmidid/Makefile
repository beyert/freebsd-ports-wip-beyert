# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	a2jmidid
PORTVERSION=	20201126
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Daemon for ALSA sequencer to JACK bridging

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386

#BUILD_DEPENDS=	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine \
#	with-glibc-shim:emulators/libc6-shim
LIB_DEPENDS=	libjack.so:audio/jack \
	libasound.so:audio/alsa-lib
RUN_DEPENDS=	aconnect:audio/alsa-utils \
	${LOCALBASE}/bin/jack_connect:audio/jack
#	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine

USES=	compiler:c11 meson

.include <bsd.port.options.mk>

LDFLAGS+=	-lexecinfo
USE_GCC=	yes

CFLAGS+=	-D_GNU_SOURCE

USE_GITHUB=	yes
GH_TUPLE=	jackaudio:a2jmidid:5b8f5d9

.include <bsd.port.mk>

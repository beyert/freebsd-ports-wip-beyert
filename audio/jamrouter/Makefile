# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	jamrouter
PORTVERSION=	20160310
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Near-Sample-Accurate JACK <-> Raw MIDI Router

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

#BUILD_DEPENDS=	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine \
#	with-glibc-shim:emulators/libc6-shim
LIB_DEPENDS=	libjack.so:audio/jack \
	libasound.so:audio/alsa-lib
RUN_DEPENDS=	aconnect:audio/alsa-utils \
	${LOCALBASE}/bin/jack_connect:audio/jack
#	${LOCALBASE}/include/wine/windows/winbase.h:emulators/wine

USES=	compiler:c11 gmake autoreconf
GNU_CONFIGURE=>.yes

.include <bsd.port.options.mk>

#LDFLAGS+=	-lexecinfo
#USE_GCC=	yes

#CFLAGS+=	-D_GNU_SOURCE

USE_GITHUB=	yes
GH_TUPLE=	williamweston:jamrouter:23527ae

.include <bsd.port.mk>

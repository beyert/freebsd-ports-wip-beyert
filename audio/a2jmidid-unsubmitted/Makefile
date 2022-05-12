# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	a2jmidid
PORTVERSION=	20201126
CATEGORIES=	audio
PKGNAMESUFFIX=	-unsubmitted

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Daemon for ALSA sequencer to JACK bridging

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

ONLY_FOR_ARCHS=	amd64 i386

LIB_DEPENDS=	libjack.so:audio/jack \
	libasound.so:audio/alsa-lib
RUN_DEPENDS=	aconnect:audio/alsa-utils \
	${LOCALBASE}/bin/jackd:audio/jack

USES=	compiler:c11 meson pkgconfig

.include <bsd.port.options.mk>

LDFLAGS+=	-lexecinfo
USE_GCC=	yes

CONFLICTS_INSTALL=	${PORTNAME}

CFLAGS+=	-D_GNU_SOURCE

USE_GITHUB=	yes
GH_TUPLE=	jackaudio:a2jmidid:5b8f5d9

.include <bsd.port.mk>

# $FreeBSD$

PORTNAME=	portmidi
PORTVERSION=	217
CATEGORIES=	audio
MASTER_SITES=	http://sourceforge.net/projects/portmedia/files/
DISTNAME=	${PORTNAME}-src-${PORTVERSION}

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Library for real time input and output of MIDI data

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/license.txt

LIB_DEPENDS=	libsndio.so:audio/sndio

USES=	cmake zip dos2unix

PLIST_FILES=	include/portmidi.h \
	include/porttime.h \
	lib/libportmidi.so \
	lib/libportmidi_s.a \
	libdata/pkgconfig/portmidi.pc

DOS2UNIX_FILES=	porttime/ptlinux.c

CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
USE_LDCONFIG=	yes
MAKE_JOBS_UNSAFE=	yes

CMAKE_ARGS+=	-DPROJECT_BINARY_DIR=Release \
	-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=${WRKSRC}/Release \
	-DCMAKE_LIBRARY_OUTPUT_DIRECTORY=${WRKSRC}/Release \
	-DCMAKE_RUNTIME_OUTPUT_DIRECTORY=${WRKSRC}/Release

NO_TEST=	Yes

WRKSRC=	${WRKDIR}/${PORTNAME}

post-extract:
	${CP} ${FILESDIR}/portmidi.pc.in ${WRKSRC}/
	${CP} -r ${FILESDIR}/pm_sndio ${WRKSRC}/

.include <bsd.port.mk>

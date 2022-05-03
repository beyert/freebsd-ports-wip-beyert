# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	portmidi
PORTVERSION=	2.0.3
PORTEPOCH=	1
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Library for real time input and output of MIDI data

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/license.txt

LIB_DEPENDS=	libsndio.so:audio/sndio

USES=	cmake

USE_GITHUB=	yes
GH_TUPLE=	PortMidi:portmidi:6a97d1e

CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib
USE_LDCONFIG=	yes
MAKE_JOBS_UNSAFE=	yes

post-extract:
	${CP} -r ${FILESDIR}/pm_sndio ${WRKSRC}/

.include <bsd.port.mk>

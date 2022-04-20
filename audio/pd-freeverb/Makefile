# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pd-freeverb
DISTVERSION=	20200104
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PD implementation of Jezar Freeverb code by Olaf Mattes

LICENSE=	GPLv2
LICENSE_FILE_GPLv2=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	electrickery:${PORTNAME}:71adb92

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

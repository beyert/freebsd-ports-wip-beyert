# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pd-iemguts
PORTVERSION=	0.3.1
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Collection of low level objects to build better PD abstractions

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	iem-projects:${PORTNAME}:2fd18fe

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

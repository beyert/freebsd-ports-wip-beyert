# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	gigaverb
PORTVERSION=	20200109
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PD-port of the Max MSP-port of Juhana Sadeharju\'s Gigaverb

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	electrickery:${PKGNAMEPREFIX}${PORTNAME}:42d808a

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

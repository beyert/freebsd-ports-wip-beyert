# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	creb
PORTVERSION=	20200112
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Abstractions and Externals library for Pure Data by Tom Schouten

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	electrickery:${PKGNAMEPREFIX}${PORTNAME}:c4441c5

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

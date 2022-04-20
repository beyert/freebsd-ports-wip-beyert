# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	lv2
PORTVERSION=	20190608
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	LV2 host external for Pure Data. Work in progress

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	jnonis:${PKGNAMEPREFIX}${PORTNAME}:c18cab6

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

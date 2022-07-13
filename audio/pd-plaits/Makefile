# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	plaits
PORTVERSION=	20190326
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Mutable Instruments Plaits for Pure Data

LICENSE=	MIT

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

PLIST_FILES=	lib/pd-externals/plts~/README.md \
		lib/pd-externals/plts~/plts~-help.pd \
		lib/pd-externals/plts~/plts~.pd_freebsd

USE_GITHUB=	yes
GH_TUPLE=	jnonis:${PKGNAMEPREFIX}${PORTNAME}:aad346c

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
		pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

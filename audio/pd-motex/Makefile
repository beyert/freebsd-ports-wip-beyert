# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	motex
PORTVERSION=	1.1.4
CATEGORIES=	audio
MASTER_SITES=	https://sourceforge.net/projects/pure-data/files/libraries/${PORTNAME}/
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Random collection of Pd objects by Iain Mott

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

#MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
#	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile
.endif

.include <bsd.port.mk>

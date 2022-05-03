# Created by: Tobias Brodel <brittlehaus@gmail.com>
# Restored by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	cyclone
PORTVERSION=	0.6.0
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-
PKGNAMESUFFIX=	-devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Set of Pure Data objects cloned from Max/MSP

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	porres:${PKGNAMEPREFIX}${PORTNAME}:773f6ac

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
	@${REINPLACE_CMD} -e 's|Linux|FreeBSD|g' \
		${WRKSRC}/Makefile
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

do-install:
	@${MKDIR} ${STAGEDIR}${PREFIX}/lib/pd-externals/cyclone
	@${FIND} ${WRKSRC} -name "*.pd" -exec ${INSTALL_DATA} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/cyclone \;
	@${FIND} ${WRKSRC} -name "*.pd_freebsd" -exec ${INSTALL_PROGRAM} {} \
		${STAGEDIR}${PREFIX}/lib/pd-externals/cyclone \;

.include <bsd.port.mk>

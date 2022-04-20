# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	fftease
PORTVERSION=	20220109
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	FFTease 3.0 external for Pd

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	ericlyon:${PKGNAMEPREFIX}${PORTNAME}:98e9819

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

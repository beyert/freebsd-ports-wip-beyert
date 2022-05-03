# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	iemlib
PORTVERSION=	1.22.2
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	General purpose objects and filters for Pure Data

LICENSE=	LGPL21
LICENSE_FILE=	${WRKSRC}/GnuLGPL.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd \
	${PREFIX}/lib/pd-externals/iemguts/try.pd_freebsd:audio/pd-iemguts

USES=	gmake

USE_GITLAB=	yes
GL_SITE=	https://git.iem.at
GL_ACCOUNT=	pd
GL_PROJECT=	${PORTNAME}
GL_COMMIT=	96c55b1a94342ae00536e05b362698ba706b4dda

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

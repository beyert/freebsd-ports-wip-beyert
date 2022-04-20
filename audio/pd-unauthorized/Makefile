# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	unauthorized
PORTVERSION=	20210729
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Revised version of Pure Data library by Yves Degoyon

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	libspeex.so:audio/speex \
	libmp3lame.so:audio/lame
BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	shakfu:pd-unauthorized:5eff56e

MAKE_ARGS+=	PDINCLUDEDIR=${LOCALBASE}/include/pd \
	pkglibdir=${PREFIX}/lib/pd-externals stripflags="${STRIP}"

post-extract:
	@${RM} ${WRKSRC}/Makefile.orig

post-patch:
	@${REINPLACE_CMD} -e 's|LICENSE.txt|LICENSE|' -e \
		's|binfile-meta|unauthorized-meta|' ${WRKSRC}/Makefile
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.pdlibbuilder
.endif

.include <bsd.port.mk>

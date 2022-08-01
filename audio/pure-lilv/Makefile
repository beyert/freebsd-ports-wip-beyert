# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pure-lilv
PORTVERSION=	0.5
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pure Lilv Interface

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${BUILD_WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		pure:lang/pure-restored \
		${LOCALBASE}/include/lilv-0/lilv/lilv.h:audio/lilv
LIB_DEPENDS=	liblilv-0.so:audio/lilv \
		libsratom-0.so:audio/sratom \
		libsord-0.so:devel/sord \
		libserd-0.so:devel/serd
RUN_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		pure:lang/pure-restored

USES=	gmake pkgconfig

CFLAGS+=	-I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib

PLIST_FILES=	lib/pure/lilv.pure lib/pure/lilv.so

USE_GITHUB=	yes
GH_TUPLE=	agraef:pure-lang:0aca920

BUILD_WRKSRC=	${WRKSRC}/${PKGNAMEPREFIX}${PORTNAME}
INSTALL_WRKSRC=	${BUILD_WRKSRC}

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${BUILD_WRKSRC}/Makefile
.endif

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/pure/lilv.so

.include <bsd.port.mk>

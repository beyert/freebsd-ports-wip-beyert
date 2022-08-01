# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	pure
PORTVERSION=	0.26
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PD loader for Pure scripts

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${BUILD_WRKSRC}/COPYING

BUILD_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		pure:lang/pure-restored
RUN_DEPENDS=	${LOCALBASE}/include/m_pd.h:audio/pd \
		pure:lang/pure-restored

USES=	gmake pkgconfig

CFLAGS+=	-I${LOCALBASE}/include -I/usr/include
LDFLAGS+=	-L${LOCALBASE}/lib -lc

USE_GITHUB=	yes
GH_TUPLE=	agraef:${PORTNAME}-lang:54bdfd4

BUILD_WRKSRC=	${WRKSRC}/${PKGNAMEPREFIX}${PORTNAME}
INSTALL_WRKSRC=	${BUILD_WRKSRC}

CFLAGS_i386=	-fPIC
LDFLAGS_i386=	-Wl,-z,notext

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${BUILD_WRKSRC}/Makefile
.endif

.include <bsd.port.mk>

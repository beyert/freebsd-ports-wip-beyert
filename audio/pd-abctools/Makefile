# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	abctools
PORTVERSION=	20170814
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Pure Data external objects

LICENSE=	BSD3CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	mrabc-yoichi:${PORTNAME}:1dc5e39

MAKE_ARGS=	PD_INCLUDE=${LOCALBASE}/include/pd

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif
	@${CP} -p ${FILESDIR}/${PORTNAME}-meta.pd ${WRKSRC}

.include <bsd.port.mk>

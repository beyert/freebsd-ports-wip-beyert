# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	flatgui
PORTVERSION=	0.1.1
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Restored flatgui external for modern versions of Pure Data

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	beyert:${PKGNAMEPREFIX}${PORTNAME}:0.1.1

#MAKE_ARGS=	PD_INCLUDE=${LOCALBASE}/include/pd

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>

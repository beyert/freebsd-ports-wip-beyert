# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	nusmuk_utils
PORTVERSION=	20211118
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Various personal utility externals for PD

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake
USE_GITHUB=	yes
GH_TUPLE=	ch-nry:pd_${PORTNAME}:6664b10

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>

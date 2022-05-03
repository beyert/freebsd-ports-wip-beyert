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

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>

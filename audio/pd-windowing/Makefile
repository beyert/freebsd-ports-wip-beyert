# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	windowing
DISTVERSION=	0.1
CATEGORIES=	audio
MASTER_SITES=	https://sourceforge.net/projects/pure-data/files/libraries/${PORTNAME}/
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Library of windowing functions for Pd

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	gmake

post-patch:
.if defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		-e 's|PD_PATH = /usr/local|PD_PATH = ${PREFIX}|' \
		-e 's|-L/usr/local/lib|-L${PREFIX}/lib|' \
		${WRKSRC}/Makefile
.endif

.include <bsd.port.mk>

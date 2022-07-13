# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	libfmsynth
PORTVERSION=	20200628
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	C library which implements an FM synthesizer

LICENSE=	MIT
LICENSE_FILE=	${WRKSRC}/COPYING

USES=	gmake compiler:c11

USE_GITHUB=	yes
GH_ACCOUNT=	Themaister
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	b989b5c

MAKEFILE=	GNUmakefile

post-patch:
	${REINPLACE_CMD} 's|/usr/local|${STAGEDIR}${PREFIX}|g' ${WRKSRC}/GNUmakefile

.include <bsd.port.mk>

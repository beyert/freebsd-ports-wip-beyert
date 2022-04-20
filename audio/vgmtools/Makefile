# $FreeBSD$

PORTNAME=	vgmtools
PORTVERSION=	20210527
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Tools for vgm/vgz files

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=		compiler cmake

USE_GITHUB=	yes
GH_ACCOUNT=	vgmrips
GH_TAGNAME=	a698613

STRIP=

.include <bsd.port.pre.mk>

TOOLS=	$$(cd ${CONFIGURE_WRKSRC}/CMakeFiles && ${LS} -1 -d *.dir | \
	${AWK} -F'.dir' '{ if ($$1 != "opt_oki" && $$1 != "optdac" && \
		$$1 != "optvgm32") { print $$1 } }')

do-install:
	cd ${CONFIGURE_WRKSRC} && ${CP} -p ${TOOLS} ${STAGEDIR}${LOCALBASE}/bin

.include <bsd.port.post.mk>

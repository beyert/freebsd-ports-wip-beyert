# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	vgmtools
DISTVERSION=	g20220718
CATEGORIES=	audio

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Tools for vgm/vgz files

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

USES=	cmake compiler

USE_GITHUB=	yes
GH_ACCOUNT=	vgmrips
GH_TAGNAME=	af83a85

STRIP=

.include <bsd.port.pre.mk>

TOOLS=	$$(cd ${CONFIGURE_WRKSRC}/CMakeFiles && ${LS} -1 -d *.dir | \
	${AWK} -F'.dir' '{ if ($$1 != "opt_oki" && $$1 != "optdac" && \
		$$1 != "optvgm32") { print $$1 } }')

.include <bsd.port.post.mk>

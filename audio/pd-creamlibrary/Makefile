# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	creamlibrary
PORTVERSION=	0.4.9
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	PD externals for those who like vanilla, chocolate, coffee or caramel

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	compiler:c++11-lib autoreconf gmake libtool

GNU_CONFIGURE=	yes

#CONFIGURE_ARGS=	--with-pd=${PREFIX}/include/pd

USE_GITHUB=	yes
GH_TUPLE=	 beyert:CreamLibrary:${PORTVERSION} \
	beyert:CicmWrapper:${PORTVERSION}:CreamLibrary/ThirdParty/CicmWrapper

INSTALL_TARGET=	install-strip

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.am
.endif

.include <bsd.port.mk>

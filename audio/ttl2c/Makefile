# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	ttl2c
PORTVERSION=	20180612
CATEGORIES=	audio devel

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Turtle to header conversion utility for LV2 plugin developers

LICENSE=	GPLv3
LICENSE_FILE=	${WRKSRC}/LICENSE

BUILD_DEPENDS=	\
		${LOCALBASE}/include/boost/core/cmath.hpp:devel/boost-libs

USES=	compiler:c++11-lang waf python:-3.0 pkgconfig

PLIST_FILES=	bin/${PORTNAME}

USE_GITHUB=	yes
GH_ACCOUNT=	lvtk
GH_PROJECT=	${PORTNAME}
GH_TAGNAME=	b64e425

CFLAGS+=	-I${LOCALBASE}/include

.include <bsd.port.mk>

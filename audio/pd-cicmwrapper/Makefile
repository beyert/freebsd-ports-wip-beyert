# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	cicmwrapper
PORTVERSION=	0.4.9
CATEGORIES=	audio
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	C interface for Tcl/Tk and PD to facilitate objects for Pure Data

LICENSE=	BSD2CLAUSE
LICENSE_FILE=	${WRKSRC}/LICENSE.txt

BUILD_DEPENDS=	pd:audio/pd
RUN_DEPENDS=	pd:audio/pd

USES=	autoreconf gmake pkgconfig libtool:keepla

GNU_CONFIGURE=	yes

#CONFIGURE_ARGS=	--with-pd="${PREFIX}"

USE_GITHUB=	yes
GH_TUPLE=	beyert:CicmWrapper:${PORTVERSION}

do-install:
	${INSTALL_DATA} ${WRKSRC}/Sources/libCicmWrapper.la \
		${STAGEDIR}${PREFIX}/lib/
	${INSTALL_DATA} ${WRKSRC}/Sources/.libs/libCicmWrapper.a \
		${STAGEDIR}${PREFIX}/lib/

post-patch:
.if defined(LOCALBASE) || defined(PREFIX)
	@${REINPLACE_CMD} -e 's|/usr/local/include|${LOCALBASE}/include|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		${WRKSRC}/pd-lib-builder/Makefile.am
.endif

.include <bsd.port.mk>

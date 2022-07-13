# Created by: Timothy Beyer <beyert@cs.ucr.edu>

PORTNAME=	lua
PORTVERSION=	20210328
CATEGORIES=	audio lang
PKGNAMEPREFIX=	pd-

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Lua bindings for Pd

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

BUILD_DEPENDS=	pd:audio/pd lua53:lang/lua53
RUN_DEPENDS=	pd:audio/pd lua53:lang/lua53

USES=	gmake

USE_GITHUB=	yes
GH_TUPLE=	agraef:${PKGNAMEPREFIX}${PORTNAME}:f07953b

MAKE_ARGS+=	PDINCLUDEDIR="${LOCALBASE}/include/pd" \
	pkglibdir="${PREFIX}/lib/pd-externals" stripflags="${STRIP}"

post-patch:
	@${REINPLACE_CMD} -e 's|/usr/local/include/lua|${LOCALBASE}/include/lua53|g' \
		-e 's|prefix = /usr/local|prefix = ${PREFIX}|' \
		-e 's|PD_PATH = /usr/local|PD_PATH = ${PREFIX}|' \
		-e 's|-L/usr/local/lib -llua|-L${PREFIX}/lib -llua-5.3|' \
		${WRKSRC}/Makefile

.include <bsd.port.mk>

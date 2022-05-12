# Created by: Kelly Hays <kelly.hays@jkhfamily.org>
# $FreeBSD: head/devel/luafilesystem/Makefile 387986 2015-05-30 21:25:06Z mat $

PORTNAME=	luafilesystem
DISTVERSIONPREFIX=	v_
DISTVERSION=	1_6_3
PORTREVISION=	1
CATEGORIES=	devel
PKGNAMEPREFIX=	${LUA_PKGNAMEPREFIX}

MAINTAINER=	fiziologus@gmail.com
COMMENT=	Library to access directory structure and file attributes

LICENSE=	MIT

USES?=		lua

USE_GITHUB=	yes
GH_ACCOUNT=	keplerproject

ALL_TARGET=	lib

PLIST_FILES=	%%LUA_MODLIBDIR%%/lfs.so
PORTDOCS=	*

MAKE_ARGS+=	INCS="-I${LUA_INCDIR}"

OPTIONS_DEFINE=	DOCS

post-patch:
	${REINPLACE_CMD} -e \
		"s|%%PREFIX%%|${PREFIX}| ; \
		s|%%MODLIBDIR%%|${LUA_MODLIBDIR}| ; \
		s|%%INCDIR%%|${LUA_INCDIR}|" ${WRKSRC}/config

post-install:
	${MKDIR} ${STAGEDIR}${DOCSDIR} && \
	${INSTALL_DATA} ${WRKSRC}/doc/us/* ${STAGEDIR}${DOCSDIR}

.include <bsd.port.mk>

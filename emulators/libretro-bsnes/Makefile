# $FreeBSD$

PORTNAME=	libretro-bsnes2014_performance
PORTVERSION=	0.20201030
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Standalone port of bSNES 2014 (performance) to libretro

LICENSE=	GPLv3

USES=		compiler:c++11-lib gmake
USE_LDCONFIG=	yes

USE_GITHUB=	yes
GH_ACCOUNT=	libretro
GH_PROJECT=	bsnes-libretro
GH_TAGNAME=	6d2c3a8

PLIST_FILES=	lib/libretro/bsnes2014_performance_libretro.so

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKSRC}/bsnes2014_performance_libretro.so ${STAGEDIR}/${PREFIX}/lib/libretro;

.include <bsd.port.mk>

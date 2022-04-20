# $FreeBSD$

PORTNAME=	libretro-beetle_saturn
PORTVERSION=	0.20210617
CATEGORIES=	emulators games

MAINTAINER=	beyert@cs.ucr.edu
COMMENT=	Fork of Mednafen Saturn for libretro

LICENSE=	GPLv2
LICENSE_FILE=	${WRKSRC}/COPYING

USES=		compiler:c++11-lib gmake gl
USE_LDCONFIG=	yes
USE_GL=	gl glu

USE_GITHUB=	yes
GH_ACCOUNT=	libretro
GH_PROJECT=	beetle-saturn-libretro
GH_TAGNAME=	ee5b214

PLIST_FILES=	lib/libretro/mednafen_saturn_libretro.so

.include <bsd.port.pre.mk>

do-install:
	${MKDIR} ${STAGEDIR}/${PREFIX}/lib/libretro;
	${INSTALL_LIB} ${WRKSRC}/mednafen_saturn_libretro.so ${STAGEDIR}/${PREFIX}/lib/libretro;

.include <bsd.port.post.mk>
